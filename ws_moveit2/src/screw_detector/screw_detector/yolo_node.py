from ament_index_python.packages import get_package_share_directory
import os

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import String
from cv_bridge import CvBridge
import cv2
from ultralytics import YOLO

class ScrewDetectorNode(Node):
    def __init__(self):
        super().__init__('screw_detector_node')

        # Subscribe to input camera images
        self.subscription = self.create_subscription(
            Image,
            '/camera/camera/color/image_raw',
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

    def image_callback(self, msg: Image):
        # Convert ROS Image to OpenCV image
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            self.get_logger().debug(f'Received image: {cv_image.shape}')
        except Exception as e:
            self.get_logger().error(f'Could not convert image: {e}')
            return

        # Run YOLO detection
        results = self.model(cv_image)

        detections = []
        # Draw bounding boxes and collect detection info
        for result in results:
            for obj in result.boxes:
                cls = int(obj.cls[0])
                conf = float(obj.conf[0])
                detections.append(f'class:{cls}, conf:{conf:.2f}')

                # Draw bounding box
                x1, y1, x2, y2 = map(int, obj.xyxy[0])
                cv2.rectangle(cv_image, (x1, y1), (x2, y2), (0, 255, 0), 2)
                cv2.putText(cv_image, f'{cls}:{conf:.2f}', (x1, y1 - 10),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

        # Publish detection results as string
        detection_msg = String()
        detection_msg.data = '; '.join(detections) if detections else "no detections"
        self.publisher_.publish(detection_msg)
        self.get_logger().info(f'Published {len(detections)} detections.')

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
