class Pose:
    def __init__(self):
        _x = 0
        _y = 0
        _z = 0
        _i = 0
        _j = 0
        _k = 0
        _w = 0

    _x : float
    _y : float
    _z : float
    _i : float
    _j : float
    _k : float
    _w : float

class Transform:
    def __init__(self):
        _parent = None # parent of type 'Transform'
        _children = [] # children of type 'Transform'

    _poseRelative : Pose
    _poseAbsolute : Pose
    _parent : Transform
    _id : str

    