import robo_planner_py.Opcua

class ActorOperation:
    _displayName : str
    _key : str
    _opcuaData : robo_planner_py.Opcua.OpcuaData

    def Execute(self):
        robo_planner_py.Opcua.Instance.OpcuaActuatorWrite(self._opcuaData)
    

