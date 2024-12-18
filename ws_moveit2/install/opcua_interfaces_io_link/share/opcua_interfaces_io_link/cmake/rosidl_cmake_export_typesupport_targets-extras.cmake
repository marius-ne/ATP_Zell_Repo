# generated from
# rosidl_cmake/cmake/template/rosidl_cmake_export_typesupport_targets.cmake.in

set(_exported_typesupport_targets
  "__rosidl_generator_c:opcua_interfaces_io_link__rosidl_generator_c;__rosidl_typesupport_fastrtps_c:opcua_interfaces_io_link__rosidl_typesupport_fastrtps_c;__rosidl_typesupport_introspection_c:opcua_interfaces_io_link__rosidl_typesupport_introspection_c;__rosidl_typesupport_c:opcua_interfaces_io_link__rosidl_typesupport_c;__rosidl_generator_cpp:opcua_interfaces_io_link__rosidl_generator_cpp;__rosidl_typesupport_fastrtps_cpp:opcua_interfaces_io_link__rosidl_typesupport_fastrtps_cpp;__rosidl_typesupport_introspection_cpp:opcua_interfaces_io_link__rosidl_typesupport_introspection_cpp;__rosidl_typesupport_cpp:opcua_interfaces_io_link__rosidl_typesupport_cpp;__rosidl_generator_py:opcua_interfaces_io_link__rosidl_generator_py")

# populate opcua_interfaces_io_link_TARGETS_<suffix>
if(NOT _exported_typesupport_targets STREQUAL "")
  # loop over typesupport targets
  foreach(_tuple ${_exported_typesupport_targets})
    string(REPLACE ":" ";" _tuple "${_tuple}")
    list(GET _tuple 0 _suffix)
    list(GET _tuple 1 _target)

    set(_target "opcua_interfaces_io_link::${_target}")
    if(NOT TARGET "${_target}")
      # the exported target must exist
      message(WARNING "Package 'opcua_interfaces_io_link' exports the typesupport target '${_target}' which doesn't exist")
    else()
      list(APPEND opcua_interfaces_io_link_TARGETS${_suffix} "${_target}")
    endif()
  endforeach()
endif()
