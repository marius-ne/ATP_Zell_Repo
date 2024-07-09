from collections.abc import Iterable
from robo_planner_py.Pose import Transform
from robo_planner_py.Pose import Pose
from robo_planner_py.Robot import Robot
import robo_planner_py.Robot
from enum import Enum
import time
from robo_planner_py.Opcua import OpcuaData



class TestSerializationClass:
    def __init__(self):
        self.tesNumber = 10
        self.testStr = "Test"

def SerializeVarName(name : str, content, useComma = True, useLinebreak = True) -> str:
    result = TaskBase.CurrentTabs + "\"" + name + "\": " + content 

    if useComma:
        result += ","

    if useLinebreak:
        result += "\n"

    return result
    

class TaskBase:
    CurrentTabsCount = 0
    CurrentTabs = ""

    def UpdateTabs():
        TaskBase.CurrentTabs = ""
        
        for i in range(TaskBase.CurrentTabsCount):
            TaskBase.CurrentTabs += "\t"

    def TabsIncrease():
        TaskBase.CurrentTabsCount += 1
        TaskBase.UpdateTabs()

    def TabsDecrease():
        TaskBase.CurrentTabsCount -= 1
        TaskBase.UpdateTabs()

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
    
    def Serialize(self, content) -> str:
        content += SerializeVarName("Id", self._id)
        content += SerializeVarName("Name", self._name)

        content = self.SerializeContent(content)
        content += SerializeVarName("Subtasks", "[\n", False, True)

        TaskBase.TabsIncrease()
        
        for subtask in self._subtasks:
            content = subtask.Serialize(content)

        content += "]"

        TaskBase.TabsDecrease()

        return content

    def SerializeContent(self, content : str) -> str:
        return content

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

    def SerializeContent(self, content : str) -> str:
        SerializeVarName("MovementType", self._moveType.name)
        SerializeVarName("TagetPose", "X: " + str(self._targetPose._x) + ", Y: " + str(self._targetPose._y) + ", Z: " + str(self._targetPose._z))

        return content
    
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
        OpcuaInterface.Instance.OpcuaActuatorWrite(self._opcuaData)
        TaskBase.LogEnd()

    def SerializeContent(self, content : str) -> str:
        opcuaContent = "{"
        opcuaContent += "ActuatorId: " + str(self._opcuaData._actuatorId) + ", "
        opcuaContent += "ActuatorWriteType: " + str(self._opcuaData._actuatorWriteType) + ", "
        opcuaContent += "ActuatorReadType: " + str(self._opcuaData._actuatorReadType) + ", "
        opcuaContent += "ActuatorCommandBool1: " + str(self._opcuaData._actuatorCommandBool1) + ", "
        opcuaContent += "ActuatorCommandBool2: " + str(self._opcuaData._actuatorCommandBool2) + ", "
        opcuaContent += "}"

        content += SerializeVarName("OpcuaData", opcuaContent)

        return content

    def AddDictionaryValues(self, dictionary):
        if self._opcuaData == None:
            print ("Opcuadata is null")

        dictionary["OpcuaData"] = self._opcuaData.AsDictionary()


    def DeSerializeContent(self, dictionary):
        self._targetPose = OpcuaData.Deserialize(dictionary["OpcuaData"])


    _opcuaData : OpcuaData



class SetRobotValueVelocity(TaskBase):

    _value : float

    def __init__(self) -> None:
        TaskBase.__init__(self)
        self._id = "Set robot velocity"
        self._value = 1.0

    def GetType(self):
        return str(SetRobotValueVelocity.__name__)

    def Execute(self) -> bool:
        TaskBase.LogStart()
        Robot.robot.SetVelocity(self._value)
        TaskBase.LogEnd()

    def SerializeContent(self, content : str) -> str:
        content += SerializeVarName("Value", self._value)

        return content
    
    def AddDictionaryValues(self, dictionary):
        dictionary["Value"] = self._value


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

    def SerializeContent(self, content : str) -> str:
        content += SerializeVarName("Value", self._value)

        return content

    _value : float # sleep time in seconds


