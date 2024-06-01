import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from enum import Enum



from robo_planner_py import Robot

#region Transformations

class Pose:
    _x : float
    _y : float
    _z : float
    _rx : float
    _ry : float
    _rz : float
    _rw : float

#endregion

#region Grippers

class GripperBase:
    pass

#endregion

#region Robots

class RobotMoveType(Enum):
    AbsolutePTP = 1
    RelativePTP = 2
    AbsoluteCartesian = 3
    RelativeCartesian = 4

class Robot:
    def __init__(self):
        _positionX = 1
    
    # service calll of a move to pose cmd to the robot backend which then calculates the robot trajectory and send it to the simulated or real robot 
    def MoveToPose(targetPose : Pose, moveType : RobotMoveType):
        pass

    # the robot tcp follows a trjaevtory containing a list of fixed points
    def FollowTrajectory(points): # list of Pose
        pass

    # detaches an attached part from the robot and places it back into the scene 
    def PartAttach(partKey : str):
        pass

    def PartDetach():
        pass

    def SetVelocity(value : float):
        pass

    _gripper : GripperBase

#endregion

#region Tasks

#region Misc

class TaskBase:
    def __init__(self, id):
        self._id = id

    def Execute(self):
        pass

    _id : str

class TaskList(TaskBase):
    def Execute(self):
        for subtask in self._subtasks:
            subtask.Execute()

    def LogStart():
        pass

    def LogEnd():
        pass
    
    _test : int
    _subtasks : list[TaskBase]

#endregion

#region Atomic Tasks

class TaskFollowTrajectory:
    def Execute(self):


#endregion

#region Composed Tasks

#endregion

#endregion


class MinimalPublisher(Node):

    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(String, 'topic', 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = String()
        msg.data = 'Hello World: %d' % self.i
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)
        self.i += 1


def main(args=None):
    rclpy.init(args=args)

    rob = Robot2()
    

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()