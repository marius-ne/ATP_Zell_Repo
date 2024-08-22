#----------------------------------------------------------------
# Generated CMake target import file for configuration "None".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "moveit_ros_planning_interface::moveit_common_planning_interface_objects" for configuration "None"
set_property(TARGET moveit_ros_planning_interface::moveit_common_planning_interface_objects APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(moveit_ros_planning_interface::moveit_common_planning_interface_objects PROPERTIES
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/libmoveit_common_planning_interface_objects.so.2.5.5"
  IMPORTED_SONAME_NONE "libmoveit_common_planning_interface_objects.so.2.5.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS moveit_ros_planning_interface::moveit_common_planning_interface_objects )
list(APPEND _IMPORT_CHECK_FILES_FOR_moveit_ros_planning_interface::moveit_common_planning_interface_objects "${_IMPORT_PREFIX}/lib/libmoveit_common_planning_interface_objects.so.2.5.5" )

# Import target "moveit_ros_planning_interface::moveit_planning_scene_interface" for configuration "None"
set_property(TARGET moveit_ros_planning_interface::moveit_planning_scene_interface APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(moveit_ros_planning_interface::moveit_planning_scene_interface PROPERTIES
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/libmoveit_planning_scene_interface.so.2.5.5"
  IMPORTED_SONAME_NONE "libmoveit_planning_scene_interface.so.2.5.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS moveit_ros_planning_interface::moveit_planning_scene_interface )
list(APPEND _IMPORT_CHECK_FILES_FOR_moveit_ros_planning_interface::moveit_planning_scene_interface "${_IMPORT_PREFIX}/lib/libmoveit_planning_scene_interface.so.2.5.5" )

# Import target "moveit_ros_planning_interface::moveit_move_group_interface" for configuration "None"
set_property(TARGET moveit_ros_planning_interface::moveit_move_group_interface APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(moveit_ros_planning_interface::moveit_move_group_interface PROPERTIES
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/libmoveit_move_group_interface.so.2.5.5"
  IMPORTED_SONAME_NONE "libmoveit_move_group_interface.so.2.5.5"
  )

list(APPEND _IMPORT_CHECK_TARGETS moveit_ros_planning_interface::moveit_move_group_interface )
list(APPEND _IMPORT_CHECK_FILES_FOR_moveit_ros_planning_interface::moveit_move_group_interface "${_IMPORT_PREFIX}/lib/libmoveit_move_group_interface.so.2.5.5" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
