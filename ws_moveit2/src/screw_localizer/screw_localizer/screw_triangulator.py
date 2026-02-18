#!/usr/bin/env python3
import numpy as np
import random
from typing import List, Tuple, Optional

import rclpy
from rclpy.node import Node
from scipy.spatial.transform import Rotation as R
from scipy.optimize import least_squares

from geometry_msgs.msg import Pose, Point
from screw_interfaces.srv import LocalizeScrews

# ==============================================================================
# 1. GEOMETRY UTILITIES (Refactored with SciPy)
# ==============================================================================

class Ray:
    def __init__(self, o: np.ndarray, d: np.ndarray, cam_id: int = 0):
        self.o = o  # Origin
        self.d = d / np.linalg.norm(d)  # Normalized Direction
        self.cam_id = cam_id  # Camera ID to track which camera this ray comes from

def pose_to_T(p: Pose) -> np.ndarray:
    T = np.eye(4)
    # Use SciPy for Quaternion -> Rotation Matrix
    quat = [p.orientation.x, p.orientation.y, p.orientation.z, p.orientation.w]
    T[:3, :3] = R.from_quat(quat).as_matrix()
    T[:3, 3] = [p.position.x, p.position.y, p.position.z]
    return T

def T_to_pose(T: np.ndarray) -> Pose:
    p = Pose()
    p.position.x, p.position.y, p.position.z = T[:3, 3]
    # Use SciPy for Rotation Matrix -> Quaternion
    quat = R.from_matrix(T[:3, :3]).as_quat()
    p.orientation.x, p.orientation.y, p.orientation.z, p.orientation.w = quat
    return p

def pixel_to_world_ray(u, v, T_world_cam, K, cam_id: int = 0) -> Ray:
    fx, fy, cx, cy = K[0,0], K[1,1], K[0,2], K[1,2]
    d_cam = np.array([(u - cx)/fx, (v - cy)/fy, 1.0])
    
    # Rotate ray direction to world frame
    d_world = T_world_cam[:3, :3] @ d_cam
    return Ray(o=T_world_cam[:3, 3], d=d_world, cam_id=cam_id)

def point_to_ray_dist(pt: np.ndarray, ray: Ray) -> float:
    # Vector from ray origin to point
    w = pt - ray.o
    # Orthogonal distance formula
    return np.linalg.norm(w - np.dot(w, ray.d) * ray.d)

# ==============================================================================
# 2. TRIANGULATION & RANSAC
# ==============================================================================

def solve_least_squares_point(rays: List[Ray], initial_guess: np.ndarray) -> np.ndarray:
    """Refines the 3D point by minimizing the sum of squared distances to all rays."""
    def residuals(p):
        return [point_to_ray_dist(p, r) for r in rays]
    
    res = least_squares(residuals, initial_guess, loss='soft_l1')
    return res.x

def closest_point_between_rays(r1: Ray, r2: Ray) -> Optional[np.ndarray]:
    # Standard geometric intersection of two 3D lines
    n = np.cross(r1.d, r2.d)
    denom = np.linalg.norm(n)**2
    if denom < 1e-9: return None
    
    res = r1.o - r2.o
    t1 = np.linalg.det([res, r2.d, n]) / denom
    t2 = np.linalg.det([res, r1.d, n]) / denom
    return 0.5 * ((r1.o + t1*r1.d) + (r2.o + t2*r2.d))

def select_poses_by_baseline(camera_positions: List[np.ndarray], m: int) -> List[int]:
    """
    Select m camera poses that maximize pairwise baselines (distances).
    
    Args:
        camera_positions: List of camera position vectors (origins)
        m: Number of poses to select. Should be at least 2, recommended 3-4.
           If m > len(camera_positions), returns all indices.
    
    Returns:
        List of m indices with best pairwise spread
    """
    n = len(camera_positions)
    if n <= m:
        return list(range(n))
    
    # Greedy selection: start with two farthest poses, then add poses maximizing min distance
    selected = []
    max_dist = 0
    max_pair = (0, 1)
    
    # Find two farthest poses
    for i in range(n):
        for j in range(i + 1, n):
            dist = np.linalg.norm(camera_positions[i] - camera_positions[j])
            if dist > max_dist:
                max_dist = dist
                max_pair = (i, j)
    
    selected = list(max_pair)

    # Greedily add poses that maximize minimum distance to selected poses
    while len(selected) < m:
        best_idx = -1
        best_min_dist = -1
        
        for i in range(n):
            if i in selected:
                continue
            # Compute minimum distance to all selected poses
            min_dist = min(np.linalg.norm(camera_positions[i] - camera_positions[s]) for s in selected)
            if min_dist > best_min_dist:
                best_min_dist = min_dist
                best_idx = i
        
        if best_idx >= 0:
            selected.append(best_idx)
        else:
            break
    
    return selected[:m]



# ==============================================================================
# 3. POSE GENERATION
# ==============================================================================

