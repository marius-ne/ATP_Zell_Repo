#!/usr/bin/env python3
"""
ROS2 Python node: screw_detector
Extends your code with:
1) 3D screw estimation (RANSAC + LS refine) from multi-view rays
2) Pose synthesis for an end-effector such that EACH screw is on the camera Z axis
   using known extrinsics: T_ee_cam (camera pose in end-effector frame)

What "on the z axis" means here:
- In the CAMERA frame, the screw should lie on the +Z axis:
    x_cam = 0, y_cam = 0, z_cam > 0
- We generate a desired end-effector pose in WORLD: T_world_ee_des
  such that the camera is looking at the screw and centered.

Assumptions / conventions:
- req.camera_poses are T_world_cam for the N frames used for triangulation.
- Extrinsics are a fixed transform T_ee_cam (camera in EE frame).
  We'll take it from ROS params (recommended) or set a default.
- "Align to z axis" is underdetermined by one point: you can still rotate about z.
  We resolve yaw by using a "world_up" vector (default [0,0,1]) and making camera x/y
  consistent (look-at with up).

You MUST adapt these parts to your stack:
- Service definition: add intrinsics and output ee_poses (Pose[])
- YOLO output parsing: currently stubbed to return (u,v) centers.
"""

import math
import random
from collections import deque
from dataclasses import dataclass
from typing import Deque, List, Optional, Tuple

import numpy as np
import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image
from geometry_msgs.msg import Pose, Point

from cv_bridge import CvBridge
import cv2
import ultralytics

from screw_interfaces.srv import LocalizeScrews  # noqa


# ----------------------- Math utilities -----------------------

@dataclass
class Ray:
    o: np.ndarray  # origin (3,)
    d: np.ndarray  # unit direction (3,)


def quat_to_R(qx: float, qy: float, qz: float, qw: float) -> np.ndarray:
    """Quaternion -> rotation matrix (right-handed)."""
    n = math.sqrt(qx*qx + qy*qy + qz*qz + qw*qw)
    if n == 0.0:
        return np.eye(3)
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
    """Rotation matrix -> quaternion (x,y,z,w)."""
    # Robust conversion
    tr = float(np.trace(R))
    if tr > 0.0:
        S = math.sqrt(tr + 1.0) * 2.0
        qw = 0.25 * S
        qx = (R[2, 1] - R[1, 2]) / S
        qy = (R[0, 2] - R[2, 0]) / S
        qz = (R[1, 0] - R[0, 1]) / S
    else:
        if R[0, 0] > R[1, 1] and R[0, 0] > R[2, 2]:
            S = math.sqrt(1.0 + R[0, 0] - R[1, 1] - R[2, 2]) * 2.0
            qw = (R[2, 1] - R[1, 2]) / S
            qx = 0.25 * S
            qy = (R[0, 1] + R[1, 0]) / S
            qz = (R[0, 2] + R[2, 0]) / S
        elif R[1, 1] > R[2, 2]:
            S = math.sqrt(1.0 + R[1, 1] - R[0, 0] - R[2, 2]) * 2.0
            qw = (R[0, 2] - R[2, 0]) / S
            qx = (R[0, 1] + R[1, 0]) / S
            qy = 0.25 * S
            qz = (R[1, 2] + R[2, 1]) / S
        else:
            S = math.sqrt(1.0 + R[2, 2] - R[0, 0] - R[1, 1]) * 2.0
            qw = (R[1, 0] - R[0, 1]) / S
            qx = (R[0, 2] + R[2, 0]) / S
            qy = (R[1, 2] + R[2, 1]) / S
            qz = 0.25 * S

    # normalize
    n = math.sqrt(qx*qx + qy*qy + qz*qz + qw*qw)
    if n == 0:
        return 0.0, 0.0, 0.0, 1.0
    return qx/n, qy/n, qz/n, qw/n


