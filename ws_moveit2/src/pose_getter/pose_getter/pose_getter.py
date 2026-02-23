#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from tf2_msgs.msg import TFMessage
from scipy.spatial.transform import Rotation as R
from rclpy.qos import QoSProfile, DurabilityPolicy
from geometry_msgs.msg import PoseStamped
import numpy as np
import yaml
import os

# Create a QoS profile for subscribing to /tf_static
qos_profile = QoSProfile(depth=10, durability=DurabilityPolicy.TRANSIENT_LOCAL)

class PoseGetterNode(Node):
    def __init__(self):
        super().__init__('pose_getter_node')
        
        # Declare parameters
        self.declare_parameter('base_frame', 'world')
        self.declare_parameter('ee_frame', 'camera')
        self.declare_parameter('publish_rate', 1.0)
        self.declare_parameter('manual_mode', False)
        self.declare_parameter('output_format', 'pose')  # 'pose' or 'matrix'
        
        self.base_frame = self.get_parameter('base_frame').value
        self.ee_frame = self.get_parameter('ee_frame').value
        rate = self.get_parameter('publish_rate').value
        self.manual_mode = self.get_parameter('manual_mode').value
        self.output_format = self.get_parameter('output_format').value
        
        # Subscribe to TF topics
        self.subscription_tf = self.create_subscription(
            TFMessage, '/tf', self.listener_callback_tf, 10)
        self.subscription_tf_static = self.create_subscription(
            TFMessage, '/tf_static', self.listener_callback_tf_static, qos_profile)
        
        self.transformations = {}
        
        # Publisher for current pose
        self.pose_pub = self.create_publisher(
            PoseStamped,
            '/pose_getter/current_ee_pose',
            10
        )
        
        # Timer to publish pose (only in continuous mode)
        if not self.manual_mode:
            self.timer = self.create_timer(1.0 / rate, self.timer_callback)
        
        mode_str = 'MANUAL (press Enter to sample)' if self.manual_mode else 'continuous'
        self.get_logger().info(f'Pose Getter Node started [{mode_str}]. Publishing {self.ee_frame} pose in {self.base_frame} frame.')
        
        # YAML file for manual mode pose logging – save in the source package dir
        # Walk up from __file__ until we find a dir containing src/pose_getter
        _src_pkg_dir = None
        _cur = os.path.dirname(os.path.abspath(__file__))
        for _ in range(10):
            _candidate = os.path.join(_cur, 'src', 'pose_getter', 'pose_getter')
            if os.path.isdir(_candidate):
                _src_pkg_dir = _candidate
                break
            _parent = os.path.dirname(_cur)
            if _parent == _cur:
                break
            _cur = _parent
        if _src_pkg_dir is None:
            _src_pkg_dir = os.path.dirname(os.path.abspath(__file__))
        self._yaml_path = os.path.join(_src_pkg_dir, 'recorded_poses.yaml')
        self._pose_count = 0
        if self.manual_mode:
            # Clear file on startup
            with open(self._yaml_path, 'w') as f:
                yaml.dump({'poses': []}, f)
            self.get_logger().info(f'Pose log cleared: {self._yaml_path}')
    
    def quaternion_to_rotation_matrix(self, x, y, z, w):
        """Convert a quaternion into a full three-dimensional rotation matrix using scipy."""
        quat = [x, y, z, w]
        norm = np.linalg.norm(quat)
        if norm < 1e-6:
            self.get_logger().warn('Received zero/near-zero norm quaternion, skipping transform.')
            return None
        try:
            return R.from_quat(quat).as_matrix()
        except ValueError as e:
            self.get_logger().warn(f'Invalid quaternion ({x}, {y}, {z}, {w}): {e}')
            return None
    
    def listener_callback_tf(self, msg):
        """Handle incoming transform messages from /tf."""
        for transform in msg.transforms:
            if transform.child_frame_id and transform.header.frame_id:
                self.transformations[(transform.header.frame_id, transform.child_frame_id)] = transform
    
    def listener_callback_tf_static(self, msg):
        """Handle incoming static transform messages from /tf_static."""
        for transform in msg.transforms:
            if transform.child_frame_id and transform.header.frame_id:
                self.transformations[(transform.header.frame_id, transform.child_frame_id)] = transform
    
    def get_transformation_matrix(self, frame_from, frame_to):
        """Get transformation matrix from frame_from to frame_to."""
        if (frame_from, frame_to) in self.transformations:
            trans = self.transformations[(frame_from, frame_to)].transform
            
            # Build 4x4 transformation matrix
            T = np.eye(4)
            rotation = [trans.rotation.x, trans.rotation.y, trans.rotation.z, trans.rotation.w]
            rot_matrix = self.quaternion_to_rotation_matrix(*rotation)
            if rot_matrix is None:
                return None
            T[:3, :3] = rot_matrix
            T[:3, 3] = [trans.translation.x, trans.translation.y, trans.translation.z]
            
            return T
        return None
    
    def get_full_transformation_matrix(self):
        """Compute full transformation from base to end-effector by chaining transforms."""
        T = np.eye(4)
        
        # Define link chain for IIWA robot (try both with and without iiwa_base)
        link_order = [
            ('world', 'iiwa_base'),
            ('iiwa_base', 'link_0'),
            ('link_0', 'link_1'),
            ('link_1', 'link_2'),
            ('link_2', 'link_3'),
            ('link_3', 'link_4'),
            ('link_4', 'link_5'),
            ('link_5', 'link_6'),
            ('link_6', 'link_7'),
            ('link_7', 'tool0'),
        ]
        # Only chain beyond tool0 if ee_frame is a different frame
        if self.ee_frame != 'tool0':
            link_order.append(('tool0', self.ee_frame))
        
        # Alternative shorter chain if iiwa_base doesn't exist
        short_chain = [
            ('world', 'link_0'),
            ('link_0', 'link_1'),
            ('link_1', 'link_2'),
            ('link_2', 'link_3'),
            ('link_3', 'link_4'),
            ('link_4', 'link_5'),
            ('link_5', 'link_6'),
            ('link_6', 'link_7'),
            ('link_7', 'tool0'),
        ]
        if self.ee_frame != 'tool0':
            short_chain.append(('tool0', self.ee_frame))
        
        # Try full chain first
        for (frame_id, child_frame_id) in link_order:
            T_local = self.get_transformation_matrix(frame_id, child_frame_id)
            if T_local is not None:
                T = np.dot(T, T_local)
            elif (frame_id, child_frame_id) == ('world', 'iiwa_base'):
                # If world->iiwa_base doesn't exist, try the short chain
                T = np.eye(4)
                for (f, c) in short_chain:
                    T_local = self.get_transformation_matrix(f, c)
                    if T_local is not None:
                        T = np.dot(T, T_local)
                    else:
                        return None
                return T
            else:
                return None
        
        return T
    
    def timer_callback(self):
        """Periodically compute and publish the current end-effector pose."""
        T = self.get_full_transformation_matrix()
        
        if T is not None:
            # Extract position and rotation
            position = T[:3, 3]
            rotation_matrix = T[:3, :3]
            
            # Convert rotation matrix to quaternion using scipy
            r = R.from_matrix(rotation_matrix)
            quat = r.as_quat()  # Returns [x, y, z, w]
            
            # Create and publish PoseStamped message
            pose_msg = PoseStamped()
            pose_msg.header.stamp = self.get_clock().now().to_msg()
            pose_msg.header.frame_id = self.base_frame
            pose_msg.pose.position.x = float(position[0])
            pose_msg.pose.position.y = float(position[1])
            pose_msg.pose.position.z = float(position[2])
            pose_msg.pose.orientation.x = float(quat[0])
            pose_msg.pose.orientation.y = float(quat[1])
            pose_msg.pose.orientation.z = float(quat[2])
            pose_msg.pose.orientation.w = float(quat[3])
            
            self.pose_pub.publish(pose_msg)
            
            # Log to console
            if self.output_format == 'matrix':
                np.set_printoptions(precision=6, suppress=True)
                self.get_logger().info(
                    f"\n{self.ee_frame} 4x4 Transform ({self.base_frame} -> {self.ee_frame}):\n{T}"
                )
            else:
                euler = r.as_euler('xyz', degrees=True)
                self.get_logger().info(
                    f"{self.ee_frame} Pose:\n"
                    f"  Position:    x={position[0]:.4f}, y={position[1]:.4f}, z={position[2]:.4f}\n"
                    f"  Quaternion:  x={quat[0]:.4f}, y={quat[1]:.4f}, z={quat[2]:.4f}, w={quat[3]:.4f}\n"
                    f"  Euler (deg): rx={euler[0]:.2f}, ry={euler[1]:.2f}, rz={euler[2]:.2f}"
                )
            
            # Append to YAML in manual mode
            if self.manual_mode:
                self._append_to_yaml(position, quat, T)
    
    def _append_to_yaml(self, position, quat, T):
        """Append current pose to the YAML log file."""
        try:
            with open(self._yaml_path, 'r') as f:
                data = yaml.safe_load(f) or {'poses': []}
        except FileNotFoundError:
            data = {'poses': []}
        
        self._pose_count += 1
        r = R.from_quat(quat)
        euler = r.as_euler('xyz', degrees=True)
        
        pose_entry = {
            'id': self._pose_count,
            'frame': self.ee_frame,
            'position': {
                'x': float(position[0]),
                'y': float(position[1]),
                'z': float(position[2]),
            },
            'orientation_quat': {
                'x': float(quat[0]),
                'y': float(quat[1]),
                'z': float(quat[2]),
                'w': float(quat[3]),
            },
            'euler_deg': {
                'rx': float(euler[0]),
                'ry': float(euler[1]),
                'rz': float(euler[2]),
            },
            'matrix_4x4': T.tolist(),
        }
        data['poses'].append(pose_entry)
        
        with open(self._yaml_path, 'w') as f:
            yaml.dump(data, f, default_flow_style=False)
        
        self.get_logger().info(f'Pose #{self._pose_count} saved to {self._yaml_path}')

def main(args=None):
    rclpy.init(args=args)
    node = PoseGetterNode()
    
    if node.manual_mode:
        # Manual mode: spin in background, prompt user in terminal
        import threading
        spin_thread = threading.Thread(target=rclpy.spin, args=(node,), daemon=True)
        spin_thread.start()
        
        print('\n=== Manual Pose Getter ===')
        print('Press ENTER to sample current pose, type "q" to quit.\n')
        
        try:
            while rclpy.ok():
                user_input = input()
                if user_input.strip().lower() == 'q':
                    break
                node.timer_callback()
        except (KeyboardInterrupt, EOFError):
            pass
        finally:
            node.destroy_node()
            if rclpy.ok():
                rclpy.shutdown()
    else:
        # Continuous mode
        try:
            rclpy.spin(node)
        except KeyboardInterrupt:
            pass
        finally:
            node.destroy_node()
            if rclpy.ok():
                rclpy.shutdown()

if __name__ == '__main__':
    main()