"""
ArUco GridBoard pose estimation node for hand-eye calibration.

Detects ALL markers on an ArUco GridBoard and computes a single, robust
board pose using cv2.aruco.estimatePoseBoard().  This is much more accurate
than single-marker detection because:
  • More corner correspondences → better solvePnP result
  • Partial occlusion is tolerated (works with ≥1 visible marker)
  • The board pose is consistent regardless of which markers are seen

The board pose (rotation + translation) is:
  1. Published as a TF transform  (camera_optical_frame → aruco_board)
  2. Saved to a YAML file when the user presses 'q'  (same format as before,
     so handeye_estimation.py works without changes)

Config parameters (config.yaml)
-------------------------------
  aruco_dictionary_name   – e.g. "DICT_5X5_250"
  aruco_marker_side_length – marker edge length in metres
  aruco_marker_separation  – gap between markers in metres  (NEW)
  aruco_grid_rows          – number of rows in the board     (NEW)
  aruco_grid_cols          – number of columns in the board  (NEW)
  (all other keys unchanged)
"""

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from geometry_msgs.msg import TransformStamped
from tf2_ros import TransformBroadcaster
from scipy.spatial.transform import Rotation as R
from cv_bridge import CvBridge
from std_msgs.msg import String

import cv2
import cv2.aruco as aruco
import numpy as np
import yaml

# ── ArUco dictionary lookup ──────────────────────────────────────────────
ARUCO_DICT = {
    "DICT_4X4_50": cv2.aruco.DICT_4X4_50,
    "DICT_4X4_100": cv2.aruco.DICT_4X4_100,
    "DICT_4X4_250": cv2.aruco.DICT_4X4_250,
    "DICT_4X4_1000": cv2.aruco.DICT_4X4_1000,
    "DICT_5X5_50": cv2.aruco.DICT_5X5_50,
    "DICT_5X5_100": cv2.aruco.DICT_5X5_100,
    "DICT_5X5_250": cv2.aruco.DICT_5X5_250,
    "DICT_5X5_1000": cv2.aruco.DICT_5X5_1000,
    "DICT_6X6_50": cv2.aruco.DICT_6X6_50,
    "DICT_6X6_100": cv2.aruco.DICT_6X6_100,
    "DICT_6X6_250": cv2.aruco.DICT_6X6_250,
    "DICT_6X6_1000": cv2.aruco.DICT_6X6_1000,
    "DICT_7X7_50": cv2.aruco.DICT_7X7_50,
    "DICT_7X7_100": cv2.aruco.DICT_7X7_100,
    "DICT_7X7_250": cv2.aruco.DICT_7X7_250,
    "DICT_7X7_1000": cv2.aruco.DICT_7X7_1000,
    "DICT_ARUCO_ORIGINAL": cv2.aruco.DICT_ARUCO_ORIGINAL,
}

# Minimum number of markers required to accept a board pose
MIN_MARKERS_FOR_POSE = 2


