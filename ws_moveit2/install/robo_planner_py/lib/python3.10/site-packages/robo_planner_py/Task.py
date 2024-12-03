from collections.abc import Iterable
from robo_planner_py.Pose import Transform
from robo_planner_py.Pose import Pose
from robo_planner_py.Robot import Robot
import robo_planner_py.Robot
from enum import Enum
import time
from robo_planner_py.Opcua import OpcuaData
import robo_planner_py.Opcua


class TaskBase:
    CurrentTabsCount = 0
    CurrentTabs = ""

    def __init__(self):
        self._subtasks = []
        self._type = self.GetType()

    def GetType(self):
        return str(TaskBase.__name__)

    def AsDictionary(self):
        dictionary = {
            "Type": self.GetType(),
            "Id": self._id,
            "Name": self._name
        }
        
        self.AddDictionaryValues(dictionary)

        list = []
        for subtask in self._subtasks:
            list.append(subtask.AsDictionary())

        dictionary["Subtasks"] = list

        return dictionary    
    
    def AddDictionaryValues(self, dictionary):
        pass

    def AddSubtask(self, subtask):
        self._subtasks.append(subtask)

    def Execute(self) -> bool:
        self.LogStart()

        for subtask in self._subtasks:
            if subtask.Execute() == False:
                return False

        self.LogEnd()
        return True
    
    def Deserialize(dict):
        type = dict["Type"]
        instance : TaskBase

        if type == str(TaskBase.__name__):
            instance = TaskBase()
        if type == str(TaskFollowTrajectory.__name__):
            instance = TaskFollowTrajectory()
        if type == str(TaskMoveToPose.__name__):
            instance = TaskMoveToPose()
        if type == str(TaskOpcuaRequest.__name__):
            instance = TaskOpcuaRequest()
        if type == str(TaskWait.__name__):
            instance = TaskWait()

        instance._id = dict["Id"]
        instance._name = dict["Name"]
        instance.DeSerializeContent(dict)

        for subtaskDict in dict["Subtasks"]:
            instanceSubtask = TaskBase.Deserialize(subtaskDict)
            instance._subtasks.append(instanceSubtask)

        return instance
        

    def DeSerializeContent(self, dictionary):
        pass

    def LogStart(self):
        pass

    def LogEnd(self):
        pass

    _id : str
    _name : str
    _type: str



class TaskFollowTrajectory(TaskBase):
    def __init__(self) -> None:
        TaskBase.__init__(self)
        self._id = "Follow Trajectory"
        self._targetPoses = [] # list of type 'Pose'

    def GetType(self):
        return str(TaskFollowTrajectory)

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
        TaskBase.__init__(self)
        self._id = "Move to Pose"
        self._moveType = RobotMoveType.AbsoluteCartesian
        self._targetPose = Pose()

    def GetType(self):
        return str(TaskMoveToPose.__name__)

    def Execute(self) -> bool:
        TaskBase.LogStart()
        Robot.robot.MoveToPose(self._targetPose, self._moveType)
        TaskBase.LogEnd()

        return True

    def DeSerializeContent(self, dictionary):
        self._targetPose = Pose.Deserialize(dictionary["TargetPose"])
        moveType = dictionary["MoveType"]

        if moveType == 1:
            self._moveType = RobotMoveType.AbsolutePTP
        if moveType == 2:
            self._moveType = RobotMoveType.RelativePTP
        if moveType == 3:
            self._moveType = RobotMoveType.AbsoluteCartesian
        if moveType == 4:
            self._moveType = RobotMoveType.RelativeCartesian

        self._moveType = moveType


    def AddDictionaryValues(self, dictionary):
        dictionary["TargetPose"] = self._targetPose.AsDictionary()
        dictionary["MoveType"] = 1

    _targetPose : Pose
    _moveType : int


class TaskOpcuaRequest(TaskBase):
    def __init__(self) -> None:
        TaskBase.__init__(self)
        self._id = "Opcua request"
        self._opcuaData = OpcuaData()
        
    def GetType(self):
        return str(TaskOpcuaRequest.__name__)
        
    def Execute(self) -> bool:
        TaskBase.LogStart()
        robo_planner_py.Opcua.Instance.OpcuaActuatorWrite(self._opcuaData)
        TaskBase.LogEnd()

    def AddDictionaryValues(self, dictionary):
        if self._opcuaData == None:
            print ("Opcuadata is null")

        dictionary["OpcuaData"] = self._opcuaData.AsDictionary()

    def DeSerializeContent(self, dictionary):
        self._targetPose = OpcuaData.Deserialize(dictionary["OpcuaData"])

    _opcuaData : OpcuaData



class SetRobotValueVelocity(TaskBase):

    _velocity : float
    _acceleration : float
    _type : int # 0 = ompl PTP; 1 = PILZ linear/cartesian movement

    def __init__(self) -> None:
        TaskBase.__init__(self)
        self._id = "Set robot velocity"
        self._velocity = 1.0
        self._acceleration = 1.0
        self._type = 0

    def GetType(self):
        return str(SetRobotValueVelocity.__name__)

    def Execute(self) -> bool:
        TaskBase.LogStart()
        Robot.robot.SetVelocity(self._velocity, self._acceleration, self._type)
        TaskBase.LogEnd()
            
    def AddDictionaryValues(self, dictionary):
        dictionary["Velocity"] = self._velocity
        dictionary["Acceleration"] = self._acceleration
        dictionary["Type"] = self._type


class TaskWait(TaskBase):
    
    def __init__(self) -> None:
        TaskBase.__init__(self)
        self._id = "Wait"
        self._value = 1.0

    def GetType(self):
        return str(TaskWait.__name__)

    def Execute(self) -> bool:
        TaskBase.LogStart()
        time.sleep(self._value)
        TaskBase.LogEnd()

    _value : float # sleep time in seconds


