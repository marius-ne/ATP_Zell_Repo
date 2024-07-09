import rclpy
from rclpy.node import Node

from std_msgs.msg import String

from robo_planner_py import Task
from robo_planner_py import Serializer
from robo_planner_py import Pose
from robo_planner_py import Logger
from robo_planner_py import Opcua
import json



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
    minimal_publisher = MinimalPublisher()
    Logger.Instance = Logger.Logger(minimal_publisher)
    
    # setup task list

    #Carrier
    
    program = Task.TaskBase()
    program._id = "Program"
    program._name = "Pick and Place"

    moveCarrier1 = Task.TaskMoveToPose()
    moveCarrier1._name = "Move Appproach to carrier"
    moveCarrier1._moveType = Task.RobotMoveType.AbsoluteCartesian
    moveCarrier1._targetPose = Pose.Pose()
    moveCarrier1._targetPose._x = 10
    moveCarrier1._targetPose._y = 5
    moveCarrier1._targetPose._z = 2
    program.AddSubtask(moveCarrier1)

    openGripperCarrier = Task.TaskOpcuaRequest()
    openGripperCarrier._name = "Open gripper carrier"
    openGripperCarrier._opcuaData = Opcua.OpcuaCmds["GreiferWriteAuf"]
    openGripperCarrier._opcuaData = Opcua.OpcuaData()
    #openGripperCarrier._opcuaData.GreiferWriteAuf()
    program.AddSubtask(openGripperCarrier)

    moveCarrier2 = Task.TaskMoveToPose()
    moveCarrier2._name = "Move Execute to carrier"
    moveCarrier2._moveType = Task.RobotMoveType.AbsoluteCartesian
    moveCarrier2._targetPose._x = 10
    moveCarrier2._targetPose._y = 5
    moveCarrier2._targetPose._z = 1
    program.AddSubtask(moveCarrier2)

    closeGripperCarrier = Task.TaskOpcuaRequest()
    closeGripperCarrier._name = "Close gripper carrier"
    closeGripperCarrier._opcuaData = Opcua.OpcuaCmds["GreiferWriteZu"]
    closeGripperCarrier._opcuaData = Opcua.OpcuaData()
    closeGripperCarrier._opcuaData.GreiferWriteZu()
    program.AddSubtask(closeGripperCarrier)

    moveCarrier3 = Task.TaskMoveToPose()
    moveCarrier3._name = "Move Finish to carrier"
    moveCarrier3._moveType = Task.RobotMoveType.AbsoluteCartesian
    moveCarrier3._targetPose._x = 10
    moveCarrier3._targetPose._y = 5
    moveCarrier3._targetPose._z = 2
    program.AddSubtask(moveCarrier3)

    # BEMI
    moveBemi1 = Task.TaskMoveToPose()
    moveBemi1._name = "Move Appproach to Bemi"
    moveBemi1._moveType = Task.RobotMoveType.AbsoluteCartesian
    moveBemi1._targetPose._x = 10
    moveBemi1._targetPose._y = 5
    moveBemi1._targetPose._z = 2
    program.AddSubtask(moveBemi1)


    openBemi = Task.TaskOpcuaRequest()
    openBemi._name = "Open Bemi"
    openBemi._opcuaData = Opcua.OpcuaCmds["BemiWriteAuf"]
    openBemi._opcuaData = Opcua.OpcuaData()
    openBemi._opcuaData.BemiWriteAuf()
    program.AddSubtask(openBemi)

    movebemi2 = Task.TaskMoveToPose()
    movebemi2._name = "Move Execute to Bemi"
    movebemi2._moveType = Task.RobotMoveType.AbsoluteCartesian
    movebemi2._targetPose._x = 10
    movebemi2._targetPose._y = 5
    movebemi2._targetPose._z = 1
    program.AddSubtask(movebemi2)

    closeGripperBemi = Task.TaskOpcuaRequest()
    closeGripperBemi._name = "Close Bemi"
    closeGripperBemi._opcuaData = Opcua.OpcuaCmds["BemiWriteZu"]
    closeGripperBemi._opcuaData = Opcua.OpcuaData()
    closeGripperBemi._opcuaData.BemiWriteZu()
    program.AddSubtask(closeGripperBemi)

    openGripperBemi = Task.TaskOpcuaRequest()
    openGripperBemi._name = "Open gripper Bemi"
    openGripperBemi._opcuaData = Opcua.OpcuaCmds["GreiferWriteAuf"]
    openGripperBemi._opcuaData = Opcua.OpcuaData()
    openGripperBemi._opcuaData.GreiferWriteAuf()
    program.AddSubtask(openGripperBemi)

    moveBemi3 = Task.TaskMoveToPose()
    moveBemi3._name = "Move Finish to Bemi"
    moveBemi3._moveType = Task.RobotMoveType.AbsoluteCartesian
    moveBemi3._targetPose._x = 10
    moveBemi3._targetPose._y = 5
    moveBemi3._targetPose._z = 2
    program.AddSubtask(moveBemi3)
    program.__dict__
    testjson = Task.TestSerializationClass()
    
    Logger.Instance.LogInfo("installed ssyslink ")

    testdic = program.AsDictionary()
    Logger.Instance.LogInfo("Testdic start")
    #Logger.Instance.LogInfo(testdic)
    Logger.Instance.LogInfo("Testdic end")
    


    serializedString = ""
    #serializedString = program.Serialize(serializedString)
    serializedString = json.dumps(testdic)

    path = "/home/aw/serialization/test.json"

    Serializer.SerializeClass(testdic, path)
    deserialized = Serializer.DeserializeClass(path)
    deserializedProgram = Task.TaskBase.Deserialize(deserialized)
    deserializedDict = deserializedProgram.AsDictionary()

    Logger.Instance.LogInfo("Serialization 2 start")

    Serializer.SerializeClass(deserializedDict, "/home/aw/serialization/test2.json")

    Logger.Instance.LogInfo("Serialization 2 end")

    #f = open("/home/aw/serialization/test.json", "w")
    #f.write(serializedString)
    #f.close()

    #Logger.Instance.LogInfo(program.__dict__)
    #Serializer.SerializeClass(program, "/home/aw/serialization/test.json")

    return

    
    rclpy.spin(minimal_publisher)
    

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()