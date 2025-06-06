cmake_minimum_required(VERSION 3.8)
project(robo_planner)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(geometric_shapes REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(wzlscheduler_interfaces REQUIRED)
find_package(opcua_interfaces REQUIRED)
find_package(modbus_interfaces REQUIRED)

add_executable(robo_planner 
  src/Gripper.cpp
  src/IoInterface.cpp
  src/Main_Remancell.cpp
  src/Part.cpp
  src/ObjectContainer.cpp
  src/Pose.cpp
  src/Robot.cpp
  src/Scene.cpp
  src/SceneObjects/SceneObjectClampingDevice.cpp
  src/Tasks/Task.cpp
  src/Tasks/TaskGripperChange.cpp
  src/Tasks/TaskGripperChangePick.cpp
  src/Tasks/TaskGripperChangePlace.cpp
  src/Tasks/TaskGripperClose.cpp
  src/Tasks/TaskGripperOpen.cpp
  src/Tasks/TaskFollowTrajectory.cpp
  src/Tasks/TaskList.cpp
  src/Tasks/TaskMoveToPose.cpp
  src/Tasks/TaskPick.cpp
  src/Tasks/TaskPickAndPlace.cpp
  src/Tasks/TaskPlace.cpp
  src/Tasks/TaskScanScene.cpp
  )

target_include_directories(robo_planner PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_compile_features(robo_planner PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  robo_planner
  "rclcpp"
  "geometric_shapes"
  "geometry_msgs"
  "tf2"
  "tf2_ros"
  "tf2_eigen"
  wzlscheduler_interfaces
  opcua_interfaces
  modbus_interfaces
)

install(TARGETS robo_planner
  DESTINATION lib/${PROJECT_NAME})

install(
  DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
