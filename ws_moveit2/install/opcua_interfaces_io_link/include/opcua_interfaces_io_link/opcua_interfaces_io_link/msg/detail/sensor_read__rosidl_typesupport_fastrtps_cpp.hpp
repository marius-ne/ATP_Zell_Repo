// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from opcua_interfaces_io_link:msg/SensorRead.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "opcua_interfaces_io_link/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "opcua_interfaces_io_link/msg/detail/sensor_read__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace opcua_interfaces_io_link
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link
cdr_serialize(
  const opcua_interfaces_io_link::msg::SensorRead & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  opcua_interfaces_io_link::msg::SensorRead & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link
get_serialized_size(
  const opcua_interfaces_io_link::msg::SensorRead & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link
max_serialized_size_SensorRead(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace opcua_interfaces_io_link

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, opcua_interfaces_io_link, msg, SensorRead)();

#ifdef __cplusplus
}
#endif

#endif  // OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
