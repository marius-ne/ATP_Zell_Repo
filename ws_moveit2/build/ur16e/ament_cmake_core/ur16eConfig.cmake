# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_ur16e_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED ur16e_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(ur16e_FOUND FALSE)
  elseif(NOT ur16e_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(ur16e_FOUND FALSE)
  endif()
  return()
endif()
set(_ur16e_CONFIG_INCLUDED TRUE)

# output package information
if(NOT ur16e_FIND_QUIETLY)
  message(STATUS "Found ur16e: 0.0.0 (${ur16e_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'ur16e' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${ur16e_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(ur16e_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${ur16e_DIR}/${_extra}")
endforeach()
