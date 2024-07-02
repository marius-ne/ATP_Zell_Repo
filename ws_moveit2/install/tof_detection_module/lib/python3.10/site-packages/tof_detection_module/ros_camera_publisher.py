import rclpy
from rclpy.node import Node
from sensor_msgs.msg import PointCloud2, PointField
import numpy as np
import open3d as o3d
import os
import ament_index_python

class PointCloudPublisher(Node):
    def __init__(self):
        self.get_logger().info('Starting node camera publisher')
        super().__init__('point_cloud_publisher')
        self.publisher_ = self.create_publisher(PointCloud2, 'point_cloud_topic', 10)
        self.get_logger().info('Set timer')
        self.timer_ = self.create_timer(1.0, self.publish_point_cloud)

    def publish_point_cloud(self):
        # Load the point cloud from file

        self.get_logger().info('Load point cloud from file')
        point_cloud = o3d.io.read_point_cloud('/home/alex/studirepos/PoseEstimationTof/point_cloud/scene.ply')

        # Convert the Open3D point cloud to numpy array
        self.get_logger().info('Process  point cloud')
        points = np.asarray(point_cloud.points)

        # Create a PointCloud2 message
        msg = PointCloud2()
        msg.header.frame_id = "map"  # Set the frame ID as needed
        msg.height = 1
        msg.width = points.shape[0]
        msg.fields = [
            PointField(name="x", offset=0, datatype=PointField.FLOAT32, count=1),
            PointField(name="y", offset=4, datatype=PointField.FLOAT32, count=1),
            PointField(name="z", offset=8, datatype=PointField.FLOAT32, count=1)
        ]
        msg.is_bigendian = False
        msg.point_step = 12
        msg.row_step = msg.point_step * points.shape[0]
        msg.is_dense = True
        msg.data = points.astype(np.float32).tobytes()

        self.get_logger().info('Publish point cloud')
        self.publisher_.publish(msg)


def get_ply(args=None):
    rclpy.init(args=args)
    point_cloud_publisher = PointCloudPublisher()
    point_cloud_publisher.get_logger().info('Start spin ros camera publisher')
    rclpy.spin(point_cloud_publisher)
    point_cloud_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    get_ply()
