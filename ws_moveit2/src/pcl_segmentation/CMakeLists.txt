cmake_minimum_required(VERSION 3.8)
project(pcl_segmentation)


# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED COMPONENTS common io)
find_package(wzlscheduler_interfaces REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)

find_package(PCL 1.1 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

# Add executable
add_executable(file_publisher
  src/FilePublisher.cpp
)

add_executable(downsampling 
  src/Downsampling.cpp
)

add_executable(clustering
  src/Clustering.cpp
)

add_executable(plane_filter
  src/PlaneRemover.cpp
)

add_executable(classification
  src/Classification.cpp
)

add_executable(matching
  src/Matching.cpp
)

add_executable(pose_snapper
  src/PoseSnapper.cpp
)

add_executable(transformation_robot
  src/TransformationRobot.cpp
)

add_executable(hand_eye_transform_publisher
  src/HandEyeTransformPublisher.cpp
)

add_executable(test_robot_pose_publisher
  src/Test/TestPoseHandPublisher.cpp
)

ament_target_dependencies(file_publisher
  rclcpp 
  sensor_msgs
  pcl_conversions
)

ament_target_dependencies(downsampling
  rclcpp 
  sensor_msgs
  pcl_conversions
)

ament_target_dependencies(clustering
  rclcpp 
  sensor_msgs
  pcl_conversions
  wzlscheduler_interfaces
)

ament_target_dependencies(plane_filter
  rclcpp 
  sensor_msgs
  pcl_conversions
)

ament_target_dependencies(classification
  rclcpp 
  sensor_msgs
  pcl_conversions
  wzlscheduler_interfaces
)

ament_target_dependencies(matching
  rclcpp 
  sensor_msgs
  pcl_conversions
  wzlscheduler_interfaces
)

ament_target_dependencies(pose_snapper
  rclcpp 
  sensor_msgs
  pcl_conversions
  wzlscheduler_interfaces
)

ament_target_dependencies(transformation_robot
  rclcpp 
  sensor_msgs
  pcl_conversions
  wzlscheduler_interfaces
  geometry_msgs
  tf2
  tf2_ros
)

ament_target_dependencies(hand_eye_transform_publisher
  rclcpp 
  geometry_msgs
  tf2
  tf2_ros
)

ament_target_dependencies(test_robot_pose_publisher
  rclcpp 
  geometry_msgs
  tf2
  tf2_ros
)


target_link_libraries(file_publisher ${PCL_LIBRARIES})
target_link_libraries(downsampling ${PCL_LIBRARIES})
target_link_libraries(clustering ${PCL_LIBRARIES})
target_link_libraries(plane_filter ${PCL_LIBRARIES})
target_link_libraries(classification ${PCL_LIBRARIES})
target_link_libraries(matching ${PCL_LIBRARIES})
target_link_libraries(pose_snapper ${PCL_LIBRARIES})
target_link_libraries(transformation_robot ${PCL_LIBRARIES})
target_link_libraries(test_robot_pose_publisher ${PCL_LIBRARIES})

# Install Cpp executables
install(TARGETS
  file_publisher
  downsampling
  clustering
  plane_filter
  classification
  matching
  pose_snapper
  transformation_robot
  hand_eye_transform_publisher
  test_robot_pose_publisher
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()