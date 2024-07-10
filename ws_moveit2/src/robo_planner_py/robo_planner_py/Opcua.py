import opcua_interfaces.msg
from robo_planner_py.Logger import Logger
from rclpy.node import Node
import opcua_interfaces
from opcua_interfaces.msg import ActuatorWrite

class OpcuaData:
    def __init__(self):
        self._actuatorId = ""
        self._actuatorWriteType = -1
        self._actuatorReadType = -1
        self._actuatorCommandBool1 = False
        self._actuatorCommandBool2 = False

    def AsDictionary(self):
        return { 
            "ActuatorId": self._actuatorId,
            "ActuatorWriteType": self._actuatorWriteType,
            "ActuatorReadType": self._actuatorReadType,
            "ActuatorCommandBool1": self._actuatorCommandBool1,
            "ActuatorCommandBool2": self._actuatorCommandBool2
        }
    
    def Deserialize(dictionary):
        instance = OpcuaData()
        
        for entry in dictionary:
            instance.__setattr__(entry, dictionary[entry])

    @classmethod
    def AlarmWriteAus(self):
        self._actuatorId = "ns=4;i=5016"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = False

    @classmethod
    def AlarmWriteAn(self):
        self._actuatorId = "ns=4;i=5016"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = True

    @classmethod
    def FarbeWriteAus(self):
        self._actuatorId = "ns=4;i=5019"
        self._actuatorWriteType = 2
        self._actuatorCommandBool1 = False
        self._actuatorCommandBool2 = False

    @classmethod
    def FarbeWriteRot(self):
        self.actuatorId = "ns=4;i=5019"
        self.actuatorWriteType = 2
        self.actuatorCommandBool1 = True
        self.actuatorCommandBool2 = False

    @classmethod
    def FarbeWriteOrange(self):
        self._actuatorId = "ns=4;i=5019"
        self._actuatorWriteType = 2
        self._actuatorCommandBool1 = False
        self._actuatorCommandBool2 = True

    @classmethod
    def FarbeWriteGruen(self):
        self._actuatorId = "ns=4;i=5019"
        self._actuatorWriteType = 2
        self._actuatorCommandBool1 = True
        self._actuatorCommandBool2 = True

    @classmethod
    def TuerWriteStop(self):
        self._actuatorId = "ns=4;i=5040"
        self._actuatorWriteType = 2
        self._actuatorCommandBool1 = False
        self._actuatorCommandBool2 = False

    @classmethod
    def TuerWriteAuf(self):
        self._actuatorId = "ns=4;i=5040"
        self._actuatorWriteType = 2
        self._actuatorCommandBool1 = True
        self._actuatorCommandBool2 = False    

    @classmethod
    def TuerWriteZu(self):
        self._actuatorId = "ns=4;i=5040"
        self._actuatorWriteType = 2
        self._actuatorCommandBool1 = False
        self._actuatorCommandBool2 = True

    @classmethod
    def TuerRead(self):
        self._actuatorId = "ns=4;i=5040"
        self._actuatorReadType = 2

    @classmethod
    def SpindelWriteAus(self):
        self._actuatorId = "ns=4;i=5015"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = False
    
    @classmethod
    def SpindelWriteAn(self):
        self._actuatorId = "ns=4;i=5015"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = True

    @classmethod
    def AnpressdruckSpindelWriteAn(self):
        self._actuatorId = "ns=4;i=5006"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = True
        self._actuatorCommandBool2 = True

    @classmethod
    def AnpressdruckSpindelWriteAus(self):
        self._actuatorId = "ns=4;i=5006"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = True
        self._actuatorCommandBool2 = False

    @classmethod
    def GreiferWriteAuf(self):
        self._actuatorId = "ns=4;i=5004"
        self._actuatorWriteType = 2
        self._actuatorCommandBool1 = False
        self._actuatorCommandBool2 = False

    @classmethod
    def GreiferWriteZu(self):
        self._actuatorId = "ns=4;i=5004"
        self._actuatorWriteType = 2
        self._actuatorCommandBool1 = True
        self._actuatorCommandBool2 = True
    
    @classmethod
    def GreiferWriteNeutral(self):
        self._actuatorId = "ns=4;i=5004"
        self._actuatorWriteType = 2
        self._actuatorCommandBool1 = True
        self._actuatorCommandBool2 = True

    @classmethod
    def BemiWriteAuf(self):
        self._actuatorId = "ns=4;i=5008"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = False 

    @classmethod
    def BemiWriteZu(self):
        self._actuatorId = "ns=4;i=5008"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = True

    @classmethod
    def Bemi2WriteAuf(self):
        self._actuatorId = "ns=4;i=5007"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = False 

    @classmethod
    def Bemi2WriteZu(self):
        self._actuatorId = "ns=4;i=5007"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = True

    @classmethod
    def Bemi3WriteAuf(self):
        self._actuatorId = "ns=4;i=5003"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = False 

    @classmethod
    def Bemi3WriteZu(self):
        self._actuatorId = "ns=4;i=5003"
        self._actuatorWriteType = 1
        self._actuatorCommandBool1 = True

    _actuatorId : str
    _actuatorWriteType : int
    _actuatorReadType : int
    _actuatorCommandBool1 : bool
    _actuatorCommandBool2 : bool


