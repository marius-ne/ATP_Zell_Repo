#!/usr/bin/env python3
from dataclasses import dataclass
from typing import Dict, List, Optional

import numpy as np
import rclpy
from geometry_msgs.msg import Pose
from rclpy.node import Node

from screw_interfaces.srv import LocalizeScrews


@dataclass
class DetectionRow:
    timestamp: str
    u: float
    v: float
    pose: Pose


def _parse_pose_token(token: str) -> Pose:
    values: Dict[str, float] = {}
    parts = token.split(";")
    for part in parts:
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


def _split_row(line: str) -> List[str]:
    if "," in line:
        return [t for t in line.strip().split(",") if t]
    raise ValueError("Unsupported CSV format: no commas found")


def load_detections(csv_path: str) -> Dict[str, List[DetectionRow]]:
    groups: Dict[str, List[DetectionRow]] = {}

    with open(csv_path, "r", encoding="utf-8") as f:
        lines = [ln for ln in (l.rstrip("\n") for l in f) if ln.strip()]

    if not lines:
        return groups

    header_tokens = _split_row(lines[0])
    has_header = header_tokens and header_tokens[0].lower() == "timestamp"
    data_lines = lines[1:] if has_header else lines

    for line in data_lines:
        tokens = _split_row(line)
        if len(tokens) < 9:
            continue

        timestamp = tokens[0]
        # tokens[1] = class
        u = float(tokens[2])
        v = float(tokens[3])
        pose_token = tokens[8]
        pose = _parse_pose_token(pose_token)

        groups.setdefault(timestamp, []).append(DetectionRow(timestamp, u, v, pose))

    return groups


def build_request(
    detections_by_image: Dict[str, List[DetectionRow]],
    k_matrix: List[float],
    max_screws: int,
    inlier_thresh_m: float,
    ransac_iters: int,
) -> LocalizeScrews.Request:
    req = LocalizeScrews.Request()
    req.intrinsics = k_matrix
    req.max_screws = int(max_screws)
    req.ransac_inlier_thresh_m = float(inlier_thresh_m)
    req.ransac_iters = int(ransac_iters)

    image_groups = list(detections_by_image.values())
    req.n = len(image_groups)
    req.camera_poses = [group[0].pose for group in image_groups]
    req.screws_per_image = [len(group) for group in image_groups]

    screw_u: List[float] = []
    screw_v: List[float] = []
    for group in image_groups:
        for det in group:
            screw_u.append(float(det.u))
            screw_v.append(float(det.v))

    req.screw_u = screw_u
    req.screw_v = screw_v

    return req


def call_localizer(
    node: Node,
    client: rclpy.client.Client,
    detections_by_image: Dict[str, List[DetectionRow]],
    k_matrix: List[float],
    max_screws: int,
    inlier_thresh_m: float,
    ransac_iters: int,
) -> Optional[LocalizeScrews.Response]:
    if not detections_by_image:
        return None

    req = build_request(detections_by_image, k_matrix, max_screws, inlier_thresh_m, ransac_iters)
    future = client.call_async(req)
    rclpy.spin_until_future_complete(node, future)
    return future.result()


def format_pose(pose: Pose) -> str:
    return (
        f"pos=({pose.position.x:.4f}, {pose.position.y:.4f}, {pose.position.z:.4f}) "
        f"quat=({pose.orientation.x:.4f}, {pose.orientation.y:.4f}, "
        f"{pose.orientation.z:.4f}, {pose.orientation.w:.4f})"
    )


def visualize_result(
    response: LocalizeScrews.Response,
    detections_by_image: Dict[str, List[DetectionRow]],
) -> None:
    if response is None or not response.success:
        return

    try:
        import matplotlib.pyplot as plt
    except Exception as exc:
        print(f"Visualization skipped (matplotlib unavailable): {exc}")
        return

    camera_positions = []
    for group in detections_by_image.values():
        pose = group[0].pose
        camera_positions.append((pose.position.x, pose.position.y, pose.position.z))

    screw_positions = [(p.x, p.y, p.z) for p in response.screw_positions]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")

    if camera_positions:
        cx, cy, cz = zip(*camera_positions)
        ax.scatter(cx, cy, cz, c="tab:blue", label="camera poses")

    if screw_positions:
        sx, sy, sz = zip(*screw_positions)
        ax.scatter(sx, sy, sz, c="tab:red", marker="x", s=60, label="screws")

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")
    ax.set_title("Screw localization result")
    ax.legend()
    ax.axis("auto")
    plt.tight_layout()
    plt.show()