def pose_to_T_world_cam(p: Pose) -> np.ndarray:
    """Convert Pose to 4x4 transform T_world_cam."""
    R = quat_to_R(p.orientation.x, p.orientation.y, p.orientation.z, p.orientation.w)
    t = np.array([p.position.x, p.position.y, p.position.z], dtype=np.float64)
    T = np.eye(4, dtype=np.float64)
    T[:3, :3] = R
    T[:3, 3] = t
    return T


def T_to_pose(T: np.ndarray) -> Pose:
    """4x4 -> geometry_msgs/Pose."""
    p = Pose()
    p.position.x = float(T[0, 3])
    p.position.y = float(T[1, 3])
    p.position.z = float(T[2, 3])
    qx, qy, qz, qw = R_to_quat(T[:3, :3])
    p.orientation.x = float(qx)
    p.orientation.y = float(qy)
    p.orientation.z = float(qz)
    p.orientation.w = float(qw)
    return p


def invert_T(T: np.ndarray) -> np.ndarray:
    R = T[:3, :3]
    t = T[:3, 3]
    Ti = np.eye(4, dtype=np.float64)
    Ti[:3, :3] = R.T
    Ti[:3, 3] = -R.T @ t
    return Ti


def pixel_to_cam_ray(u: float, v: float, fx: float, fy: float, cx: float, cy: float) -> np.ndarray:
    x = (u - cx) / fx
    y = (v - cy) / fy
    d = np.array([x, y, 1.0], dtype=np.float64)
    d /= (np.linalg.norm(d) + 1e-12)
    return d


def make_world_ray(u: float, v: float, T_world_cam: np.ndarray, fx: float, fy: float, cx: float, cy: float) -> Ray:
    d_cam = pixel_to_cam_ray(u, v, fx, fy, cx, cy)
    R = T_world_cam[:3, :3]
    t = T_world_cam[:3, 3]
    d_world = R @ d_cam
    d_world /= (np.linalg.norm(d_world) + 1e-12)
    return Ray(o=t.copy(), d=d_world)


def closest_point_between_two_rays(r1: Ray, r2: Ray) -> Optional[np.ndarray]:
    o1, d1 = r1.o, r1.d
    o2, d2 = r2.o, r2.d
    w0 = o1 - o2
    a = float(d1 @ d1)
    b = float(d1 @ d2)
    c = float(d2 @ d2)
    d = float(d1 @ w0)
    e = float(d2 @ w0)
    denom = a*c - b*b
    if abs(denom) < 1e-9:
        return None
    s = (b*e - c*d) / denom
    t = (a*e - b*d) / denom
    p1 = o1 + s * d1
    p2 = o2 + t * d2
    return 0.5 * (p1 + p2)


def point_to_ray_distance(x: np.ndarray, r: Ray) -> float:
    v = x - r.o
    perp = v - (v @ r.d) * r.d
    return float(np.linalg.norm(perp))


def refine_point_least_squares(rays: List[Ray]) -> Tuple[np.ndarray, float]:
    A = np.zeros((3, 3), dtype=np.float64)
    b = np.zeros((3,), dtype=np.float64)
    I = np.eye(3, dtype=np.float64)
    for r in rays:
        ddT = np.outer(r.d, r.d)
        M = I - ddT
        A += M
        b += M @ r.o
    x = np.linalg.solve(A + 1e-9*np.eye(3), b)
    dists = np.array([point_to_ray_distance(x, r) for r in rays], dtype=np.float64)
    rmse = float(np.sqrt(np.mean(dists * dists))) if len(dists) else float("inf")
    return x, rmse


