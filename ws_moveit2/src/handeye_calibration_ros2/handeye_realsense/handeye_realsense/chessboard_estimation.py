"""
Copyright © 2024 Shengyang Zhuang. All rights reserved.

Contact: https://shengyangzhuang.github.io/

Modified to use single ArUco marker detection + chessboard corner
refinement for the Zivid ZVD-CB01 (7x8 squares, 30 mm) calibration board.
"""
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TransformStamped
from tf2_ros import TransformBroadcaster, StaticTransformBroadcaster
from scipy.spatial.transform import Rotation as R
from cv_bridge import CvBridge
from std_msgs.msg import String
from realsense2_camera_msgs.msg import RGBD

import cv2
import numpy as np
import yaml

# ArUco dictionary lookup
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
    "DICT_ARUCO_ORIGINAL": cv2.aruco.DICT_ARUCO_ORIGINAL
}


class ArucoNode(Node):
    def __init__(self):
        super().__init__('aruco_node')

        with open('src/handeye_calibration_ros2/handeye_realsense/config.yaml', 'r') as file:
            config = yaml.safe_load(file)

        aruco_dictionary_name = config["aruco_dictionary_name"]
        self.aruco_marker_name = config["aruco_marker_name"]
        self.aruco_marker_side_length = config["aruco_marker_side_length"]
        self.camera_calibration_parameters_filename = config["camera_calibration_parameters_filename"]
        self.image_topic = config["image_topic"]
        self.calculated_camera_optical_frame_name = config["calculated_camera_optical_frame_name"]
        self.marker_data_file_name = config["marker_data_file_name"]
        self.image_filename = config["image_filename"]

        # Chessboard parameters (Zivid ZVD-CB01: 7x8 squares → 6x7 inner corners, 30 mm)
        self.chessboard_inner_cols = config.get("chessboard_inner_cols", 6)
        self.chessboard_inner_rows = config.get("chessboard_inner_rows", 7)
        self.chessboard_square_size = config.get("chessboard_square_size", 0.030)

        # Check that we have a valid ArUco marker
        if ARUCO_DICT.get(aruco_dictionary_name, None) is None:
            self.get_logger().error(f"ArUCo tag of '{aruco_dictionary_name}' is not supported")
            return

        # Load the camera parameters from the saved file
        cv_file = cv2.FileStorage(self.camera_calibration_parameters_filename, cv2.FILE_STORAGE_READ)
        self.mtx = cv_file.getNode('K').mat()
        self.dst = cv_file.getNode('D').mat()
        cv_file.release()

        # Set up ArUco dictionary and detector parameters
        self.dictionary = cv2.aruco.getPredefinedDictionary(ARUCO_DICT[aruco_dictionary_name])
        self.detector_params = cv2.aruco.DetectorParameters_create()
        self.detector_params.cornerRefinementMethod = cv2.aruco.CORNER_REFINE_SUBPIX
        self.detector_params.markerBorderBits = 1

        # Precompute chessboard 3D object points (Z = 0 plane)
        self.chessboard_pattern = (self.chessboard_inner_cols, self.chessboard_inner_rows)
        self.chessboard_obj_pts = np.zeros(
            (self.chessboard_inner_cols * self.chessboard_inner_rows, 3), dtype=np.float32)
        self.chessboard_obj_pts[:, :2] = np.mgrid[
            0:self.chessboard_inner_cols,
            0:self.chessboard_inner_rows
        ].T.reshape(-1, 2) * self.chessboard_square_size

        # Sub-pixel refinement criteria
        self.subpix_criteria = (
            cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

        self.get_logger().info(
            f"Detecting single '{aruco_dictionary_name}' ArUco marker "
            f"(side={self.aruco_marker_side_length}m) + "
            f"chessboard {self.chessboard_inner_cols}x{self.chessboard_inner_rows} "
            f"(square={self.chessboard_square_size}m)"
        )

        # Create the subscriber
        self.subscription = self.create_subscription(RGBD, self.image_topic, self.listener_callback, 10)
        self.keypress_publisher = self.create_publisher(String, 'keypress_topic', 10)

        self.pose_count = 0
        self.last_rvec = None
        self.last_tvec = None

        # Initialize the transform broadcasters
        self.tfbroadcaster = TransformBroadcaster(self)
        self.static_tfbroadcaster = StaticTransformBroadcaster(self)

        # Used to convert between ROS and OpenCV images
        self.bridge = CvBridge()

    def listener_callback(self, data: RGBD):
        current_frame = self.bridge.imgmsg_to_cv2(data.rgb, desired_encoding='bgr8')
        gray = cv2.cvtColor(current_frame, cv2.COLOR_BGR2GRAY)

        # --- Step 1: detect single ArUco marker ---
        corners, marker_ids, rejected = cv2.aruco.detectMarkers(
            current_frame, self.dictionary, parameters=self.detector_params)

        aruco_detected = marker_ids is not None and len(marker_ids) > 0
        if aruco_detected:
            cv2.aruco.drawDetectedMarkers(current_frame, corners, marker_ids)

        # --- Step 2: detect chessboard corners for precise pose ---
        cb_found, cb_corners = cv2.findChessboardCorners(
            gray, self.chessboard_pattern,
            cv2.CALIB_CB_ADAPTIVE_THRESH + cv2.CALIB_CB_NORMALIZE_IMAGE + cv2.CALIB_CB_FAST_CHECK)

        rvec = None
        tvec = None

        if cb_found:
            # Refine to sub-pixel accuracy
            cb_corners_refined = cv2.cornerSubPix(
                gray, cb_corners, (11, 11), (-1, -1), self.subpix_criteria)

            # Solve PnP using the chessboard corners
            success, rvec, tvec = cv2.solvePnP(
                self.chessboard_obj_pts, cb_corners_refined, self.mtx, self.dst)

            if success:
                cv2.drawChessboardCorners(current_frame, self.chessboard_pattern,
                                          cb_corners_refined, cb_found)
                cv2.drawFrameAxes(current_frame, self.mtx, self.dst, rvec, tvec, 0.05)
            else:
                rvec = None
                tvec = None

        # Fallback: if chessboard was not found but ArUco was, use ArUco pose
        if rvec is None and aruco_detected:
            rvecs, tvecs, _ = cv2.aruco.estimatePoseSingleMarkers(
                corners, self.aruco_marker_side_length, self.mtx, self.dst)
            if rvecs is not None and len(rvecs) > 0:
                rvec = rvecs[0].reshape((3, 1))
                tvec = tvecs[0].reshape((3, 1))
                cv2.drawFrameAxes(current_frame, self.mtx, self.dst, rvec, tvec, 0.05)
                self.get_logger().debug("Using ArUco fallback pose (chessboard not found)")

        if rvec is not None:
            self.last_rvec = rvec
            self.last_tvec = tvec

            # Build TF transform for the board origin
            t = TransformStamped()
            t.header.stamp = self.get_clock().now().to_msg()
            t.header.frame_id = self.calculated_camera_optical_frame_name
            t.child_frame_id = self.aruco_marker_name

            t.transform.translation.x = float(tvec[0][0])
            t.transform.translation.y = float(tvec[1][0])
            t.transform.translation.z = float(tvec[2][0])

            rotation_matrix = cv2.Rodrigues(rvec)[0]
            quat = R.from_matrix(rotation_matrix).as_quat()  # [x, y, z, w]

            t.transform.rotation.x = quat[0]
            t.transform.rotation.y = quat[1]
            t.transform.rotation.z = quat[2]
            t.transform.rotation.w = quat[3]

            self.tfbroadcaster.sendTransform(t)

        # Display
        cv2.namedWindow("camera", cv2.WINDOW_NORMAL)
        cv2.resizeWindow("camera", 700, 500)
        cv2.imshow("camera", current_frame)

        key = cv2.waitKey(1)
        if key == ord('q'):
            if self.last_rvec is not None:
                self.save_marker_data(self.last_rvec, self.last_tvec)
                self.save_image(current_frame)
                self.get_logger().info(f"Saved pose_{self.pose_count} board transform.")
            else:
                self.get_logger().warn("No board pose detected yet, nothing to save.")
            self.keypress_publisher.publish(String(data='q'))
        elif key == ord('e'):
            self.get_logger().info("Ending program...")
            self.keypress_publisher.publish(String(data='e'))
            cv2.destroyAllWindows()
            rclpy.shutdown()

    def save_marker_data(self, rvec, tvec):
        """Save the single board pose (rvec/tvec) to a YAML file."""
        yaml_file_path = self.marker_data_file_name
        try:
            with open(yaml_file_path, 'r') as file:
                data = yaml.safe_load(file) or {'poses': []}
        except FileNotFoundError:
            data = {'poses': []}

        R_mat = cv2.Rodrigues(rvec)[0]
        marker_data = {
            'rotation': R_mat.tolist(),
            'translation': tvec.flatten().tolist(),
        }
        data['poses'].append(marker_data)

        with open(yaml_file_path, 'w') as file:
            yaml.dump(data, file, default_flow_style=False)

        self.pose_count += 1
        self.get_logger().info(f"Pose {self.pose_count}:")
        self.get_logger().info("Rotation Matrix:\n" + str(R_mat))
        self.get_logger().info("Translation Vector:\n" + str(tvec.flatten()))
        self.get_logger().info(f'Transformation for Pose {self.pose_count} appended to {self.marker_data_file_name}')

    def save_image(self, frame):
        image_filename = self.image_filename.format(pose_count=self.pose_count)
        cv2.imwrite(image_filename, frame)
        self.get_logger().info(f'Image saved as {image_filename}')


def main(args=None):
    rclpy.init(args=args)
    aruco_node = ArucoNode()
    try:
        rclpy.spin(aruco_node)
    finally:
        aruco_node.destroy_node()


if __name__ == '__main__':
    main()
