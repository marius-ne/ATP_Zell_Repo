# Run Demo
source /opt/ros/humble/setup.bash
source ws/restackcell/ws_moveit2/install/setup.bash
1. Start Robot Controller

2. In a new terminal run 

ros2 launch ur_robot_driver ur_control.launch.py ur_type:=ur16e robot_ip:=192.168.20.20 launch_rviz:=false description_package:=ur_description

3. start the program "Remote Ros" on the UR16e
Click Run

4. In a new terminal run to start moveit
ros2 launch robo_planner ur_planner_pilz.launch.py


5. In a new terminal run to start the roboplanner
ros2 launch robo_planner ur_planner_launch.py


(6.) Start the Websocket
ros2 launch rosbridge_server rosbridge_websocket_launch.xml


Colcon build when there are changes in Code:
cd ws/restackcell/ws_moveit2/
colcon build