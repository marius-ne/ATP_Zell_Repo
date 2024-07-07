from Pose import Transform
from Pose import Pose
from Robot import Robot
import Robot
from enum import Enum

class TaskBase:
    def __init__(self):
        self.subtasks = []


    def AddSubtask(self, subtask):
        self.subtasks.append(subtask)


    def Execute(self) -> bool:
        self.LogStart()

        for subtask in self.subtasks:
            if subtask.Execute() == False:
                return False

        self.LogEnd()
        return True
    

    def LogStart(self):
        pass

    def LogEnd(self):
        pass

    _id : str



class TaskFollowTrajectory(TaskBase):
    def __init__(self) -> None:
        self._targetPoses = [] # list of type 'Pose'

    def AddPose(self, pose : Pose):
         self._targetPoses.append(pose)

    def Execute(self) -> bool:
        TaskBase.LogStart()
        Robot.robot.FollowTrajectory(self._targetPoses)
        TaskBase.LogEnd()

        return True
    
class RobotMoveType(Enum):    
    AbsolutePTP = 1
    RelativePTP = 2
    AbsoluteCartesian = 3
    RelativeCartesian = 4

class TaskMoveToPose(TaskBase):
    def __init__(self) -> None:
        pass

    def Execute(self) -> bool:
        TaskBase.LogStart()
        Robot.robot.MoveToPose(self._targetPose, self._moveType)
        TaskBase.LogEnd()

        return True

    _targetPose : Pose
    _moveType : RobotMoveType


class OpcuaData:
    _actuatorId : str
    _actuatorWriteType : int
    _actuatorReadType : int
    _actuatorCommandBool1 : bool
    _actuatorCommandBool2 : bool

class TaskOpcuaRequest(TaskBase):
    def __init__(self) -> None:
        pass

    _opcuaData : OpcuaData

    def Execute(self) -> bool:
        TaskBase.LogStart()
        # todo: send the opcua data via service request to the opcua client node
        TaskBase.LogEnd()
