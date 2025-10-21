import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState

class LeRobotDataCollector(Node):
    def __init__(self):
        super().__init__('lerobot_data_collector')
        self.get_logger().info('LeRobot Data Collection Node started')

        # TODO: 
        # -Add subscription to camera topic
        # -Add subscription to joint angle goals (only relevant when commanding robot?)
        # /iiwa_arm_controller/state or  moveit_msgs/msg/DisplayTrajectory
        # -Add ability to load existing dataset
        # -Add ability to start/stop recording and keep/discard frames, perhaps with some UI
        # -Add ability to correct differences in timestamps between data sources
        # -Add ability to add recorded frame to loaded dataset when choosing to keep it
        # -Add ability to save dataset to disk, perhaps with some UI

        
        self.joint_sub = self.create_subscription(JointState, '/joint_states', self.joint_callback, 10)
        
    def joint_callback(self, msg):
        self.get_logger().info(f'Received joint states: {msg.name}')

def main(args=None):
    rclpy.init(args=args)
    node = LeRobotDataCollector()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()