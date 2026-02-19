#!/usr/bin/env python3
"""
Subscribes to /screw_detector/detections, parses detection+depth+pose,
and calls the localize_screws service on screw_depth_localizer.

Usage:
    ros2 run screw_localizer run_localization
"""
from typing import Dict, List, Optional
import numpy as np
import yaml

import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Header
from geometry_msgs.msg import Pose, Point, PoseArray
from visualization_msgs.msg import Marker, MarkerArray
from screw_interfaces.srv import LocalizeScrews


# ---------------------------------------------------------------------------
# Parsing helpers
# ---------------------------------------------------------------------------

def parse_pose_token(token: str) -> Pose:
    """Parse 'x>0.1;y>0.2;z>0.3;qx>0;qy>0;qz>0;qw>1' into a Pose."""
    values: Dict[str, float] = {}
    for part in token.split(";"):
        if ">" not in part:
            continue
        key, val = part.split(">", 1)
        values[key.strip()] = float(val.strip())

    pose = Pose()
    pose.position.x = values.get("x", 0.0)
    pose.position.y = values.get("y", 0.0)
    pose.position.z = values.get("z", 0.0)
    pose.orientation.x = values.get("qx", 0.0)
    pose.orientation.y = values.get("qy", 0.0)
    pose.orientation.z = values.get("qz", 0.0)
    pose.orientation.w = values.get("qw", 1.0)
    return pose


def parse_detection_string(detection: str) -> Optional[dict]:
    """
    Parse a single detection entry from the screw_detector topic.

    Expected format (one detection):
        class:0, center_x:123.45, center_y:678.90, w:50, h:50,
        conf:0.95, depth:1234.5, pose:x>0.1;y>0.2;z>0.3;qx>0;qy>0;qz>0;qw>1
    """
    fields: Dict[str, str] = {}
    # The pose value contains semicolons but no commas, so splitting on ", "
    # (comma + space) correctly keeps the pose intact as one field.
    for token in detection.split(", "):
        key, _, val = token.partition(":")
        fields[key.strip()] = val.strip()

    try:
        return {
            "cls": int(fields["class"]),
            "u": float(fields["center_x"]),
            "v": float(fields["center_y"]),
            "depth_mm": float(fields["depth"]),
            "conf": float(fields["conf"]),
            "pose": parse_pose_token(fields["pose"]) if fields.get("pose", "N/A") != "N/A" else None,
        }
    except (KeyError, ValueError):
        return None


def parse_detections_message(msg_data: str) -> List[dict]:
    """Split a full detections message (semicolon-separated) into individual dicts."""
    if not msg_data or msg_data.strip() == "no detections":
        return []

    results = []
    for entry in msg_data.split("; "):
        parsed = parse_detection_string(entry.strip())
        if parsed is not None:
            results.append(parsed)
    return results


# ---------------------------------------------------------------------------
# ROS 2 Node
# ---------------------------------------------------------------------------

