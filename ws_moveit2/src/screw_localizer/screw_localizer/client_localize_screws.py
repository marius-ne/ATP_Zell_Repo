#!/usr/bin/env python3
"""
Client script to request screw localization from the screw_depth_localizer service.
Usage: ros2 run screw_localizer client_localize_screws
"""

import rclpy
from rclpy.node import Node
from screw_interfaces.srv import LocalizeScrews
from geometry_msgs.msg import Pose


class ScrewLocalizerClient(Node):
    def __init__(self):
        super().__init__('screw_localizer_client')
        self.client = self.create_client(LocalizeScrews, 'detect_screws')
        
        # Wait for service to be available
        while not self.client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Waiting for detect_screws service...')
        
        self.get_logger().info('Service available, sending request...')
        self.send_request()

    def send_request(self):
        """Send a minimal request to trigger screw detection."""
        req = LocalizeScrews.Request()
        
        # Minimal request fields (the service will use cached camera frame)
        req.n = 0  # Not used, service will use cached RGBD frame
        req.camera_poses = []
        req.intrinsics = []
        req.screws_per_image = []
        req.screw_u = []
        req.screw_v = []
        req.max_screws = 10
        req.ransac_inlier_thresh_m = 0.01
        req.ransac_iters = 100
        
        future = self.client.call_async(req)
        future.add_done_callback(self.response_callback)

    def response_callback(self, future):
        """Handle the service response."""
        try:
            response = future.result()
            
            if response.success:
                self.get_logger().info(f"✓ {response.message}")
                self.get_logger().info(f"Found {len(response.screw_positions)} screw(s)")
                
                for i, pos in enumerate(response.screw_positions):
                    rmse = response.screw_fit_rmse_m[i]
                    pose = response.desired_ee_poses[i]
                    self.get_logger().info(
                        f"  Screw {i}: pos=({pos.x:.3f}, {pos.y:.3f}, {pos.z:.3f}), "
                        f"rmse={rmse:.4f}m"
                    )
                    self.get_logger().info(
                        f"    EE pose: pos=({pose.position.x:.3f}, {pose.position.y:.3f}, "
                        f"{pose.position.z:.3f})"
                    )
            else:
                self.get_logger().error(f"✗ Service failed: {response.message}")
        
        except Exception as e:
            self.get_logger().error(f'Service call failed: {e}')
        
        finally:
            rclpy.shutdown()


def main(args=None):
    rclpy.init(args=args)
    client = ScrewLocalizerClient()
    rclpy.spin(client)


if __name__ == '__main__':
    main()
