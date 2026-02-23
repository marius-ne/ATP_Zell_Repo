import rclpy
from rclpy.node import Node
import yaml
import numpy as np

class MarkerPositionEstimator(Node):
    def __init__(self):
        super().__init__('marker_position_estimator')

        # File paths
        cam_marker_poses_path = '/home/remanpilot/ws/restackcell/ws_moveit2/src/handeye_calibration_ros2/handeye_realsense/resource/marker_data_realsense_custom_calib.yaml'
        ee_poses_path = '/home/remanpilot/ws/restackcell/ws_moveit2/src/handeye_calibration_ros2/handeye_realsense/resource/robot_data_realsense_custom_calib.yaml'
        
        # Manually input your estimated extrinsic matrix (Camera -> End Effector)
        # Structure: [[R, t], [0, 1]]
        self.T_ee_cam = np.array([[ 0.99949278 ,-0.02734792  ,0.01631804 ,-0.19035098],
 [ 0.01642375,  0.00364518, -0.99985848, -0.01819389],
 [ 0.02728457 , 0.99961933,  0.00409248,  0.02748924],
 [ 0.        ,  0.        ,        0.    ,      1.        ]])

        self.compute_marker_positions(ee_poses_path, cam_marker_poses_path)

    def load_yaml_poses(self, file_path):
        with open(file_path, 'r') as file:
            data = yaml.safe_load(file)
        return data['poses']

    def make_4x4(self, rotation, translation):
        mat = np.eye(4)
        mat[:3, :3] = np.array(rotation)
        mat[:3, 3] = np.array(translation)
        return mat

    def compute_marker_positions(self, ee_path, cam_marker_path):
        try:
            ee_poses = self.load_yaml_poses(ee_path)
            cam_marker_poses = self.load_yaml_poses(cam_marker_path)
        except Exception as e:
            self.get_logger().error(f"Failed to load YAML: {e}")
            return

        count = min(len(ee_poses), len(cam_marker_poses))
        if len(ee_poses) != len(cam_marker_poses):
            self.get_logger().warn(f"List mismatch! Using first {count} poses.")

        all_positions = []

        self.get_logger().info("--- Estimated Marker Positions (Base Frame) ---")
        
        for i in range(count):
            # T_base_ee
            T_base_ee = self.make_4x4(ee_poses[i]['rotation'], ee_poses[i]['translation'])
            
            # T_cam_aruco
            T_cam_aruco = self.make_4x4(cam_marker_poses[i]['rotation'], cam_marker_poses[i]['translation'])

            # Chain: Base -> EE -> Cam -> Aruco
            T_base_aruco = T_base_ee @ self.T_ee_cam @ T_cam_aruco

            pos = T_base_aruco[:3, 3]
            all_positions.append(pos)
            self.get_logger().info(f"Pose {i:02d}: X={pos[0]:.4f}, Y={pos[1]:.4f}, Z={pos[2]:.4f}")

        # --- Statistical Analysis ---
        positions_np = np.array(all_positions)
        mean_pos = np.mean(positions_np, axis=0)
        std_pos = np.std(positions_np, axis=0)
        
        # Calculate Euclidean distances from the mean for each point
        dist_from_mean = np.linalg.norm(positions_np - mean_pos, axis=1)
        max_drift = np.max(dist_from_mean)
        rmse = np.mean(dist_from_mean)

        self.get_logger().info("-----------------------------------------------")
        self.get_logger().info("--- STATISTICAL REPORT ---")
        self.get_logger().info(f"Mean Position:  X={mean_pos[0]:.4f}, Y={mean_pos[1]:.4f}, Z={mean_pos[2]:.4f}")
        self.get_logger().info(f"Std Deviation:  X={std_pos[0]:.4f}, Y={std_pos[1]:.4f}, Z={std_pos[2]:.4f}")
        self.get_logger().info(f"Mean Error:      {rmse * 1000:.2f} mm")
        self.get_logger().info(f"Max Drift:      {max_drift * 1000:.2f} mm")
        self.get_logger().info("-----------------------------------------------")

        if rmse < 0.005:
            self.get_logger().info("Result: EXCELLENT calibration (<5mm error).")
        elif rmse < 0.015:
            self.get_logger().info("Result: ACCEPTABLE calibration (<15mm error).")
        else:
            self.get_logger().warn("Result: POOR calibration. Check for board warping or rotation errors.")

def main(args=None):
    rclpy.init(args=args)
    node = MarkerPositionEstimator()
    rclpy.shutdown()

if __name__ == '__main__':
    main()