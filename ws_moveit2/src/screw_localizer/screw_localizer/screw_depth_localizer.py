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

# ==============================================================================
# 2. ROS NODE
# ==============================================================================

class ScrewDepthLocalizer(Node):
    def __init__(self):
        super().__init__("screw_depth_localizer")
        self.srv = self.create_service(LocalizeScrews, "localize_screws", self.handle_service)
        self.get_logger().info("Screw Depth Localizer Node Ready")

    def handle_service(self, req, resp):
        """
        Single-view depth-based screw localization.
        Returns 3D world-frame screw positions.
        """
        K = np.array(req.intrinsics).reshape(3, 3)

        n_views = req.n
        assert n_views == 1, (
            "Currently only supports n=1 (single view). "
            "For multi-view, use screw_triangulator."
        )

        # The request carries the EE pose; convert to camera pose
        T_world_cam = pose_to_T(req.camera_poses[0])

        screw_detections = req.screws_per_image[0]
        self.get_logger().info(
            f"Service call: {screw_detections} detection(s), "
            f"cam origin={T_world_cam[:3, 3]}"
        )

        screws = []
        for j in range(screw_detections):
            u = req.screw_u[j]
            v = req.screw_v[j]
            depth = req.screw_d[j]

            # Build ray in world frame and project along it by depth
            ray = pixel_to_world_ray(u, v, T_world_cam, K)
            point = ray.o + depth * ray.d
            screws.append(point)

        if not screws:
            resp.success = False
            resp.message = "No screws detected in current frame."
            return resp

        for pt in screws:
            resp.screw_positions.append(
                Point(x=float(pt[0]), y=float(pt[1]), z=float(pt[2]))
            )

        resp.success = True
        resp.message = f"Localized {len(screws)} screw(s)."
        return resp


def main():
    rclpy.init()
    node = ScrewDepthLocalizer()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
    