#!/usr/bin/env python3
"""
ROS2 Python node: screw_detector (Pure Math Version)

This node performs multi-view triangulation without running the vision model itself.
It receives:
1. N Camera Poses
2. 2D Detections (u,v) corresponding to those poses
3. Camera Intrinsics

It outputs:
1. 3D Screw Positions (triangulated via RANSAC)
2. Desired End-Effector Poses to align camera Z-axis with the screws
"""

import math
import random
from typing import List, Optional, Tuple

import numpy as np
import rclpy
from rclpy.node import Node

from geometry_msgs.msg import Pose, Point
from screw_interfaces.srv import LocalizeScrews


# ==============================================================================
# 1. MATH UTILITIES (Geometry & Triangulation)
# ==============================================================================

class Ray:
    def __init__(self, o: np.ndarray, d: np.ndarray):
        self.o = o  # origin (3,)
        self.d = d  # unit direction (3,)

def quat_to_R(qx, qy, qz, qw) -> np.ndarray:
    n = math.sqrt(qx*qx + qy*qy + qz*qz + qw*qw)
    if n == 0.0: return np.eye(3)
    qx, qy, qz, qw = qx/n, qy/n, qz/n, qw/n
    xx, yy, zz = qx*qx, qy*qy, qz*qz
    xy, xz, yz = qx*qy, qx*qz, qy*qz
    wx, wy, wz = qw*qx, qw*qy, qw*qz
    return np.array([
        [1 - 2*(yy + zz),     2*(xy - wz),       2*(xz + wy)],
        [2*(xy + wz),         1 - 2*(xx + zz),   2*(yz - wx)],
        [2*(xz - wy),         2*(yz + wx),       1 - 2*(xx + yy)],
    ], dtype=np.float64)

def R_to_quat(R: np.ndarray) -> Tuple[float, float, float, float]:
    tr = float(np.trace(R))
    if tr > 0.0:
        S = math.sqrt(tr + 1.0) * 2.0
        qw, qx, qy, qz = 0.25 * S, (R[2,1] - R[1,2]) / S, (R[0,2] - R[2,0]) / S, (R[1,0] - R[0,1]) / S
    else:
        if R[0,0] > R[1,1] and R[0,0] > R[2,2]:
            S = math.sqrt(1.0 + R[0,0] - R[1,1] - R[2,2]) * 2.0
            qw, qx, qy, qz = (R[2,1] - R[1,2]) / S, 0.25 * S, (R[0,1] + R[1,0]) / S, (R[0,2] + R[2,0]) / S
        elif R[1,1] > R[2,2]:
            S = math.sqrt(1.0 + R[1,1] - R[0,0] - R[2,2]) * 2.0
            qw, qx, qy, qz = (R[0,2] - R[2,0]) / S, (R[0,1] + R[1,0]) / S, 0.25 * S, (R[1,2] + R[2,1]) / S
        else:
            S = math.sqrt(1.0 + R[2,2] - R[0,0] - R[1,1]) * 2.0
            qw, qx, qy, qz = (R[1,0] - R[0,1]) / S, (R[0,2] + R[2,0]) / S, (R[1,2] + R[2,1]) / S, 0.25 * S
    n = math.sqrt(qx*qx + qy*qy + qz*qz + qw*qw)
    return (0.0, 0.0, 0.0, 1.0) if n == 0 else (qx/n, qy/n, qz/n, qw/n)

def pose_to_T(p: Pose) -> np.ndarray:
    T = np.eye(4, dtype=np.float64)
    T[:3, :3] = quat_to_R(p.orientation.x, p.orientation.y, p.orientation.z, p.orientation.w)
    T[:3, 3] = [p.position.x, p.position.y, p.position.z]
    return T

def T_to_pose(T: np.ndarray) -> Pose:
    p = Pose()
    p.position.x, p.position.y, p.position.z = float(T[0,3]), float(T[1,3]), float(T[2,3])
    p.orientation.x, p.orientation.y, p.orientation.z, p.orientation.w = R_to_quat(T[:3, :3])
    return p

def invert_T(T: np.ndarray) -> np.ndarray:
    R, t = T[:3, :3], T[:3, 3]
    Ti = np.eye(4)
    Ti[:3, :3] = R.T
    Ti[:3, 3] = -R.T @ t
    return Ti

