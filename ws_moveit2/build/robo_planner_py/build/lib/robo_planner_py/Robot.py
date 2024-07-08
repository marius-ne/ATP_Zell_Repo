
from robo_planner_py.Pose import Pose
from robo_planner_py.Logger import Logger

class Robot:
    def __init__(self):
        pass
    
    # input: list of 'Pose' objects
    def FollowTrajectory(self, points):
        # todo: make the ros service call
        pass

    def MoveToPose(targetPose : Pose, moveType):
        # todo: make ros service call
        pass

    def SetVelocity(self, value : float):
        # todo: set the velocity of the robot
        pass

class RobotDummy():
    def FollowTrajectory(self, points):
        Logger.LogInfo("Robot dummy - FollowTrajectory")

    def MoveToPose(targetPose : Pose, moveType):
        Logger.LogInfo("Robot dummy - MoveToPose")
        pass

    def SetVelocity(self, value : float):
        Logger.LogInfo("Robot dummy - SetVelocity")
        pass


robot = RobotDummy()

