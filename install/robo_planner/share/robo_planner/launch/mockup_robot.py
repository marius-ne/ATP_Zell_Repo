from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="mockup_robot",
            executable="mockup_robot",
            name="mockup_robot",
            parameters=[{
            }]
        ),     
        Node(
            package="robo_planner",
            executable="robo_planner",
            name="robo_planner",
            parameters=[{
            }]
        ),        
    ])