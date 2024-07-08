import rclpy
from rclpy.node import Node


class Logger():
    
    
    def __init__(self, node : Node) -> None:
        self._node = node

    def LogInfo(self, content : str) -> None:
        self._node.get_logger().info(content)

    def LogWarning(self, content : str) -> None:
        self.__node.get_logger().info(content)

    def LogFatal(self, content : str) -> None:
        self.__node.get_logger().fatal(content)

    def LogError(self, content : str) -> None:
        self.__node.get_logger().error(content)

    _node : Node

Instance : Logger





