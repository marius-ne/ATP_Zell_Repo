#!/usr/bin/env python3
import numpy as np
import random
from typing import List, Tuple, Optional
import os
import cv2

import rclpy
from rclpy.node import Node
from scipy.spatial.transform import Rotation as R
from scipy.optimize import least_squares
from ament_index_python.packages import get_package_share_directory
from ultralytics import YOLO
from cv_bridge import CvBridge

from geometry_msgs.msg import Pose, Point
from realsense2_camera_msgs.msg import RGBD
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

class ScrewDepthLocalizer(Node):
    def __init__(self):
        super().__init__("screw_depth_localizer")
        
        # Parameters
        self.declare_parameter("T_ee_cam", np.eye(4).flatten().tolist())
        self.declare_parameter("approach_dist_m", 0.25)
        self.declare_parameter("fx", 916.3)
        self.declare_parameter("fy", 916.3)
        self.declare_parameter("cx", 640.0)
        self.declare_parameter("cy", 360.0)
        
        # Get parameters
        self.T_ee_cam = np.array(self.get_parameter("T_ee_cam").value).reshape(4, 4)
        self.approach_dist_m = self.get_parameter("approach_dist_m").value
        fx = self.get_parameter("fx").value
        fy = self.get_parameter("fy").value
        cx = self.get_parameter("cx").value
        cy = self.get_parameter("cy").value
        
        self.K = np.array([
            [fx, 0, cx],
            [0, fy, cy],
            [0, 0, 1]
        ])
        
        # Load YOLO model
        pkg_share = get_package_share_directory('screw_detector')
        weights_path = os.path.join(pkg_share, 'weights', 'best.pt')
        self.model = YOLO(weights_path)
        self.bridge = CvBridge()
        
        # Subscribe to RGBD camera feed
        self.rgbd_subscription = self.create_subscription(
            RGBD,
            '/camera/camera/rgbd',
            self._rgbd_callback,
            1
        )
        
        # Store latest RGBD frame
        self.latest_rgb = None
        self.latest_depth = None
        
        # Create service
        self.srv = self.create_service(LocalizeScrews, "detect_screws", self.handle_service)
        self.get_logger().info("Screw Depth Localizer Node Ready")

    def _rgbd_callback(self, msg: RGBD):
        """Cache the latest RGBD frame"""
        try:
            self.latest_rgb = self.bridge.imgmsg_to_cv2(msg.rgb, desired_encoding='bgr8')
            self.latest_depth = self.bridge.imgmsg_to_cv2(msg.depth, desired_encoding='16UC1')
        except Exception as e:
            self.get_logger().error(f'Could not convert RGBD image: {e}')

    def handle_service(self, req, resp):
        """
        Service handler: receives start request, detects screws, and returns their 3D positions.
        """
        if self.latest_rgb is None or self.latest_depth is None:
            resp.success = False
            resp.message = "No RGBD frame available. Ensure camera is publishing."
            return resp
        
        self.get_logger().info("=== SERVICE CALL: Localizing Screws ===")
        
        # Run YOLO detection on latest frame
        results = self.model(self.latest_rgb)
        
        screws = []
        # Extract detection info
        for result in results:
            for obj in result.boxes:
                cls = int(obj.cls[0])
                conf = float(obj.conf[0])
                center_x, center_y, width, height = obj.xywh[0]
                
                # Get depth value (in mm) at detection center
                depth_mm = self.latest_depth[int(center_y), int(center_x)]
                depth_m = depth_mm / 1000.0  # Convert to meters
                
                if depth_m <= 0:
                    self.get_logger().warning(f"Invalid depth {depth_mm}mm at ({center_x:.1f}, {center_y:.1f})")
                    continue
                
                # Convert pixel + depth to 3D point in camera frame
                fx, fy, cx, cy = self.K[0, 0], self.K[1, 1], self.K[0, 2], self.K[1, 2]
                x_cam = (center_x - cx) / fx * depth_m
                y_cam = (center_y - cy) / fy * depth_m
                z_cam = depth_m
                
                point_cam = np.array([x_cam, y_cam, z_cam])
                
                # Transform to world frame (assuming camera frame = world frame for now)
                # In a full setup, you would use T_world_cam from robot state
                point_world = point_cam
                
                screws.append(point_world)
                self.get_logger().info(f"Detected screw at world position: {point_world}")
        
        if not screws:
            resp.success = False
            resp.message = "No screws detected in current frame."
            return resp
        
        # Generate approach poses for each detected screw
        for pt in screws:
            # Screw position
            resp.screw_positions.append(Point(x=pt[0], y=pt[1], z=pt[2]))
            resp.screw_fit_rmse_m.append(0.0)  # Single-view, no triangulation error
            
            # Desired EE pose: approach from above (camera Z pointing down at screw)
            approach_height = self.approach_dist_m
            cam_pos = pt + np.array([0, 0, approach_height])
            T_world_cam = get_look_at_pose(pt, cam_pos)
            T_world_ee = T_world_cam @ np.linalg.inv(self.T_ee_cam)
            resp.desired_ee_poses.append(T_to_pose(T_world_ee))
        
        resp.success = True
        resp.message = f"Localized {len(screws)} screw(s)."
        self.get_logger().info(resp.message)
        return resp


def main():
    rclpy.init()
    node = ScrewDepthLocalizer()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
    