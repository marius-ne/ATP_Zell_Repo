#!/usr/bin/env python3
"""
Subscribes to /screw_detector/detections, parses detection+depth+pose,
and calls the detect_screws service on screw_depth_localizer.

Usage:
    python3 run_localization.py                        # uses default RealSense intrinsics
    python3 run_localization.py --K "909.95300569, 0.0, 635.79822139, 0.0, 909.95300569, 385.66617804, 0.0, 0.0, 1.0"
"""
import argparse
from typing import Dict, List, Optional
import numpy as np

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from geometry_msgs.msg import Pose
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

        # Service client for screw_depth_localizer
        self._client = self.create_client(LocalizeScrews, "detect_screws")
        self.get_logger().info("Waiting for detect_screws service ...")
        self._client.wait_for_service()
        self.get_logger().info("detect_screws service available.")

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
            f"Received {len(detections)} detection(s). Calling detect_screws ..."
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

        self.get_logger().info(
            f"Localization succeeded -- {len(resp.screw_positions)} screw(s) found:"
        )
        for i, pos in enumerate(resp.screw_positions):
            self.get_logger().info(
                f"  Screw {i}: pos=({pos.x:.4f}, {pos.y:.4f}, {pos.z:.4f})"
            )


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(
        description="Run screw localization from live detections"
    )
    parser.add_argument("--K", type=str, default="909.95300569, 0.0, 635.79822139, 0.0, 909.95300569, 385.66617804, 0.0, 0.0, 1.0", help="Intrinsics matrix as [[fx, 0, cx], [0, fy, cy], [0, 0, 1]] flattened row-major")
    args = parser.parse_args()

    intrinsics = [float(x.strip()) for x in args.K.split(",")]
    intrinsics = np.array(intrinsics).reshape(3, 3)

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