import robo_planner_py.SeneObject
from rclpy.node import Node
import rclpy
import robo_planner_py.SeneObject

class Scene:
    def __init(self, node : Node):
        self._sceneObjects = { }


    def AddSceneObject(self, key : str, object : robo_planner_py.SeneObject.SceneObject):
        self._sceneObjects[key] = object

    def RemoveSceneObject(self, key : str):
        self._sceneObjects.pop(key)