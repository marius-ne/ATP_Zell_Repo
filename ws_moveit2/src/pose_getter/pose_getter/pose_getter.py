#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from tf2_msgs.msg import TFMessage
from scipy.spatial.transform import Rotation as R
from rclpy.qos import QoSProfile, DurabilityPolicy
from geometry_msgs.msg import PoseStamped
import numpy as np

# Create a QoS profile for subscribing to /tf_static
qos_profile = QoSProfile(depth=10, durability=DurabilityPolicy.TRANSIENT_LOCAL)

class PoseGetterNode(Node):
    def __init__(self):
        super().__init__('pose_getter_node')
        
        # Declare parameters
        self.declare_parameter('base_frame', 'world')
        self.declare_parameter('ee_frame', 'tool0')
        self.declare_parameter('publish_rate', 1.0)
        
        self.base_frame = self.get_parameter('base_frame').value
        self.ee_frame = self.get_parameter('ee_frame').value
        rate = self.get_parameter('publish_rate').value
        
        # Subscribe to TF topics
        self.subscription_tf = self.create_subscription(
            TFMessage, '/tf', self.listener_callback_tf, 10)
        self.subscription_tf_static = self.create_subscription(
            TFMessage, '/tf_static', self.listener_callback_tf_static, qos_profile)
        
        self.transformations = {}
        
        # Publisher for current pose
        self.pose_pub = self.create_publisher(
            PoseStamped,
            '/current_ee_pose',
            10
        )
        
        # Timer to publish pose
        self.timer = self.create_timer(1.0 / rate, self.timer_callback)
        
        self.get_logger().info(f'Pose Getter Node started. Publishing {self.ee_frame} pose in {self.base_frame} frame.')
    
    def quaternion_to_rotation_matrix(self, x, y, z, w):
        """Convert a quaternion into a full three-dimensional rotation matrix using scipy."""
        return R.from_quat([x, y, z, w]).as_matrix()
    
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
            T[:3, :3] = self.quaternion_to_rotation_matrix(*rotation)
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
            self.get_logger().info(
                f"EE Pose: pos=({position[0]:.4f}, {position[1]:.4f}, {position[2]:.4f}), "
                f"quat=({quat[0]:.4f}, {quat[1]:.4f}, {quat[2]:.4f}, {quat[3]:.4f})"
            )

def main(args=None):
    rclpy.init(args=args)
    node = PoseGetterNode()
    
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