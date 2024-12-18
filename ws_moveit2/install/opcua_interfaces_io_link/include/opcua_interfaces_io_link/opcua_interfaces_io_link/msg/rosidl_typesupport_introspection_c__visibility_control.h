// generated from
// rosidl_typesupport_introspection_c/resource/rosidl_typesupport_introspection_c__visibility_control.h.in
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES_IO_LINK__MSG__ROSIDL_TYPESUPPORT_INTROSPECTION_C__VISIBILITY_CONTROL_H_
#define OPCUA_INTERFACES_IO_LINK__MSG__ROSIDL_TYPESUPPORT_INTROSPECTION_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_opcua_interfaces_io_link __attribute__ ((dllexport))
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_IMPORT_opcua_interfaces_io_link __attribute__ ((dllimport))
  #else
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_opcua_interfaces_io_link __declspec(dllexport)
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_IMPORT_opcua_interfaces_io_link __declspec(dllimport)
  #endif
  #ifdef ROSIDL_TYPESUPPORT_INTROSPECTION_C_BUILDING_DLL_opcua_interfaces_io_link
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_PUBLIC_opcua_interfaces_io_link ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_opcua_interfaces_io_link
  #else
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_PUBLIC_opcua_interfaces_io_link ROSIDL_TYPESUPPORT_INTROSPECTION_C_IMPORT_opcua_interfaces_io_link
  #endif
#else
  #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_opcua_interfaces_io_link __attribute__ ((visibility("default")))
  #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_IMPORT_opcua_interfaces_io_link
  #if __GNUC__ >= 4
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_PUBLIC_opcua_interfaces_io_link __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_PUBLIC_opcua_interfaces_io_link
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // OPCUA_INTERFACES_IO_LINK__MSG__ROSIDL_TYPESUPPORT_INTROSPECTION_C__VISIBILITY_CONTROL_H_