def get_look_at_pose(target: np.ndarray, eye: np.ndarray) -> np.ndarray:
    """Generates T_world_cam looking at target from eye position."""
    z = target - eye
    z /= np.linalg.norm(z)
    # Using Scipy to build rotation from vectors (Forward=Z, Up=Y)
    y_global = np.array([0, 1, 0])
    x = np.cross(y_global, z)
    x /= np.linalg.norm(x)
    y = np.cross(z, x)
    
    T = np.eye(4)
    T[:3, :3] = np.stack([x, y, z], axis=1)
    T[:3, 3] = eye
    return T

# ==============================================================================
# 4. ROS NODE
# ==============================================================================

class ScrewTriangulatorNode(Node):
    def __init__(self):
        super().__init__("screw_detector")
        self.declare_parameter("approach_dist_m", 0.25)
        self.srv = self.create_service(LocalizeScrews, "detect_screws", self.handle_service)
        self.get_logger().info("Screw Triangulator Node Ready")

    def ransac_triangulation(self, rays: List[Ray], max_screws=5, thresh=0.01, iters=100):
        remaining_indices = list(range(len(rays)))
        results = []

        for screw_idx in range(max_screws):
            if len(remaining_indices) < 2: break
            
            best_inliers, best_pt = [], None

            for iter_idx in range(iters):
                idx1, idx2 = random.sample(remaining_indices, 2)
                
                # CRITICAL: Only triangulate rays from DIFFERENT cameras
                if rays[idx1].cam_id == rays[idx2].cam_id:
                    continue
                
                pt_hyp = closest_point_between_rays(rays[idx1], rays[idx2])
                if pt_hyp is None: continue

                inliers = [i for i in remaining_indices if point_to_ray_dist(pt_hyp, rays[i]) < thresh]
                
                if len(inliers) > len(best_inliers):
                    best_inliers, best_pt = inliers, pt_hyp

            if len(best_inliers) < 3: break 

            # SciPy Refinement
            refined_pt = solve_least_squares_point([rays[i] for i in best_inliers], best_pt)
            rmse = np.sqrt(np.mean([point_to_ray_dist(refined_pt, rays[i])**2 for i in best_inliers]))
            
            # DEBUG: Check if point is near camera origins
            min_dist_to_origin = min(np.linalg.norm(refined_pt - rays[i].o) for i in best_inliers)
            self.get_logger().info(f"  [RANSAC] Screw {screw_idx}: inliers={len(best_inliers)}, pt={refined_pt}, rmse={rmse:.6f}, min_dist_to_origin={min_dist_to_origin:.6f}")
            
            results.append((refined_pt, rmse))
            remaining_indices = [i for i in remaining_indices if i not in best_inliers]

        return results

    def handle_service(self, req, resp):
        K = np.array(req.intrinsics).reshape(3,3)
        dist_m = self.get_parameter("approach_dist_m").value
        
        self.get_logger().info(f"=== SERVICE CALL ===")
        self.get_logger().info(f"n={req.n}, max_screws={req.max_screws}")
        self.get_logger().info(f"K=\n{K}")
        self.get_logger().info(f"screws_per_image={list(req.screws_per_image)}")
        self.get_logger().info(f"Total screw_u: {len(req.screw_u)}, screw_v: {len(req.screw_v)}")
        
        # Extract camera positions and select best subset by baseline
        camera_positions = [pose_to_T(pose)[:3, 3] for pose in req.camera_poses]
        M_POSES = 5
        m_poses = min(req.n, M_POSES)  # Use up to M_POSES poses with best baseline spread
        selected_pose_indices = select_poses_by_baseline(camera_positions, m_poses)
        self.get_logger().info(f"Selected {len(selected_pose_indices)} poses: {selected_pose_indices}")
        self.get_logger().info(f"Selected camera positions with distances: {[np.linalg.norm(camera_positions[i] - camera_positions[j]) for i in selected_pose_indices for j in selected_pose_indices if i < j]}")

        # Build rays only from selected camera poses
        rays = []
        idx = 0
        for i in range(req.n):
            T_world_cam = pose_to_T(req.camera_poses[i])
            for j in range(req.screws_per_image[i]):
                u = req.screw_u[idx]
                v = req.screw_v[idx]
                if i in selected_pose_indices:
                    ray = pixel_to_world_ray(u, v, T_world_cam, K, cam_id=i)
                    rays.append(ray)
                    self.get_logger().debug(f"Ray from cam {i}: origin={ray.o}, dir={ray.d}")
                idx += 1

        self.get_logger().info(f"Total rays created: {len(rays)}")
        screws = self.ransac_triangulation(rays, req.max_screws, req.ransac_inlier_thresh_m, req.ransac_iters)

        if not screws:
            resp.success = False
            resp.message = "No screws detected."
            return resp

        for pt, rmse in screws:
            # Position
            resp.screw_positions.append(Point(x=pt[0], y=pt[1], z=pt[2]))
            resp.screw_fit_rmse_m.append(rmse)
            
            # Align EE: Camera Z looking down at screw from dist_m
            cam_pos = pt + np.array([0, 0, dist_m])
            T_world_cam = get_look_at_pose(pt, cam_pos)

            # resp.desired_ee_poses.append(T_to_pose(T_world_ee))

        resp.success = True
        return resp

def main():
    rclpy.init()
    node = ScrewTriangulatorNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
