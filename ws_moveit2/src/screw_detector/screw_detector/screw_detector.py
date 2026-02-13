from ament_index_python.packages import get_package_share_directory
import os
import cv2

from datetime import datetime
from ultralytics import YOLO

import rclpy
from rclpy.node import Node
from rclpy.serialization import serialize_message, deserialize_message  # Add this

from sensor_msgs.msg import Image
from std_msgs.msg import String
from geometry_msgs.msg import PoseStamped
from realsense2_camera_msgs.msg import RGBD
from cv_bridge import CvBridge

class ScrewDetectorNode(Node):
    def __init__(self):
        super().__init__('screw_detector_node')

        # Add parameters for manual operation
        self.declare_parameter('write_to_file', False)
        self.declare_parameter('output_dir', '')
        self.declare_parameter('get_robot_poses', False)

        # If writing to file is enabled, set up output directory and CSV file
        self._write_to_file = self.get_parameter('write_to_file').value
        self._output_dir = self.get_parameter('output_dir').value
        os.makedirs(self._output_dir, exist_ok=True)
        if self._write_to_file and self._output_dir:
            self._dir_identifier = datetime.now().strftime('%Y%m%d_%H%M%S')
            os.makedirs(f'{self._output_dir}/{self._dir_identifier}', exist_ok=True)
            # Create csv to append to
            with open(f'{self._output_dir}/{self._dir_identifier}/_screw_detections.csv', 'w') as f:
                f.write("timestamp,class,x,y,width,height,confidence,depth,pose\n")
        elif self._write_to_file and not self._output_dir:
            self.get_logger().warning('Output directory not specified. Detections will not be saved to file.')
            self._write_to_file = False

        # Optional logging of current robot poses with detections for later analysis
        #   NOTE: requires pose_getter node to be running
        self._get_robot_poses = self.get_parameter('get_robot_poses').value
        if self._get_robot_poses:
            self.pose_subscription = self.create_subscription(
                PoseStamped,
                '/pose_getter/current_ee_pose',
                self._pose_callback,
                10
            )
            self.current_pose = ""

        # Subscribe to RealSense RGBD message (contains both color and depth)
        self.subscription = self.create_subscription(
            RGBD,
            '/camera/camera/rgbd',
            self.image_callback,
            10
        )

        # Publisher for detection results as string
        self.publisher_ = self.create_publisher(
            String,
            '/screw_detector/detections',
            10
        )

        # Publisher for annotated images for RViz
        self.image_pub = self.create_publisher(
            Image,
            '/screw_detector/annotated_image',
            10
        )

        pkg_share = get_package_share_directory('screw_detector')
        weights_path = os.path.join(pkg_share, 'weights', 'best.pt')

        self.bridge = CvBridge()
        self.model = YOLO(weights_path)

        self.get_logger().info('Screw Detector Node started.')

    def _pose_callback(self, msg: PoseStamped):
        """Cache the latest pose message"""
        # Store the full message object
        self.current_pose = msg
        
        # Also create a readable string representation
        p = msg.pose.position
        o = msg.pose.orientation
        self.current_pose_str = f"x>{p.x:.4g};y>{p.y:.4g};z>{p.z:.4g};" + \
                                f"qx>{o.x:.4g};qy>{o.y:.4g};qz>{o.z:.4g};qw>{o.w:.4g}"
        
        self.get_logger().debug(f'Received pose: {self.current_pose_str}')

    def image_callback(self, msg: RGBD):
        # Extract color and depth images from RGBD message
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg.rgb, desired_encoding='bgr8')
            cv_depth = self.bridge.imgmsg_to_cv2(msg.depth, desired_encoding='16UC1')
            self.get_logger().debug(f'Received color image: {cv_image.shape}, depth image: {cv_depth.shape}')
        except Exception as e:
            self.get_logger().error(f'Could not convert image: {e}')
            return
        
        # Also get current robot pose if enabled
        if self._get_robot_poses and self.current_pose:
            self.get_logger().debug(f'Using cached pose: {self.current_pose_str}')

        # Run YOLO detection
        results = self.model(cv_image)

        detections = []
        # Draw bounding boxes and collect detection info
        for result in results:
            for obj in result.boxes:
                cls = int(obj.cls[0])
                conf = float(obj.conf[0])
                # Center coordinates should be sub-pixel accurate
                center_x, center_y, width, height = obj.xywh[0] 
                
                # Make bounding box for visualization
                width = int(width)
                height = int(height)
                x1 = int(center_x - width // 2)      # top left corner x
                y1 = int(center_y - height // 2)     # top left corner y
                x2 = x1 + width
                y2 = y1 + height

                # Get depth value (in mm) at the detection spot
                depth_value_mm = cv_depth[int(center_y), int(center_x)]  

                # Encode detection info as message to pass to other nodes
                detection_string = f'class:{cls}, center_x:{center_x:5g}, center_y:{center_y:5g}, ' + \
                    f'w:{width}, h:{height}, conf:{conf:.2f}, depth:{depth_value_mm:.5g}' + \
                    (f', pose:{self.current_pose_str}' if self._get_robot_poses else ', pose:N/A')
                detections.append(detection_string)

                # Draw bounding box
                cv2.rectangle(cv_image, (x1, y1), (x2, y2), (0, 255, 0), 2)
                cv2.putText(cv_image, f'{cls}:{conf:.2f} d:{depth_value_mm:.3g}', (x1, y1 - 10),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 150), 2)

        # Publish detection results as string
        detection_msg = String()
        detection_msg.data = '; '.join(detections) if detections else "no detections"
        self.publisher_.publish(detection_msg)
        self.get_logger().info(f'Published {len(detections)} detections.')

        # Write detections to file if enabled
        if self._write_to_file:
            # Get current timestamp for unique file naming
            timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
            with open(f'{self._output_dir}/{self._dir_identifier}/_screw_detections.csv', 'a') as f:
                for detection in detections:
                    columns_string = ','.join([f"{d.split(':')[1]}" for d in detection.split(', ')])
                    f.write(f"{timestamp},{columns_string}\n")
            # Save image file
            cv2.imwrite(f'{self._output_dir}/{self._dir_identifier}/img_{timestamp}.jpg', cv_image)

        # Publish annotated image for RViz
        try:
            annotated_msg = self.bridge.cv2_to_imgmsg(cv_image, encoding='bgr8')
            self.image_pub.publish(annotated_msg)
        except Exception as e:
            self.get_logger().error(f'Could not publish annotated image: {e}')

def main(args=None):
    rclpy.init(args=args)
    node = ScrewDetectorNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
