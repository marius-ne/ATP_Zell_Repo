"""
Launch file for the full screw localization pipeline.

Starts (in order, with delays):
  1. RealSense camera
  2. pose_getter          (needs iiwa_ros2 running & connected)
  3. screw_detector
  4. screw_depth_localizer
  5. screw_segmentor
  6. run_localization      (helper / orchestrator node)

Usage:
    ros2 launch screw_localizer screw_localization.launch.py

Override defaults:
    ros2 launch screw_localizer screw_localization.launch.py \
        ee_frame:=camera_custom \
        camera_config_json:=/path/to/config.json \
        launch_rviz:=true
"""

import os

from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    TimerAction,
)
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import (
    LaunchConfiguration,
    PathJoinSubstitution,
)
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    # ── Launch arguments ────────────────────────────────────────────────
    camera_config_json_arg = DeclareLaunchArgument(
        'camera_config_json',
        default_value=os.path.join(
            os.path.expanduser('~'),
            'ATP25_26_Gruppe6_Entschraubung',
            'camera_config',
            'camera_for_screw_with_depth_config.json',
        ),
        description='Absolute path to the RealSense JSON config file',
    )

    ee_frame_arg = DeclareLaunchArgument(
        'ee_frame',
        default_value='camera_custom',
        description='End-effector frame used by pose_getter',
    )

    get_robot_poses_arg = DeclareLaunchArgument(
        'get_robot_poses',
        default_value='true',
        description='Whether screw_detector fetches robot poses',
    )

    reject_too_few_detections_arg = DeclareLaunchArgument(
        'reject_too_few_detections',
        default_value='false',
        description='Whether screw_detector rejects too-few detections',
    )

    launch_rviz_arg = DeclareLaunchArgument(
        'launch_rviz',
        default_value='false',
        description='Start rviz2 for visualisation',
    )

    # ── 1. RealSense camera ────────────────────────────────────────────
    realsense_camera = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([
                FindPackageShare('realsense2_camera'),
                'launch',
                'rs_launch.py',
            ])
        ),
        launch_arguments={
            'rgb_camera.color_profile': '1280x720x15',
            'depth_module.depth_profile': '1280x720x15',
            'enable_rgbd': 'true',
            'enable_sync': 'true',
            'align_depth.enable': 'true',
            'enable_color': 'true',
            'enable_depth': 'true',
            'json_file_path': LaunchConfiguration('camera_config_json'),
            'initial_reset': 'true',
        }.items(),
    )

    # ── 2. Pose getter (requires iiwa_ros2 to be running) ──────────────
    pose_getter_node = Node(
        package='pose_getter',
        executable='pose_getter',
        name='pose_getter',
        parameters=[{
            'ee_frame': LaunchConfiguration('ee_frame'),
        }],
        output='screen',
    )

    # ── 3. Screw detector ──────────────────────────────────────────────
    screw_detector_node = Node(
        package='screw_detector',
        executable='screw_detector',
        name='screw_detector',
        parameters=[{
            'get_robot_poses': LaunchConfiguration('get_robot_poses'),
            'reject_too_few_detections': LaunchConfiguration('reject_too_few_detections'),
        }],
        output='screen',
    )

    # ── 4. Screw depth localizer ───────────────────────────────────────
    screw_depth_localizer_node = Node(
        package='screw_localizer',
        executable='screw_depth_localizer',
        name='screw_depth_localizer',
        output='screen',
    )

    # ── 5. Screw segmentor ─────────────────────────────────────────────
    screw_segmentor_node = Node(
        package='screw_detector',
        executable='screw_segmentor',
        name='screw_segmentor',
        output='screen',
    )

    # ── 6. Run localization (orchestrator / helper node) ───────────────
    run_localization_node = Node(
        package='screw_localizer',
        executable='run_localization.py',
        name='run_localization',
        output='screen',
    )

    # ── Optional: rviz2 ────────────────────────────────────────────────
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        condition=IfCondition(LaunchConfiguration('launch_rviz')),
    )

    # ── Assemble launch description (staggered start) ──────────────────
    return LaunchDescription([
        # Declare arguments
        camera_config_json_arg,
        ee_frame_arg,
        get_robot_poses_arg,
        reject_too_few_detections_arg,
        launch_rviz_arg,

        # 1 – camera starts immediately
        realsense_camera,

        # 2 – pose_getter (give camera time to initialise)
        TimerAction(period=5.0, actions=[pose_getter_node]),

        # 3 – screw_detector
        TimerAction(period=8.0, actions=[screw_detector_node]),

        # 4 – screw_depth_localizer
        TimerAction(period=10.0, actions=[screw_depth_localizer_node]),

        # 5 – screw_segmentor
        TimerAction(period=12.0, actions=[screw_segmentor_node]),

        # 6 – run_localization (needs all the above)
        TimerAction(period=14.0, actions=[run_localization_node]),

        # Optional rviz (condition-guarded)
        TimerAction(period=6.0, actions=[rviz_node]),
    ])