OpcuaCmds = { "AlarmWriteAus": OpcuaData.AlarmWriteAus(),
              "AlarmWriteAn": OpcuaData.AlarmWriteAn(),
              "FarbeWriteAus": OpcuaData.FarbeWriteAus(),
              "FarbeWriteRot": OpcuaData.FarbeWriteRot(),
              "FarbeWriteOrange": OpcuaData.FarbeWriteOrange(),
              "FarbeWriteGruen": OpcuaData.FarbeWriteGruen(),
              "TuerWriteStop": OpcuaData.TuerWriteStop(),
              "TuerWriteAuf": OpcuaData.TuerWriteAuf(),
              "TuerWriteZu": OpcuaData.TuerWriteZu(),
              "TuerRead": OpcuaData.TuerRead(),
              "SpindelWriteAus": OpcuaData.SpindelWriteAus(),
              "SpindelWriteAn": OpcuaData.SpindelWriteAn(),
              "AnpressdruckSpindelWriteAus": OpcuaData.AnpressdruckSpindelWriteAus(),
              "GreiferWriteAuf": OpcuaData.GreiferWriteAuf(),
              "GreiferWriteZu": OpcuaData.GreiferWriteZu(),
              "GreiferWriteNeutral": OpcuaData.GreiferWriteNeutral(),
              "BemiWriteAuf": OpcuaData.BemiWriteAuf(),
              "BemiWriteZu": OpcuaData.BemiWriteZu(),
              "Bemi2WriteAuf": OpcuaData.Bemi2WriteAuf(),
              "Bemi2WriteZu": OpcuaData.Bemi2WriteZu(),
              "Bemi3WriteAuf": OpcuaData.Bemi3WriteAuf(),
              "Bemi3WriteZu": OpcuaData.Bemi3WriteZu(),
}    

class OpcuaInterface():
    def __init__(self, node : Node) -> None:
        self.opcua_actuator_write_publisher_ = node.create_publisher(ActuatorWrite, "Actuator_Write", 10)

    def OpcuaActuatorWrite(self, data : OpcuaData):
        msg = ActuatorWrite()
        msg.actuator_id = data.actuatorId
        msg.actuator_write_type = data.actuatorWriteType

        if data.actuatorWriteType == 1:
            msg.actuator_command_bool1 = data.actuatorCommandBool1

        if data._actuatorWriteType == 2:
            msg.actuator_command_bool1 = data.actuatorCommandBool1
            msg.actuator_command_bool2 = data.actuatorCommandBool2

        self.opcua_actuator_write_publisher_.publish(msg)


class OpcuaInterfaceDummy:
    def OpcuaActuatorWrite(self, data : OpcuaData):
        Logger.LogInfo("Opcua call")

Instance = OpcuaInterfaceDummy()