class Pose:
    def __init__(self):
        self._x = 0
        self._y = 0
        self._z = 0
        self._i = 0
        self._j = 0
        self._k = 0
        self._w = 0

    def __init__(self, x : float, y : float, z : float):
        self._x = x
        self._y = y
        self._z = z
        self._i = 0
        self._j = 0
        self._k = 0
        self._w = 0


    _x : float
    _y : float
    _z : float
    _i : float
    _j : float
    _k : float
    _w : float

    def AsDictionary(self):
        self.__dict__.keys
        return self.__dict__
    
    def Deserialize(dictionary):
        pose = Pose()
        
        for entry in dictionary:
            pose.__setattr__(entry, dictionary[entry])

        return pose

class Transform:
    def __init__(self):
        _parent = None # parent of type 'Transform'
        _children = [] # children of type 'Transform'

    _poseRelative : Pose
    _poseAbsolute : Pose
    _id : str

    