class RunLocalization(Node):
    def __init__(self, intrinsics: List[float]):
        super().__init__("run_localization")
        self._intrinsics = intrinsics

        # Publisher for screw positions (for downstream processing)
        self._pose_pub = self.create_publisher(
            PoseArray, "screws_from_depth", 10
        )
        # Publisher for RViz-compatible 3-D screw markers
        self._marker_pub = self.create_publisher(
            MarkerArray, "screws_from_depth_markers", 10
        )
        self._frame_id = "world"  # should be the same as the one that pose_getter uses as base frame (iiwa_base or world currently)

        # Service client for screw_depth_localizer
        self._client = self.create_client(LocalizeScrews, "localize_screws")
        self.get_logger().info("Waiting for localize_screws service ...")
        self._client.wait_for_service()
        self.get_logger().info("localize_screws service available.")

        # Subscribe to screw_detector detections
        self._sub = self.create_subscription(
            String,
            "/screw_detector/detections",
            self._detection_callback,
            10,
        )
        self.get_logger().info(
            "Subscribed to /screw_detector/detections -- waiting for messages ..."
        )

    # ---- callback ----------------------------------------------------------

    def _detection_callback(self, msg: String):
        detections = parse_detections_message(msg.data)
        if not detections:
            self.get_logger().info("No detections in this message, skipping.")
            return

        # All detections in one message share the same image / camera pose.
        # Use the pose from the first detection that carries one.
        camera_pose = None
        for det in detections:
            if det["pose"] is not None:
                camera_pose = det["pose"]
                break

        if camera_pose is None:
            self.get_logger().warn(
                "No valid pose in detections (is pose_getter running?). Skipping."
            )
            return

        self.get_logger().info(
            f"Received {len(detections)} detection(s). Calling localize_screws ..."
        )

        # Build service request
        req = LocalizeScrews.Request()
        req.n = 1
        req.intrinsics = self._intrinsics
        req.camera_poses = [camera_pose]
        req.screws_per_image = [len(detections)]
        req.max_screws = len(detections)
        req.ransac_inlier_thresh_m = 0.01
        req.ransac_iters = 100

        req.screw_u = [det["u"] for det in detections]
        req.screw_v = [det["v"] for det in detections]
        # Depth from the detector is in mm; the localizer expects metres.
        req.screw_d = [det["depth_mm"] / 1000.0 for det in detections]

        # Async call so the node keeps spinning while waiting
        future = self._client.call_async(req)
        future.add_done_callback(self._service_response_callback)

    # ---- service response --------------------------------------------------

    def _service_response_callback(self, future):
        try:
            resp = future.result()
        except Exception as exc:
            self.get_logger().error(f"Service call failed: {exc}")
            return

        if not resp.success:
            self.get_logger().warn(f"Localization failed: {resp.message}")
            return

        n_screws = len(resp.screw_positions)
        self.get_logger().info(
            f"Localization succeeded -- {n_screws} screw(s) found:"
        )

        # Build & publish MarkerArray for RViz
        marker_array = MarkerArray()
        stamp = self.get_clock().now().to_msg()

        # First, add a DELETE_ALL marker to clear stale markers
        delete_marker = Marker()
        delete_marker.header = Header(stamp=stamp, frame_id=self._frame_id)
        delete_marker.action = Marker.DELETEALL
        marker_array.markers.append(delete_marker)

        for i, pos in enumerate(resp.screw_positions):
            self.get_logger().info(
                f"  Screw {i}: pos=({pos.x:.4f}, {pos.y:.4f}, {pos.z:.4f})"
            )
            marker = Marker()
            marker.header = Header(stamp=stamp, frame_id=self._frame_id)
            marker.ns = "screws_from_depth"
            marker.id = i
            marker.type = Marker.SPHERE
            marker.action = Marker.ADD
            marker.pose.position = Point(x=pos.x, y=pos.y, z=pos.z)
            marker.pose.orientation.w = 1.0
            marker.scale.x = 0.01  # 1 cm diameter
            marker.scale.y = 0.01
            marker.scale.z = 0.01
            marker.color.r = 0.0
            marker.color.g = 1.0
            marker.color.b = 0.0
            marker.color.a = 1.0
            marker.lifetime.sec = 0  # persistent until next update
            marker_array.markers.append(marker)
        self._marker_pub.publish(marker_array)

        # Publish PoseArray for downstream processing
        pose_array = PoseArray()
        pose_array.header = Header(stamp=stamp, frame_id=self._frame_id)
        for pos in resp.screw_positions:
            p = Pose()
            p.position = Point(x=pos.x, y=pos.y, z=pos.z)
            p.orientation.w = 1.0
            pose_array.poses.append(p)
        self._pose_pub.publish(pose_array)

        self.get_logger().info(
            f"Published {n_screws} screw(s) to /screws_from_depth and /screws_from_depth_markers"
        )


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def load_intrinsics_from_yaml() -> List[float]:
    """Load camera intrinsics from realsense_info.yaml file."""
    import os
    # Try workspace-relative path first
    yaml_path = os.path.join(os.getcwd(), "src/handeye_calibration_ros2/handeye_realsense/realsense_info.yaml")
    
    # If that doesn't exist, try from home
    if not os.path.exists(yaml_path):
        yaml_path = os.path.expanduser("~/ws/restackcell/ws_moveit2/src/handeye_calibration_ros2/handeye_realsense/realsense_info.yaml")
    
    try:
        with open(yaml_path, 'r') as f:
            data = yaml.safe_load(f)
        
        # Extract the K matrix data (row-major 3x3)
        K_data = data['K']['data']
        print(f"Loaded intrinsics from {yaml_path}")
        return K_data
    except Exception as e:
        print(f"Warning: Could not load intrinsics from {yaml_path}: {e}")
        print("Using default RealSense intrinsics")
        # Default RealSense intrinsics as fallback
        return [909.95300569, 0.0, 635.79822139, 0.0, 909.95300569, 385.66617804, 0.0, 0.0, 1.0]


def main():
    intrinsics = load_intrinsics_from_yaml()

    rclpy.init()
    node = RunLocalization(intrinsics)
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()