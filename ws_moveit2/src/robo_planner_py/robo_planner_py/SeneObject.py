from Pose import Pose
from Pose import Transform

class SceneObject:

    _id : str

    # origin of the scene object
    _transformOrigin : Transform

    # robot approach transform
    _transformApproach : Transform

    # the transform in which the execution happens (e.g. pick/place position)
    _transformExecution : Transform

    # the reference key to the corresponding collision object of the scene object
    _collisionObjectKey : str

    # the reference key to the corresponding visualization mesh to display
    _meshObjectKey : str


class SceneObjectPart:
    pass

class SceneObjectEquipment:
    pass
