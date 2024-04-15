// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from ur16e_interfaces:msg/LoadObject.idl
// generated code does not contain a copyright notice

#ifndef UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "ur16e_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "ur16e_interfaces/msg/detail/load_object__struct.hpp"

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

namespace ur16e_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ur16e_interfaces
cdr_serialize(
  const ur16e_interfaces::msg::LoadObject & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ur16e_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  ur16e_interfaces::msg::LoadObject & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ur16e_interfaces
get_serialized_size(
  const ur16e_interfaces::msg::LoadObject & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ur16e_interfaces
max_serialized_size_LoadObject(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace ur16e_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ur16e_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, ur16e_interfaces, msg, LoadObject)();

#ifdef __cplusplus
}
#endif

#endif  // UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
