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
from visualization_msgs.msg import Marker, MarkerArray
from std_msgs.msg import ColorRGBA, Header

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
        self.marker_pub = self.create_publisher(MarkerArray, "screw_rays", 10)
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
        rays = []
        for j in range(screw_detections):
            u = req.screw_u[j]
            v = req.screw_v[j]
            depth = req.screw_d[j]

            # Build ray in world frame and project along it by depth
            ray = pixel_to_world_ray(u, v, T_world_cam, K)
            point = ray.o + depth * ray.d
            screws.append(point)
            rays.append(ray)

        # Publish ray visualization
        self._publish_ray_markers(rays)

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

    def _publish_ray_markers(self, rays: List[Ray], ray_length: float = 1.0):
        """Publish MarkerArray visualizing 1m rays from camera origin for each screw."""
        marker_array = MarkerArray()
        stamp = self.get_clock().now().to_msg()

        # First, publish a DELETE_ALL marker to clear previous rays
        delete_marker = Marker()
        delete_marker.header = Header(stamp=stamp, frame_id="world")
        delete_marker.action = Marker.DELETEALL
        marker_array.markers.append(delete_marker)

        for i, ray in enumerate(rays):
            marker = Marker()
            marker.header = Header(stamp=stamp, frame_id="world")
            marker.ns = "screw_rays"
            marker.id = i
            marker.type = Marker.ARROW
            marker.action = Marker.ADD

            # Arrow defined by start and end points
            start = Point(
                x=float(ray.o[0]),
                y=float(ray.o[1]),
                z=float(ray.o[2]),
            )
            end_pt = ray.o + ray_length * ray.d
            end = Point(
                x=float(end_pt[0]),
                y=float(end_pt[1]),
                z=float(end_pt[2]),
            )
            marker.points = [start, end]

            # Shaft and head diameter
            marker.scale.x = 0.005  # shaft diameter
            marker.scale.y = 0.01   # head diameter
            marker.scale.z = 0.015  # head length

            # Colour: cyan, fully opaque
            marker.color = ColorRGBA(r=0.0, g=1.0, b=1.0, a=1.0)
            marker.lifetime.sec = 30  # auto-expire after 30s

            marker_array.markers.append(marker)

        self.marker_pub.publish(marker_array)
        self.get_logger().info(f"Published {len(rays)} ray marker(s) on /screw_rays")


def main():
    rclpy.init()
    node = ScrewDepthLocalizer()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
    