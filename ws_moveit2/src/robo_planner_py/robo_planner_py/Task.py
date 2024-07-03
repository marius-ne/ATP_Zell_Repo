from Pose import Transform
from Pose import Pose
from Robot import Robot
import Robot

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



class FollowTrajectory:
    def __init__(self) -> None:
        self._targetPoses = [] # list of type 'Pose'

    def AddPose(self, pose : Pose):
         self._targetPoses.append(pose)

    def Execute(self) -> bool:
        TaskBase.LogStart()
        Robot.robot.FollowTrajectory()
        TaskBase.LogEnd()

        return True