def pixel_to_world_ray(u, v, T_cam_world, K) -> Ray:
    """Project pixel (u,v) to a 3D ray in World Frame."""
    fx, fy, cx, cy = K[0,0], K[1,1], K[0,2], K[1,2]
    # 1. Ray in Camera Frame
    d_cam = np.array([(u - cx)/fx, (v - cy)/fy, 1.0])
    d_cam /= np.linalg.norm(d_cam)
    # 2. Transform to World Frame
    R, t = T_cam_world[:3, :3], T_cam_world[:3, 3]
    d_world = R @ d_cam
    return Ray(o=t.copy(), d=d_world / np.linalg.norm(d_world))

def closest_point_between_rays(r1: Ray, r2: Ray) -> Optional[np.ndarray]:
    w0 = r1.o - r2.o
    a, b, c = np.dot(r1.d, r1.d), np.dot(r1.d, r2.d), np.dot(r2.d, r2.d)
    d, e = np.dot(r1.d, w0), np.dot(r2.d, w0)
    denom = a*c - b*b
    if abs(denom) < 1e-9: return None
    s = (b*e - c*d) / denom
    t = (a*e - b*d) / denom
    return 0.5 * ((r1.o + s*r1.d) + (r2.o + t*r2.d))

def point_to_ray_dist(pt: np.ndarray, r: Ray) -> float:
    v = pt - r.o
    return np.linalg.norm(v - np.dot(v, r.d) * r.d)

# ==============================================================================
# 2. RANSAC LOGIC
# ==============================================================================

def ransac_triangulation(rays: List[Ray], max_screws=5, thresh=0.01, iters=100) -> List[Tuple[np.ndarray, float]]:
    """Returns list of (3d_point, rmse) tuples."""
    remaining_indices = list(range(len(rays)))
    results = []

    for _ in range(max_screws):
        if len(remaining_indices) < 2: break
        
        best_inliers, best_pt = [], None

        for _ in range(iters):
            # Pick 2 random rays to hypothesize a point
            idx1, idx2 = random.sample(remaining_indices, 2)
            pt_hyp = closest_point_between_rays(rays[idx1], rays[idx2])
            if pt_hyp is None: continue

            # Check support
            current_inliers = [i for i in remaining_indices if point_to_ray_dist(pt_hyp, rays[i]) < thresh]
            
            if len(current_inliers) > len(best_inliers):
                best_inliers = current_inliers
                best_pt = pt_hyp

        # Heuristic: need at least 3 rays to confirm a screw (or 2 if very strict)
        if len(best_inliers) < 3: break 

        # Refine point using Least Squares on all inliers
        # Solve Ax = b where A = sum(I - dd^T), b = sum((I - dd^T)o)
        A, b = np.zeros((3,3)), np.zeros(3)
        for i in best_inliers:
            d, o = rays[i].d, rays[i].o
            M = np.eye(3) - np.outer(d, d)
            A += M
            b += M @ o
        
        refined_pt = np.linalg.solve(A, b)
        
        # Calculate RMSE
        dists = [point_to_ray_dist(refined_pt, rays[i]) for i in best_inliers]
        rmse = np.sqrt(np.mean(np.array(dists)**2))
        
        results.append((refined_pt, rmse))
        
        # Remove inliers from pool
        remaining_indices = [i for i in remaining_indices if i not in best_inliers]

    return results

# ==============================================================================
# 3. POSE GENERATION (Align Camera Z to Screw)
# ==============================================================================

def get_look_at_pose(target: np.ndarray, current_cam_pos: np.ndarray, up=np.array([0,0,1.])) -> np.ndarray:
    """Returns 4x4 T_world_cam looking at target."""
    z_axis = target - current_cam_pos
    z_axis /= np.linalg.norm(z_axis)
    x_axis = np.cross(up, z_axis)
    x_axis /= np.linalg.norm(x_axis)
    y_axis = np.cross(z_axis, x_axis)
    
    T = np.eye(4)
    T[:3, 0], T[:3, 1], T[:3, 2] = x_axis, y_axis, z_axis
    T[:3, 3] = current_cam_pos
    return T

