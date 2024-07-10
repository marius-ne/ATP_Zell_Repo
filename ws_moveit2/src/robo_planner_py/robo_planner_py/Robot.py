
from robo_planner_py.Pose import Pose
from robo_planner_py.Logger import Logger
from rclpy.node import Node
import rclpy

from wzlscheduler_interfaces.srv import RobotMoveToPosition
from wzlscheduler_interfaces.srv import FollowTrajectory
from wzlscheduler_interfaces.srv import RobotSetVelocity
from wzlscheduler_interfaces.srv import SceneObjectAttach
from wzlscheduler_interfaces.srv import SceneObjectDetach


class Robot:
    def __init__(self, node : Node):
        self.node_ = node

        self.serviceRobotMoveToPosition_ = node.create_client(RobotMoveToPosition, "robot_move_to_position")
        self.serviceRobotFollowTrajectory_ = node.create_client(FollowTrajectory, "robot_follow_trajectory")
        self.serviceRobotSetVelocity_ = node.create_client(RobotSetVelocity, "robot_set_velocity")
        self.serviceSceenObjectAttach_ = node.create_client(SceneObjectAttach, "scene_object_attach")
        self.serviceSceenObjectDetach_ = node.create_client(SceneObjectDetach, "scene_object_detach")

        while not self.serviceRobotMoveToPosition_.wait_for_service(timeout_sec=1.0):
            self.node_.get_logger().info('service not available, waiting again...')

        while not self.serviceRobotFollowTrajectory_.wait_for_service(timeout_sec=1.0):
            self.node_.get_logger().info('service not available, waiting again...')

        while not self.serviceRobotSetVelocity_.wait_for_service(timeout_sec=1.0):
            self.node_.get_logger().info('service not available, waiting again...')

        while not self.serviceSceenObjectAttach_.wait_for_service(timeout_sec=1.0):
            self.node_.get_logger().info('service not available, waiting again...')
        
        while not self.serviceSceenObjectDetach_.wait_for_service(timeout_sec=1.0):
            self.node_.get_logger().info('service not available, waiting again...')

    
    # input: list of 'Pose' objects
    def FollowTrajectory(self, points):
        # todo: make the ros service call
        pass

    def MoveToPose(self, targetPose : Pose, moveType):
        request = RobotMoveToPosition.Request()
        request.movetype = moveType
        request.pose = targetPose

        future = self.serviceRobotMoveToPosition_.call_async(request)
        rclpy.spin_until_future_complete(self.node_, future)
        repsonse = future.result()
        Logger.LogInfo("Service result: " + repsonse.result)

    def SetVelocity(self, value : float):
        request = RobotSetVelocity.Request()
        request.value = value

        future = self.serviceRobotSetVelocity_.call_async(request)
        rclpy.spin_until_future_complete(self.node_, future)
        repsonse = future.result()
        Logger.LogInfo("Service result: " + repsonse.result)
        pass

    def PartAttach(self, partKey : str):
        request = SceneObjectAttach.Request()
        request.name = partKey

        future = self.serviceSceenObjectAttach_.call_async(request)
        rclpy.spin_until_future_complete(self.node_, future)
        repsonse = future.result()
        Logger.LogInfo("Service result: " + repsonse.result)

    def PartDetach(self):
        request = SceneObjectDetach.Request()

        future = self.serviceSceenObjectDetach_.call_async(request)
        rclpy.spin_until_future_complete(self.node_, future)
        repsonse = future.result()
        Logger.LogInfo("Service result: " + repsonse.result)

    node_ : Node


class RobotDummy():
    def FollowTrajectory(self, points):
        Logger.LogInfo("Robot dummy - FollowTrajectory")

    def MoveToPose(self, targetPose : Pose, moveType):
        Logger.LogInfo("Robot dummy - MoveToPose")
        pass

    def SetVelocity(self, value : float):
        Logger.LogInfo("Robot dummy - SetVelocity")
        pass


robot = RobotDummy()