def run_localizer_from_csv(
    csv_path: str,
    fx: float,
    fy: float,
    cx: float,
    cy: float,
    timestamp: Optional[str] = None,
    max_screws: int = 5,
    inlier_thresh_m: float = 0.01,
    ransac_iters: int = 100,
    service: str = "detect_screws",
    visualize: bool = False,
) -> Optional[LocalizeScrews.Response]:
    k_matrix = [
        fx, 0.0, cx,
        0.0, fy, cy,
        0.0, 0.0, 1.0,
    ]

    groups = load_detections(csv_path)
    if timestamp:
        if timestamp not in groups:
            raise ValueError(f"Timestamp {timestamp} not found in CSV")
        groups = {timestamp: groups[timestamp]}

    visualize_camera_poses(groups)

    rclpy.init()
    node = rclpy.create_node("csv_screw_localizer")
    client = node.create_client(LocalizeScrews, service)

    if not client.wait_for_service(timeout_sec=5.0):
        node.get_logger().error(f"Service {service} not available")
        rclpy.shutdown()
        raise RuntimeError("LocalizeScrews service not available")

    resp = call_localizer(
        node,
        client,
        groups,
        k_matrix,
        max_screws,
        inlier_thresh_m,
        ransac_iters,
    )

    rclpy.shutdown()

    if visualize:
        visualize_result(resp, groups)

    return resp


def visualize_camera_poses(
    detections_by_image: Dict[str, List[DetectionRow]],
) -> None:
    """Visualize camera poses with their orientations as coordinate frames."""
    try:
        import matplotlib.pyplot as plt
        from mpl_toolkits.mplot3d import Axes3D
        from scipy.spatial.transform import Rotation as R
    except Exception as exc:
        print(f"Camera pose visualization skipped (dependencies unavailable): {exc}")
        return

    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection="3d")

    frame_scale = 0.05

    xs = []
    ys = []
    zs = []
    for i, group in enumerate(detections_by_image.values()):
        pose = group[0].pose
        pos = [pose.position.x, pose.position.y, pose.position.z]
        quat = [pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w]
        xs.append(pos[0])
        ys.append(pos[1])
        zs.append(pos[2])

        # Plot camera position
        ax.scatter(*pos, c="tab:blue", s=50)

        # Get rotation matrix to draw coordinate frame axes
        rot = R.from_quat(quat).as_matrix()
        x_axis = rot[:, 0] * frame_scale
        y_axis = rot[:, 1] * frame_scale
        z_axis = rot[:, 2] * frame_scale

        # Draw coordinate frame axes (red=X, green=Y, blue=Z)
        ax.quiver(pos[0], pos[1], pos[2], x_axis[0], x_axis[1], x_axis[2], color="r", arrow_length_ratio=0.1, linewidth=3)
        ax.quiver(pos[0], pos[1], pos[2], y_axis[0], y_axis[1], y_axis[2], color="g", arrow_length_ratio=0.1, linewidth=3)
        ax.quiver(pos[0], pos[1], pos[2], z_axis[0], z_axis[1], z_axis[2], color="b", arrow_length_ratio=0.1, linewidth=3)

        ax.text(pos[0], pos[1], pos[2], f"  img{i}", fontsize=8)

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")
    ax.set_title("Camera poses with orientations")
    ax.set_box_aspect((np.ptp(xs), np.ptp(ys), np.ptp(zs))) 
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    K = [ 909.95300569, 0., 635.79822139, 0., 909.95300569, 385.66617804, 0., 0., 1. ]
    response = run_localizer_from_csv(
        csv_path="/home/remanpilot/ATP25_26_Gruppe6_Entschraubung/detector_payload/20260213_171657/_screw_detections.csv",
        fx=K[0],
        fy=K[4],
        cx=K[2],
        cy=K[5],
        timestamp=None,
        max_screws=5,
        inlier_thresh_m=0.05,
        ransac_iters=100,
        visualize=True,
    )
    print(response)
