import rclpy
from rclpy.node import Node

from geometry_msgs.msg import Pose
from wzlscheduler_interfaces.msg import LabeledPose
from wzlscheduler_interfaces.msg import LabeledPoses


class ImageToWorldPublisher(Node):

    def __init__(self):
        super().__init__('image_to_world')

        # initialize variables
        self.poses = []

        self.offset_x = 0.15
        self.offset_y = 0.15
        self.gapsize_x = 0.1
        self.gapsize_y = 0.1
        self.poses_snapped = []

        # create publisher
        self.publisher_ = self.create_publisher(LabeledPoses, 'LabeledPosesSnapped', 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

        # create subscriber
        self.subscription = self.create_subscription(
            LabeledPoses,
            'LabeledPoses',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        

    def construct_labeled_pose(self, msg : LabeledPose):
        pose = msg.pose
        
        drillhole_index_x = (int)((pose.position.x - self.offset_x + self.gapsize_x * 0.5) / self.gapsize_x)
        drillhole_index_y = (int)((pose.position.y - self.offset_y + self.gapsize_y * 0.5) / self.gapsize_y)

        pose.position.x = drillhole_index_x * self.gapsize_x + self.offset_x
        pose.position.y = drillhole_index_y * self.gapsize_y + self.offset_y

        msg.pose = pose
        msg.drillholeindexx = drillhole_index_x
        msg.drillholeindexy = drillhole_index_y

        return msg


    def listener_callback(self, msg):
        msg = LabeledPoses()
        self.poses = []

        for element in msg.elements:
            x = element.x
            y = element.y
            width = element.width
            height = element.height

            pose = self.pose_from_boundingbox(x, y, width, height)
            self.poses.append(pose)

        msg.elements = self.poses

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