# generated from ament_cmake_export_include_directories/cmake/ament_cmake_export_include_directories-extras.cmake.in

set(_exported_include_dirs "${lucid_vision_driver_DIR}/../../../include;/home/alex/Downloads/ArenaSDK_v0.1.84_Linux_x64/ArenaSDK_Linux_x64/GenICam/library/CPP/include;/home/alex/Downloads/ArenaSDK_v0.1.84_Linux_x64/ArenaSDK_Linux_x64/include/")

# append include directories to lucid_vision_driver_INCLUDE_DIRS
# warn about not existing paths
if(NOT _exported_include_dirs STREQUAL "")
  find_package(ament_cmake_core QUIET REQUIRED)
  foreach(_exported_include_dir ${_exported_include_dirs})
    if(NOT IS_DIRECTORY "${_exported_include_dir}")
      message(WARNING "Package 'lucid_vision_driver' exports the include directory '${_exported_include_dir}' which doesn't exist")
    endif()
    normalize_path(_exported_include_dir "${_exported_include_dir}")
    list(APPEND lucid_vision_driver_INCLUDE_DIRS "${_exported_include_dir}")
  endforeach()
endif()
