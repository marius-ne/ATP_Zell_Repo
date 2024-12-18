from robo_planner_py.ActorOperation import ActorOperation

class GripperBase:
    def __init__(self):
        pass

    _id : str
    _displayName : str
    _operations : dict[str, ActorOperation]

    def AsDisctionary(self):
        return { 
            "Id": self._id,
            "DisplayName": self._displayName,
            "Operations": self._operations 
        }

    def Deserialize(dict):
        instance = GripperBase()
        instance._id = dict["Id"]
        instance._displayName = dict["DisplayName"]
        instance._operations = dict["Operations"]

    def Execute(self, operationKey : str) -> None:
        self._operations[operationKey].Execute()




