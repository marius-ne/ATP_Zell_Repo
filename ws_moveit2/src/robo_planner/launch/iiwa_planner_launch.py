from ament_index_python import get_package_share_directory
import launch
import os
import sys

from launch_ros.actions import Node
from launch.substitutions import PathJoinSubstitution, Command, FindExecutable
from launch_ros.substitutions import FindPackageShare

from launch.actions import IncludeLaunchDescription, RegisterEventHandler
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.parameter_descriptions import ParameterValue

def get_robot_description():
    joint_limit_params = PathJoinSubstitution(
        [FindPackageShare("iiwa_description"), "moveit2", "iiwa_joint_limits.yaml"]
    )
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name='xacro')]),
            ' ',
            PathJoinSubstitution(
                [FindPackageShare('iiwa_description'), 'config', 'iiwa.config.xacro']
            ),
            ' ',
            'prefix:=',
            '""',
            ' ',
            'base_frame_file:=',
            'base_frame_custom.yaml',
            ' ',
            'description_package:=',
            'iiwa_description',
            ' ',
            'namespace:=',
            '/',
        ]
    )


    robot_description = {"robot_description": ParameterValue(robot_description_content, value_type=str)}
    return robot_description

def get_robot_description_semantic():
    # MoveIt Configuration
    robot_description_semantic_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution(
                [FindPackageShare('iiwa_description',), "srdf", "iiwa.srdf.xacro"]
            ),
            " ",
            "name:=",
            "iiwa",
            " ",
            "prefix:=",
            '""',
            " ",
            'description_package:=',
            'iiwa_description',
        ]
    )
    robot_description_semantic = {
        "robot_description_semantic": ParameterValue(robot_description_semantic_content, value_type=str)
    }
    return robot_description_semantic

def generate_launch_description():
    # generate_common_hybrid_launch_description() returns a list of nodes to launch
    robot_description = get_robot_description()
    robot_description_semantic = get_robot_description_semantic()
    #robot_description_kinematics = PathJoinSubstitution([FindPackageShare("robo_planner"), "config","custom_moveit_config","config","kinematics.yaml"])
    cell_config = os.path.join(
            get_package_share_directory('robo_planner'),
            'config',
            'cell_config.yaml'
        )
    
    opcua_client_node = Node(
        package="opcua_client",
        executable="client_node",
        name="opcua_client",
        output="screen",
        parameters=[
        ],
    )

    modbus_client_node = Node(
        package="modbus_client",
        executable="modbus_client_node",
        name="modbus_client",
        output="screen",
        parameters=[
        ],
    )

    opcua_client_io_link_node = Node(
        package="opcua_client_io_link",
        executable="client_node_io_link",
        name="opcua_client_io_link",
        output="screen",
        parameters=[{
            "connection_retry_delay": 5.0,
            "reconnect_attempts": 5,
            "timeout": 10.0
        }],
        respawn=True,
        respawn_delay=1.0
    )

    # TODO Add rosbridge websocket server
    

    moveit_backend = Node(
        package="moveit_backend",
        executable="moveit_iiwa",
        name="moveit_backend_iiwa",
        output="screen",
        parameters=[
            robot_description,
            robot_description_semantic,
            #robot_description_kinematics
        ],
    )
    robo_planner_node = Node(
        package="robo_planner",
        executable="robo_planner",
        name="robo_planner",
        output="screen",
        parameters=[cell_config
        ],
    )

    #publish TF
    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        output="both",
        parameters=[
            robot_description
        ],
    )


    #return launch.LaunchDescription([opcua_client_node, opcua_client_io_link_node, modbus_client_node, moveit_backend, robo_planner_node, robot_state_publisher])
    #return launch.LaunchDescription([modbus_client_node, moveit_backend, robo_planner_node, robot_state_publisher])
    return launch.LaunchDescription([opcua_client_node, moveit_backend, robo_planner_node, robot_state_publisher])