def ransac_extract_points_from_rays(
    rays: List[Ray],
    max_points: int,
    inlier_thresh_m: float,
    iters: int,
    min_inliers: int = 6,
) -> List[Tuple[np.ndarray, float, List[int]]]:
    remaining = list(range(len(rays)))
    results: List[Tuple[np.ndarray, float, List[int]]] = []

    for _ in range(max_points):
        if len(remaining) < min_inliers:
            break

        best_inliers: List[int] = []
        best_x: Optional[np.ndarray] = None

        for _k in range(iters):
            i1, i2 = random.sample(remaining, 2)
            x0 = closest_point_between_two_rays(rays[i1], rays[i2])
            if x0 is None:
                continue

            inliers = []
            for idx in remaining:
                if point_to_ray_distance(x0, rays[idx]) <= inlier_thresh_m:
                    inliers.append(idx)

            if len(inliers) > len(best_inliers):
                best_inliers = inliers
                best_x = x0

        if best_x is None or len(best_inliers) < min_inliers:
            break

        x_ref, rmse = refine_point_least_squares([rays[i] for i in best_inliers])
        results.append((x_ref, rmse, best_inliers))
        remaining = [i for i in remaining if i not in set(best_inliers)]

    return results


# ----------------------- "Look-at" pose synthesis -----------------------

def normalize(v: np.ndarray) -> np.ndarray:
    n = np.linalg.norm(v)
    if n < 1e-12:
        return v
    return v / n


def look_at_R_world_cam(cam_pos_w: np.ndarray, target_w: np.ndarray, world_up: np.ndarray) -> np.ndarray:
    """
    Construct R_world_cam such that camera +Z points from camera to target.
    We enforce right-handed camera frame with:
      z_cam (in world) = forward = normalize(target - cam_pos)
      x_cam (in world) = normalize(world_up x z_cam)
      y_cam (in world) = z_cam x x_cam
    This fixes the roll/yaw about z using world_up.
    """
    z_w = normalize(target_w - cam_pos_w)  # camera +Z axis in world
    if np.linalg.norm(z_w) < 1e-9:
        return np.eye(3)
    x_w = np.cross(world_up, z_w)
    if np.linalg.norm(x_w) < 1e-9:
        # world_up parallel to z -> pick alternative up
        alt_up = np.array([0.0, 1.0, 0.0], dtype=np.float64)
        x_w = np.cross(alt_up, z_w)
    x_w = normalize(x_w)
    y_w = normalize(np.cross(z_w, x_w))
    # Columns are basis vectors of cam axes expressed in world
    R_world_cam = np.column_stack([x_w, y_w, z_w])
    return R_world_cam


def desired_ee_pose_for_screw(
    screw_w: np.ndarray,
    T_ee_cam: np.ndarray,
    approach_dist_m: float,
    world_up: np.ndarray = np.array([0.0, 0.0, 1.0], dtype=np.float64),
) -> np.ndarray:
    """
    Compute T_world_ee_des so that the camera optical axis (+Z_cam) points to screw and screw lies on z axis.
    We position the camera at:
      cam_pos = screw - approach_dist * z_w
    where z_w points from cam to screw.

    Then:
      T_world_cam_des = [R_world_cam, cam_pos]
      T_world_ee_des = T_world_cam_des * inv(T_ee_cam)
    """
    # Choose camera position behind the screw along viewing direction
    # (initially pick a direction; we compute R from look-at which sets z_w)
    # We'll iterate once: assume z_w from a temporary camera position.
    # Use a default initial direction: +Z_world
    z_guess = np.array([0.0, 0.0, 1.0], dtype=np.float64)
    cam_pos = screw_w - approach_dist_m * z_guess

    R_world_cam = look_at_R_world_cam(cam_pos, screw_w, world_up)
    z_w = R_world_cam[:, 2]  # updated forward axis
    cam_pos = screw_w - approach_dist_m * z_w  # recompute with consistent forward direction
    R_world_cam = look_at_R_world_cam(cam_pos, screw_w, world_up)

    T_world_cam = np.eye(4, dtype=np.float64)
    T_world_cam[:3, :3] = R_world_cam
    T_world_cam[:3, 3] = cam_pos

    T_world_ee = T_world_cam @ invert_T(T_ee_cam)
    return T_world_ee


