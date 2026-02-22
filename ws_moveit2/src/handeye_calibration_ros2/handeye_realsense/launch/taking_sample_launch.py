"""
Copyright © 2024 Shengyang Zhuang. All rights reserved.

Contact: https://shengyangzhuang.github.io/
"""
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition, UnlessCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    # Declare the launch argument
    use_chessboard_arg = DeclareLaunchArgument(
        'use_chessboard',
        default_value='false',
        description='Whether to use the chessboard and marker for pose estimation'
    )

    use_chessboard = LaunchConfiguration('use_chessboard')

    return LaunchDescription([
        use_chessboard_arg,
        Node(
            package='handeye_realsense',
            executable='robot',
            name='robot_state_estimation'
        ),
        # ArUco-only estimation (default)
        Node(
            package='handeye_realsense',
            executable='aruco',
            name='aruco_estimation',
            condition=UnlessCondition(use_chessboard),
        ),
        # ArUco + chessboard estimation (Zivid ZVD-CB01)
        Node(
            package='handeye_realsense',
            executable='chessboard',
            name='chessboard_estimation',
            condition=IfCondition(use_chessboard),
        ),
    ])