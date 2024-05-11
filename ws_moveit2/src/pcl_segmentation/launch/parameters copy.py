from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="pcl_segmentation",
            executable="file_publisher",
            name="file_publisher_param_node",
            output="screen",
            emulate_tty=True,
            parameters=[
                {"file_path": "/home/aw/restackcell/ws_moveit2/src/pcl_segmentation/data/0.ply"}
                {"publisher_name": "/test_publisher"}
            ]
        )
    ])