# ----------------------- Node -----------------------

class ScrewDetectorNode(Node):
    def __init__(self):
        super().__init__("screw_detector")

        # --- Params: topics ---
        self.declare_parameter("image_topic", "/camera/image_raw")
        image_topic = self.get_parameter("image_topic").get_parameter_value().string_value

        self.bridge = CvBridge()
        self.image_sub = self.create_subscription(Image, image_topic, self._on_image, 10)
        self._img_buf: Deque[Image] = deque(maxlen=400)

        # --- Params: extrinsics T_ee_cam (camera in EE frame) ---
        # Provide as 16 floats row-major, representing a 4x4 homogeneous transform.
        # Example:
        # ros2 param set /screw_detector T_ee_cam "[1,0,0,0.02, 0,1,0,0.00, 0,0,1,0.10, 0,0,0,1]"
        self.declare_parameter("T_ee_cam", [1.0, 0.0, 0.0, 0.0,
                                           0.0, 1.0, 0.0, 0.0,
                                           0.0, 0.0, 1.0, 0.0,
                                           0.0, 0.0, 0.0, 1.0])
        self.declare_parameter("approach_dist_m", 0.25)  # how far camera should be from screw along its z axis
        self.declare_parameter("world_up", [0.0, 0.0, 1.0])

        # Service
        self.srv = self.create_service(LocalizeScrews, "detect_screws", self._on_detect_screws)
        self.get_logger().info(f"screw_detector ready. Subscribed to {image_topic}, service /detect_screws")

        # Load model
        self.model = ultralytics.YOLO("weights.pt")

    def _on_image(self, msg: Image):
        self._img_buf.append(msg)

    def detect_screws_2d(self, bgr: np.ndarray) -> List[Tuple[float, float]]:
        """
        Parse Ultralytics detections into list of (u,v) pixel centers.
        You MUST adapt class filtering to your model.
        """
        # Ultralytics returns list of Results
        results = self.model.predict(bgr, verbose=False)
        if not results:
            return []

        r = results[0]
        if r.boxes is None or len(r.boxes) == 0:
            return []

        dets_uv: List[Tuple[float, float]] = []
        # r.boxes.xyxy is Nx4 tensor on CPU/GPU; convert to numpy
        xyxy = r.boxes.xyxy.cpu().numpy()
        conf = r.boxes.conf.cpu().numpy() if r.boxes.conf is not None else None
        cls = r.boxes.cls.cpu().numpy() if r.boxes.cls is not None else None

        for i in range(xyxy.shape[0]):
            # Optional: filter by class id == screw_class_id
            # if cls is not None and int(cls[i]) != 0:
            #     continue
            # Optional: filter by confidence
            if conf is not None and float(conf[i]) < 0.25:
                continue
            x1, y1, x2, y2 = xyxy[i]
            u = 0.5 * (float(x1) + float(x2))
            v = 0.5 * (float(y1) + float(y2))
            dets_uv.append((u, v))

        return dets_uv

    def _on_detect_screws(self, req: LocalizeScrews.Request, resp: LocalizeScrews.Response):
        n = int(req.n)
        poses = list(req.camera_poses)
        max_screws = int(req.max_screws) if req.max_screws > 0 else 5
        inlier_thresh_m = float(req.ransac_inlier_thresh_m) if req.ransac_inlier_thresh_m > 0 else 0.01
        iters = int(req.ransac_iters) if req.ransac_iters > 0 else 600

        # intrinsics from request: you used req.intrinsics; I assume it's a 3x3 float array
        # If your srv uses float64[9] intrinsics, adapt accordingly.
        K = np.array(req.intrinsics, dtype=np.float64).reshape(3, 3)
        fx, fy, cx, cy = float(K[0, 0]), float(K[1, 1]), float(K[0, 2]), float(K[1, 2])

        if n <= 1:
            resp.success = False
            resp.message = "n must be >= 2"
            return resp
        if len(poses) != n:
            resp.success = False
            resp.message = f"camera_poses length must equal n (got {len(poses)} vs n={n})"
            return resp

        # Capture next N frames after the request
        captured: List[Image] = []
        start_len = len(self._img_buf)
        timeout_s = 5.0
        t0 = self.get_clock().now()
        while len(captured) < n:
            if len(self._img_buf) > start_len + len(captured):
                msg = list(self._img_buf)[start_len + len(captured)]
                captured.append(msg)
                continue

            if (self.get_clock().now() - t0).nanoseconds * 1e-9 > timeout_s:
                resp.success = False
                resp.message = f"Timeout waiting for {n} new frames (got {len(captured)})"
                return resp
            rclpy.spin_once(self, timeout_sec=0.01)

        # Build rays from detections
        rays: List[Ray] = []
        num_dets_per_frame: List[int] = []
        for i in range(n):
            img_msg = captured[i]
            T_world_cam = pose_to_T_world_cam(poses[i])

            try:
                bgr = self.bridge.imgmsg_to_cv2(img_msg, desired_encoding="bgr8")
            except Exception as e:
                resp.success = False
                resp.message = f"cv_bridge conversion failed: {e}"
                return resp

            dets_uv = self.detect_screws_2d(bgr)
            num_dets_per_frame.append(len(dets_uv))

            for (u, v) in dets_uv:
                rays.append(make_world_ray(u, v, T_world_cam, fx, fy, cx, cy))

        if len(rays) < 2:
            resp.success = False
            resp.message = f"No detections / insufficient rays. Dets per frame: {num_dets_per_frame}"
            return resp

        # Extract screw 3D points
        min_inliers = max(6, n)  # heuristic
        extracted = ransac_extract_points_from_rays(
            rays=rays,
            max_points=max_screws,
            inlier_thresh_m=inlier_thresh_m,
            iters=iters,
            min_inliers=min_inliers,
        )

        if not extracted:
            resp.success = False
            resp.message = f"RANSAC found no stable 3D points. rays={len(rays)}, dets/frame={num_dets_per_frame}"
            return resp

        # Load extrinsics + approach settings
        T_ee_cam_list = self.get_parameter("T_ee_cam").value
        if len(T_ee_cam_list) != 16:
            resp.success = False
            resp.message = "Param T_ee_cam must have 16 floats (row-major 4x4)."
            return resp
        T_ee_cam = np.array(T_ee_cam_list, dtype=np.float64).reshape(4, 4)

        approach_dist_m = float(self.get_parameter("approach_dist_m").value)
        world_up = np.array(self.get_parameter("world_up").value, dtype=np.float64).reshape(3,)

        # Fill response: 3D positions + desired EE poses
        resp.success = True
        resp.message = (
            f"OK. Frames={n}, total_rays={len(rays)}, dets_per_frame={num_dets_per_frame}, "
            f"points={len(extracted)}"
        )

        resp.screw_positions = []
        resp.screw_fit_rmse_m = []

        # YOU MUST add this field to srv response:
        # geometry_msgs/Pose[] desired_ee_poses
        resp.desired_ee_poses = []

        for (x, rmse, _inliers) in extracted:
            # screw position
            p = Point()
            p.x, p.y, p.z = float(x[0]), float(x[1]), float(x[2])
            resp.screw_positions.append(p)
            resp.screw_fit_rmse_m.append(float(rmse))

            # compute desired EE pose
            T_world_ee_des = desired_ee_pose_for_screw(
                screw_w=x,
                T_ee_cam=T_ee_cam,
                approach_dist_m=approach_dist_m,
                world_up=world_up,
            )
            resp.desired_ee_poses.append(T_to_pose(T_world_ee_des))

        return resp


def main():
    rclpy.init()
    node = ScrewDetectorNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
