import launch
import os
import sys

from launch_ros.actions import Node
from launch.substitutions import PathJoinSubstitution, Command, FindExecutable
from launch_ros.substitutions import FindPackageShare

def get_robot_description():
    joint_limit_params = PathJoinSubstitution(
        [FindPackageShare("ur_description"), "config", "ur16e", "joint_limits.yaml"]
    )
    kinematics_params = PathJoinSubstitution(
        [FindPackageShare("ur_description"), "config", "ur16e", "default_kinematics.yaml"]
    )
    physical_params = PathJoinSubstitution(
        [FindPackageShare("ur_description"), "config", "ur16e", "physical_parameters.yaml"]
    )
    visual_params = PathJoinSubstitution(
        [FindPackageShare("ur_description"), "config", "ur16e", "visual_parameters.yaml"]
    )
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution([FindPackageShare("ur_description"), "urdf", "ur.urdf.xacro"]),
            " ",
            "robot_ip:=192.168.56.101",
            " ",
            "joint_limit_params:=",
            joint_limit_params,
            " ",
            "kinematics_params:=",
            kinematics_params,
            " ",
            "physical_params:=",
            physical_params,
            " ",
            "visual_params:=",
            visual_params,
            " ",
           "safety_limits:=",
            "true",
            " ",
            "safety_pos_margin:=",
            "0.15",
            " ",
            "safety_k_position:=",
            "20",
            " ",
            "name:=",
            "ur",
            " ",
            "ur_type:=",
            "ur16e",
            " ",
            "prefix:=",
            '""',
            " ",
        ]
    )


    robot_description = {"robot_description": robot_description_content}
    return robot_description

def get_robot_description_semantic():
    # MoveIt Configuration
    robot_description_semantic_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution([FindPackageShare("ur_moveit_config"), "srdf", "ur.srdf.xacro"]),
            " ",
            "name:=",
            # Also ur_type parameter could be used but then the planning group names in yaml
            # configs has to be updated!
            "ur",
            " ",
            "prefix:=",
            '""',
            " ",
        ]
    )
    robot_description_semantic = {
        "robot_description_semantic": robot_description_semantic_content
    }
    return robot_description_semantic
    
def generate_launch_description():
    # generate_common_hybrid_launch_description() returns a list of nodes to launch
    robot_description = get_robot_description()
    robot_description_semantic = get_robot_description_semantic()

    robot_description_kinematics = PathJoinSubstitution([FindPackageShare("ur_moveit_config"), "config", "kinematics.yaml"])

    opcua_client_node = Node(
        package="opcua_client",
        executable="client_node",
        name="opcua_client",
        output="screen",
        parameters=[
        ],
    )

    moveit_node = Node(
        package="moveit_backend",
        executable="moveit_ur",
        name="moveit_backend_ur",
        output="screen",
        parameters=[
            robot_description,
            robot_description_semantic,
            robot_description_kinematics
        ],
    )
    robo_planner_node = Node(
        package="robo_planner",
        executable="robo_planner",
        name="robo_planner",
        output="screen",
        parameters=[
        ],
    )

    #publlish TF
    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        output="both",
        parameters=[
            robot_description
        ],
    )


    return launch.LaunchDescription([opcua_client_node, moveit_node, robo_planner_node, robot_state_publisher])
