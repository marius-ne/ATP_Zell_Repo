from robo_planner_py.Pose import Pose
from robo_planner_py.Pose import Transform
import robo_planner_py.Core

class SceneObjectPrefab:

    def __init__(self, id : str) -> None:
        self._ = id
        SceneObjectInstanceContainer[id] = self

    def AsDictionary(self):
        return { 
            "Id", self._id,
            "Type", self.GetType(),
            "TransformOrigin", self._transformOrigin.AsDictionary(),
            "TransformApproach", self._transformApproach.AsDictionary(),
            "TransformExecution", self._transformExecution.AsDictionary(),
            "CollisionObjectKey", self._collisionObjectKey,
            "MeshObjectKey", self._meshObjectKey }

    def DeSerialize(self, dict):
        type = dict["Type"]
        instance : SceneObjectPrefab

        if type == str(SceneObjectPrefab.__name__):
            instance = SceneObjectPrefab()
        if type == str(SceneObjectPartPrefab.__name__):
            instance = SceneObjectPartPrefab()
        if type == str(SceneObjectEquipmentPrefab.__name__):
            instance = SceneObjectEquipmentPrefab()

        instance._id = dict["Id"]
        instance._type = dict["Type"]
        instance._transformOrigin = dict["TransformOrigin"].Deserialize()
        instance._transformApproach = dict["TransformApproach"].Deserialize()
        instance._transformExecution = dict["TransformExecution"].Deserialize()
        instance._collisionObjectKey = dict["CollisionObjectKey"]
        instance._meshObjectKey = dict["MeshObjectKey"]

        instance.DeSerializeContent(dict)

        return instance

    def GetType(self):
        return str(SceneObjectPrefab.__name__)

    def DeSerializeContent(self, dict):
        pass

    _id : str
    _type : str

    # origin of the scene object
    _transformOrigin : Pose

    # robot approach transform
    _transformApproach : Pose

    # the transform in which the execution happens (e.g. pick/place position)
    _transformExecution : Pose

    # the reference key to the corresponding collision object of the scene object
    _collisionObjectKey : str

    # the reference key to the corresponding visualization mesh to display
    _meshObjectKey : str


class SceneObjectPartPrefab:

    def GetType(self):
        return str(SceneObjectPartPrefab.__name__)
    
    def DeSerializeContent(self, dict):
        pass

class SceneObjectEquipmentPrefab:
    
    def GetType(self):
        return str(SceneObjectEquipmentPrefab.__name__)
    
    def DeSerializeContent(self, dict):
        pass

class SceneObjectInstance:

    _id : str
    _prefab : SceneObjectPrefab

    def __init__(self, prefab : SceneObjectPrefab, id : str) -> None:
        self._id = id
        self._prefab = prefab
        SceneObjectInstanceContainer[self._id] = self

    def GenerateId(prefab : SceneObjectPrefab) -> str:
        return prefab._id + robo_planner_py.Core.GetNextId()

    def AsDictionary(self):
        return { 
            "Id", self._id,
            "PrefabId", self._prefab._id 
        }
    
    def DeSerialize(self, dict):
        instance = SceneObjectInstance()
        instance._id = dict["Id"]
        instance._prefab = SceneObjectPrefabContainer[dict["PrefabId"]]

SceneObjectPrefabContainer : dict[str, SceneObjectPrefab]
SceneObjectInstanceContainer : dict[str, SceneObjectInstance]