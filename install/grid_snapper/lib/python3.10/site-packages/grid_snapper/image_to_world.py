import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from geometry_msgs.msg import Pose
from wzlscheduler_interfaces.msg import LabeledBoundingBox
from wzlscheduler_interfaces.msg import LabeledBoundingBoxes
from wzlscheduler_interfaces.msg import LabeledPose
from wzlscheduler_interfaces.msg import LabeledPoses


class ImageToWorldPublisher(Node):

    def __init__(self):
        super().__init__('image_to_world')

        # initialize variables
        self.poses = []

        self.image_offset_x = 300
        self.image_offset_y = 200
        self.image_width = 1920
        self.image_height = 1080
        self.pixel_to_world_scale_x = 0.001
        self.pixel_to_world_scale_y = 0.001
        self.label_world_offset_x = [0, 0, 0, 0, 0]
        self.label_world_offset_y = [0, 0, 0, 0, 0]

        # create publisher
        self.publisher_ = self.create_publisher(LabeledPoses, 'LabeledPoses', 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

        # create subscriber
        self.subscription = self.create_subscription(
            LabeledBoundingBoxes,
            'labeledboundingboxes',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def get_pixel_offset_label_x(self, labelclass):
        offset_world = self.label_world_offset_x[labelclass]
        offset_pixels = offset_world / self.pixel_to_world_scale_x
        return offset_pixels
    
    def get_pixel_offset_label_y(self, labelclass):
        offset_world = self.label_world_offset_y[labelclass]
        offset_pixels = offset_world / self.pixel_to_world_scale_y
        return offset_pixels

    def pose_from_boundingbox(self, x, y, labelclass):
        pose = Pose()
        
        pose._position.x = (x - self.image_offset_x) * self.pixel_to_world_scale_x
        pose._position.y = (y - self.image_offset_y) * self.pixel_to_world_scale_y
        pose._position.z

        pose.orientation.x = 0
        pose.orientation.y = 0
        pose.orientation.z = 0
        pose.orientation.w = 1

        return pose
    

    def listener_callback(self, msg):
        self.poses = []

        for element in msg.elements:
            x = element.x
            y = element.y
            width = element.width
            height = element.height

            pose = self.pose_from_boundingbox(x, y, width, height)
            self.poses.append(pose)
            

    def timer_callback(self):
        msg = LabeledPoses()
        msg.elements = self.poses

        self.publisher_.publish(msg)
        self.get_logger().info('Publishing labeled poses')
        self.i += 1


def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = ImageToWorldPublisher()

    rclpy.spin(minimal_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()