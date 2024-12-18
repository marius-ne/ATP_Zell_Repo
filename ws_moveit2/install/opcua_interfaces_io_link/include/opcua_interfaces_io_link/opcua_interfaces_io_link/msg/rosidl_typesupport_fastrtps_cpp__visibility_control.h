// generated from
// rosidl_typesupport_fastrtps_cpp/resource/rosidl_typesupport_fastrtps_cpp__visibility_control.h.in
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES_IO_LINK__MSG__ROSIDL_TYPESUPPORT_FASTRTPS_CPP__VISIBILITY_CONTROL_H_
#define OPCUA_INTERFACES_IO_LINK__MSG__ROSIDL_TYPESUPPORT_FASTRTPS_CPP__VISIBILITY_CONTROL_H_

#if __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_opcua_interfaces_io_link __attribute__ ((dllexport))
    #define ROSIDL_TYPESUPPORT_FASTRTPS_CPP_IMPORT_opcua_interfaces_io_link __attribute__ ((dllimport))
  #else
    #define ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_opcua_interfaces_io_link __declspec(dllexport)
    #define ROSIDL_TYPESUPPORT_FASTRTPS_CPP_IMPORT_opcua_interfaces_io_link __declspec(dllimport)
  #endif
  #ifdef ROSIDL_TYPESUPPORT_FASTRTPS_CPP_BUILDING_DLL_opcua_interfaces_io_link
    #define ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_opcua_interfaces_io_link
  #else
    #define ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link ROSIDL_TYPESUPPORT_FASTRTPS_CPP_IMPORT_opcua_interfaces_io_link
  #endif
#else
  #define ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_opcua_interfaces_io_link __attribute__ ((visibility("default")))
  #define ROSIDL_TYPESUPPORT_FASTRTPS_CPP_IMPORT_opcua_interfaces_io_link
  #if __GNUC__ >= 4
    #define ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link
  #endif
#endif

#if __cplusplus
}
#endif

#endif  // OPCUA_INTERFACES_IO_LINK__MSG__ROSIDL_TYPESUPPORT_FASTRTPS_CPP__VISIBILITY_CONTROL_H_
