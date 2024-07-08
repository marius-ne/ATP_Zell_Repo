from collections.abc import Iterable
from robo_planner_py.Pose import Transform
from robo_planner_py.Pose import Pose
from robo_planner_py.Robot import Robot
import robo_planner_py.Robot
from enum import Enum
import time
from robo_planner_py import OpcuaInterface

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

    def LogStart(self):
        pass

    def LogEnd(self):
        pass

    _id : str
    _name : str



class TaskFollowTrajectory(TaskBase):
    def __init__(self) -> None:
        TaskBase.__init__(self)
        self._id = "Follow Trajectory"
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
        TaskBase.__init__(self)
        self._id = "Move to Pose"
        self._moveType = RobotMoveType.AbsoluteCartesian
        self._targetPose = Pose()

    def Execute(self) -> bool:
        TaskBase.LogStart()
        Robot.robot.MoveToPose(self._targetPose, self._moveType)
        TaskBase.LogEnd()

        return True

    def SerializeContent(self, content : str) -> str:
        SerializeVarName("MovementType", self._moveType.name)
        SerializeVarName("TagetPose", "X: " + str(self._targetPose._x) + ", Y: " + str(self._targetPose._y) + ", Z: " + str(self._targetPose._z))

        return content

    _targetPose : Pose
    _moveType : RobotMoveType


class TaskOpcuaRequest(TaskBase):
    def __init__(self) -> None:
        TaskBase.__init__(self)
        self._id = "Opcua request"
        self._opcuaData = OpcuaInterface.OpcuaData()
        
        
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


    #_opcuaData : OpcuaInterface.OpcuaData



class SetRobotValueVelocity(TaskBase):

    _value : float

    def __init__(self) -> None:
        TaskBase.__init__(self)
        self._id = "Set robot velocity"
        self._value = 1.0

    def Execute(self) -> bool:
        TaskBase.LogStart()
        Robot.robot.SetVelocity(self._value)
        TaskBase.LogEnd()

    def SerializeContent(self, content : str) -> str:
        content += SerializeVarName("Value", self._value)

        return content


class TaskWait(TaskBase):
    
    def __init__(self) -> None:
        TaskBase.__init__(self)
        self._id = "Wait"
        self._value = 1.0

    def Execute(self) -> bool:
        TaskBase.LogStart()
        time.sleep(self._value)
        TaskBase.LogEnd()

    def SerializeContent(self, content : str) -> str:
        content += SerializeVarName("Value", self._value)

        return content

    _value : float # sleep time in seconds


