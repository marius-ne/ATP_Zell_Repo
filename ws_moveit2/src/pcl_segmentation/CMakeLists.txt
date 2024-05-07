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



target_link_libraries(file_publisher ${PCL_LIBRARIES})
target_link_libraries(downsampling ${PCL_LIBRARIES})
target_link_libraries(clustering ${PCL_LIBRARIES})
target_link_libraries(plane_filter ${PCL_LIBRARIES})
target_link_libraries(classification ${PCL_LIBRARIES})
target_link_libraries(matching ${PCL_LIBRARIES})

# Install Cpp executables
install(TARGETS
  file_publisher
  downsampling
  clustering
  plane_filter
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()