def calculate_ee_pose(screw_pt: np.ndarray, T_ee_cam: np.ndarray, dist_m: float) -> Pose:
    """
    Calculates T_world_ee such that the camera looks directly at screw_pt 
    from dist_m away along the Z-axis.
    """
    # 1. Determine Desired Camera Position (Approaching from above/Z-world)
    # We want cam to be at screw + (dist * world_up) roughly
    # But strictly, we align camera Z to the vector (Screw - Cam)
    # Let's assume a top-down approach vector
    approach_vec = np.array([0, 0, 1.0]) 
    cam_pos_world = screw_pt + (approach_vec * dist_m) # Simple top-down approach
    
    # 2. Compute T_world_cam (Look At)
    # Look from cam_pos -> screw_pt. World Up is Y usually for robotics, or Z. 
    # Let's assume standard Z-up world.
    # Note: LookAt creates Z-axis pointing AT target. 
    T_world_cam = get_look_at_pose(screw_pt, cam_pos_world, up=np.array([0,1,0.]))

    # 3. Compute T_world_ee
    # T_world_ee = T_world_cam * T_cam_ee (which is inv(T_ee_cam))
    T_world_ee = T_world_cam @ invert_T(T_ee_cam)
    
    return T_to_pose(T_world_ee)

# ==============================================================================
# 4. ROS NODE
# ==============================================================================

from dataclasses import dataclass

class ScrewTriangulatorNode(Node):
    def __init__(self):
        super().__init__("screw_detector") # Keeps same node name
        
        # Params
        self.declare_parameter("T_ee_cam", [1.,0.,0.,0., 0.,1.,0.,0., 0.,0.,1.,0., 0.,0.,0.,1.])
        self.declare_parameter("approach_dist_m", 0.25)
        
        # Service
        self.srv = self.create_service(LocalizeScrews, "detect_screws", self.handle_service)
        self.get_logger().info("Screw Triangulator Ready. Waiting for detections...")

    def handle_service(self, req, resp):
        # 1. Validation
        if len(req.camera_poses) != req.n:
            resp.success = False
            resp.message = "Mismatch: n != len(camera_poses)"
            return resp
            
        if sum(req.num_detections_per_pose) != len(req.screw_2d_centroids):
            resp.success = False
            resp.message = "Mismatch: sum(counts) != len(detections)"
            return resp

        # 2. Parse Params
        K = np.array(req.intrinsics).reshape(3,3)
        T_ee_cam = np.array(self.get_parameter("T_ee_cam").value).reshape(4,4)
        dist_m = self.get_parameter("approach_dist_m").value
        
        # 3. Build Rays
        rays = []
        det_idx = 0
        
        for i in range(req.n):
            T_world_cam = pose_to_T(req.camera_poses[i])
            num_dets = req.num_detections_per_pose[i]
            
            for _ in range(num_dets):
                pt_2d = req.screw_2d_centroids[det_idx]
                det_idx += 1
                
                # Create Ray
                ray = pixel_to_world_ray(pt_2d.x, pt_2d.y, T_world_cam, K)
                rays.append(ray)

        if len(rays) < 2:
            resp.success = False
            resp.message = "Not enough detections for triangulation."
            return resp

        # 4. Triangulate
        screws = ransac_triangulation(
            rays, 
            max_screws=req.max_screws, 
            thresh=req.ransac_inlier_thresh_m, 
            iters=req.ransac_iters
        )

        if not screws:
            resp.success = False
            resp.message = "RANSAC failed to find stable points."
            return resp

        # 5. Build Response
        resp.success = True
        resp.message = f"Found {len(screws)} screws."
        
        for (pt, rmse) in screws:
            # Add Position
            p_msg = Point()
            p_msg.x, p_msg.y, p_msg.z = pt[0], pt[1], pt[2]
            resp.screw_positions.append(p_msg)
            resp.screw_fit_rmse_m.append(rmse)
            
            # Add Desired Pose
            pose_msg = calculate_ee_pose(pt, T_ee_cam, dist_m)
            resp.desired_ee_poses.append(pose_msg)

        return resp

def main():
    rclpy.init()
    node = ScrewTriangulatorNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()