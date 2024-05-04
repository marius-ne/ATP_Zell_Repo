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
find_package(sensor_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED COMPONENTS common io)

find_package(PCL 1.1 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

# Add executable
add_executable(robo_planner_segmentation 
  src/Segmentation.cpp
  src/Clustering.cpp
  )
add_executable(robo_planner_pointcloud_subscriber src/PointcloudSubscriber.cpp)
#add_executable(rs_pcl_filter src/filter/rspcl_filter_node.cpp src/filter/rspcl_filter_component.cpp)
#add_executable(rs_pcl_clustering src/clustering/rspcl_clustering_node.cpp src/clustering/rspcl_clustering_component.cpp)
#add_executable(rs_pcl_marker src/visualization_marker/rspcl_marker.cpp)

ament_target_dependencies(robo_planner_segmentation
  rclcpp 
  sensor_msgs
  pcl_conversions
)

ament_target_dependencies(robo_planner_pointcloud_subscriber
  rclcpp 
  sensor_msgs
  pcl_conversions
)

#ament_target_dependencies(rs_pcl_filter
#  rclcpp 
#  sensor_msgs
#  pcl_conversions
#)

#ament_target_dependencies(rs_pcl_clustering
#  rclcpp 
#  sensor_msgs
#  pcl_conversions
#)

#ament_target_dependencies(rs_pcl_marker
#  rclcpp 
#  sensor_msgs
#  geometry_msgs
#  visualization_msgs
#  pcl_conversions
#)

target_link_libraries(robo_planner_segmentation ${PCL_LIBRARIES})
target_link_libraries(robo_planner_pointcloud_subscriber ${PCL_LIBRARIES})
#target_link_libraries(rs_pcl_marker ${PCL_LIBRARIES})

# Install Cpp executables
install(TARGETS
  robo_planner_segmentation
  robo_planner_pointcloud_subscriber
  #rs_pcl_marker
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()