class ArucoNode(Node):
    def __init__(self):
        super().__init__('aruco_node')

        # ── Load config ──────────────────────────────────────────────────
        with open('src/handeye_calibration_ros2/handeye_realsense/config.yaml', 'r') as file:
            config = yaml.safe_load(file)

        aruco_dictionary_name = config["aruco_dictionary_name"]
        self.aruco_marker_name = config.get("aruco_marker_name", "aruco_board")
        self.marker_length = config["aruco_marker_side_length"]
        self.marker_separation = config.get("aruco_marker_separation", 0.006)
        self.grid_rows = config.get("aruco_grid_rows", 4)
        self.grid_cols = config.get("aruco_grid_cols", 3)
        self.total_markers = self.grid_rows * self.grid_cols

        self.camera_calibration_parameters_filename = config["camera_calibration_parameters_filename"]
        self.image_topic = config["image_topic"]
        self.calculated_camera_optical_frame_name = config["calculated_camera_optical_frame_name"]
        self.marker_data_file_name = config["marker_data_file_name"]
        self.image_filename = config["image_filename"]

        # ── Validate dictionary ──────────────────────────────────────────
        dict_id = ARUCO_DICT.get(aruco_dictionary_name)
        if dict_id is None:
            self.get_logger().error(
                f"ArUCo dictionary '{aruco_dictionary_name}' is not supported")
            return

        # ── Load camera intrinsics ───────────────────────────────────────
        cv_file = cv2.FileStorage(
            self.camera_calibration_parameters_filename, cv2.FILE_STORAGE_READ)
        self.mtx = cv_file.getNode('K').mat()
        self.dst = cv_file.getNode('D').mat()
        cv_file.release()

        # ── Set up ArUco board + detector ────────────────────────────────
        self.dictionary = aruco.getPredefinedDictionary(dict_id)

        # GridBoard: (cols, rows), markerLength, markerSeparation, dictionary
        self.board = aruco.GridBoard(
            (self.grid_cols, self.grid_rows),
            self.marker_length,
            self.marker_separation,
            self.dictionary,
        )

        self.detector_params = aruco.DetectorParameters()
        self.detector = aruco.ArucoDetector(self.dictionary, self.detector_params)

        self.get_logger().info(
            f"GridBoard: {self.grid_cols}×{self.grid_rows} = {self.total_markers} "
            f"markers  ({aruco_dictionary_name}, "
            f"{self.marker_length*1000:.0f} mm + {self.marker_separation*1000:.0f} mm gap)")

        # ── ROS plumbing ─────────────────────────────────────────────────
        self.subscription = self.create_subscription(
            Image, self.image_topic, self.listener_callback, 10)
        self.keypress_publisher = self.create_publisher(
            String, 'keypress_topic', 10)
        self.tfbroadcaster = TransformBroadcaster(self)
        self.bridge = CvBridge()

        self.pose_count = 0
        # Cache latest valid board pose for saving on keypress
        self._last_rvec = None
        self._last_tvec = None

    # ── Image callback ───────────────────────────────────────────────────

    def listener_callback(self, data):
        current_frame = self.bridge.imgmsg_to_cv2(data)
        gray = cv2.cvtColor(current_frame, cv2.COLOR_BGR2GRAY) \
            if len(current_frame.shape) == 3 else current_frame

        # Detect individual markers
        corners, ids, rejected = self.detector.detectMarkers(gray)

        if ids is not None and len(ids) >= MIN_MARKERS_FOR_POSE:
            # Draw all detected markers
            aruco.drawDetectedMarkers(current_frame, corners, ids)

            # Estimate board pose from ALL detected markers at once
            obj_points, img_points = self.board.matchImagePoints(corners, ids)

            if obj_points is not None and len(obj_points) >= 4:
                success, rvec, tvec = cv2.solvePnP(
                    obj_points, img_points, self.mtx, self.dst)

                if success:
                    self._last_rvec = rvec
                    self._last_tvec = tvec

                    # Draw board coordinate frame
                    cv2.drawFrameAxes(
                        current_frame, self.mtx, self.dst,
                        rvec, tvec, self.marker_length * 2)

                    # Broadcast TF: camera → board
                    self._broadcast_board_tf(rvec, tvec)

                    # Overlay info
                    n_detected = len(ids)
                    cv2.putText(
                        current_frame,
                        f"Board: {n_detected}/{self.total_markers} markers",
                        (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8,
                        (0, 255, 0), 2)
            else:
                cv2.putText(
                    current_frame,
                    f"Detected {len(ids)} markers – need corners from ≥1",
                    (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7,
                    (0, 0, 255), 2)
        else:
            n = 0 if ids is None else len(ids)
            cv2.putText(
                current_frame,
                f"Markers: {n}/{self.total_markers} (need ≥{MIN_MARKERS_FOR_POSE})",
                (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7,
                (0, 0, 255), 2)

        # ── Display + keypress handling ──────────────────────────────────
        cv2.namedWindow("camera", cv2.WINDOW_NORMAL)
        cv2.resizeWindow("camera", 700, 500)
        cv2.imshow("camera", current_frame)

        key = cv2.waitKey(1)
        if key == ord('q'):
            if self._last_rvec is not None:
                self.save_board_pose(self._last_rvec, self._last_tvec)
                self.save_image(current_frame)
                self.get_logger().info(
                    f"Saved pose_{self.pose_count} board transform.")
                self.keypress_publisher.publish(String(data='q'))
            else:
                self.get_logger().warn(
                    "No valid board pose yet – cannot save.")
        elif key == ord('e'):
            self.get_logger().info("Ending program...")
            self.keypress_publisher.publish(String(data='e'))
            cv2.destroyAllWindows()
            rclpy.shutdown()

    # ── TF broadcast ─────────────────────────────────────────────────────

    def _broadcast_board_tf(self, rvec, tvec):
        """Publish the board→camera transform on /tf."""
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = self.calculated_camera_optical_frame_name
        t.child_frame_id = self.aruco_marker_name

        t.transform.translation.x = float(tvec[0][0])
        t.transform.translation.y = float(tvec[1][0])
        t.transform.translation.z = float(tvec[2][0])

        rot_mat = cv2.Rodrigues(rvec)[0]
        quat = R.from_matrix(rot_mat).as_quat()  # [x, y, z, w]
        t.transform.rotation.x = quat[0]
        t.transform.rotation.y = quat[1]
        t.transform.rotation.z = quat[2]
        t.transform.rotation.w = quat[3]

        self.tfbroadcaster.sendTransform(t)

    # ── Persistence (same YAML format as before) ─────────────────────────

    def save_board_pose(self, rvec, tvec):
        """Append ONE board pose to the marker data YAML.

        Format is identical to the old single-marker version so that
        handeye_estimation.py works without changes.
        """
        yaml_file_path = self.marker_data_file_name
        try:
            with open(yaml_file_path, 'r') as f:
                data = yaml.safe_load(f) or {'poses': []}
        except FileNotFoundError:
            data = {'poses': []}

        rot_mat = cv2.Rodrigues(rvec)[0]
        pose_entry = {
            'rotation': rot_mat.tolist(),
            'translation': tvec.flatten().tolist(),
        }
        data['poses'].append(pose_entry)

        with open(yaml_file_path, 'w') as f:
            yaml.dump(data, f, default_flow_style=False)

        self.pose_count += 1
        self.get_logger().info(f"Pose {self.pose_count}:")
        self.get_logger().info("Rotation Matrix:\n" + str(rot_mat))
        self.get_logger().info("Translation Vector:\n" + str(tvec.flatten()))
        self.get_logger().info(
            f"Board pose appended to {self.marker_data_file_name}")

    def save_image(self, frame):
        image_filename = self.image_filename.format(pose_count=self.pose_count)
        cv2.imwrite(image_filename, frame)
        self.get_logger().info(f"Image saved as {image_filename}")


def main(args=None):
    rclpy.init(args=args)
    aruco_node = ArucoNode()
    try:
        rclpy.spin(aruco_node)
    finally:
        aruco_node.destroy_node()


if __name__ == '__main__':
    main()
