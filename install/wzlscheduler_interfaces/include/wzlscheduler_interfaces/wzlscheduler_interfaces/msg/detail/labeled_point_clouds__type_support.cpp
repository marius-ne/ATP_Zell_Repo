// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from wzlscheduler_interfaces:msg/LabeledPointClouds.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "wzlscheduler_interfaces/msg/detail/labeled_point_clouds__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace wzlscheduler_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void LabeledPointClouds_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) wzlscheduler_interfaces::msg::LabeledPointClouds(_init);
}

void LabeledPointClouds_fini_function(void * message_memory)
{
  auto typed_message = static_cast<wzlscheduler_interfaces::msg::LabeledPointClouds *>(message_memory);
  typed_message->~LabeledPointClouds();
}

size_t size_function__LabeledPointClouds__elements(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<wzlscheduler_interfaces::msg::LabeledPointCloud> *>(untyped_member);
  return member->size();
}

const void * get_const_function__LabeledPointClouds__elements(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<wzlscheduler_interfaces::msg::LabeledPointCloud> *>(untyped_member);
  return &member[index];
}

void * get_function__LabeledPointClouds__elements(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<wzlscheduler_interfaces::msg::LabeledPointCloud> *>(untyped_member);
  return &member[index];
}

void fetch_function__LabeledPointClouds__elements(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const wzlscheduler_interfaces::msg::LabeledPointCloud *>(
    get_const_function__LabeledPointClouds__elements(untyped_member, index));
  auto & value = *reinterpret_cast<wzlscheduler_interfaces::msg::LabeledPointCloud *>(untyped_value);
  value = item;
}

void assign_function__LabeledPointClouds__elements(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<wzlscheduler_interfaces::msg::LabeledPointCloud *>(
    get_function__LabeledPointClouds__elements(untyped_member, index));
  const auto & value = *reinterpret_cast<const wzlscheduler_interfaces::msg::LabeledPointCloud *>(untyped_value);
  item = value;
}

void resize_function__LabeledPointClouds__elements(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<wzlscheduler_interfaces::msg::LabeledPointCloud> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember LabeledPointClouds_message_member_array[1] = {
  {
    "elements",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<wzlscheduler_interfaces::msg::LabeledPointCloud>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wzlscheduler_interfaces::msg::LabeledPointClouds, elements),  // bytes offset in struct
    nullptr,  // default value
    size_function__LabeledPointClouds__elements,  // size() function pointer
    get_const_function__LabeledPointClouds__elements,  // get_const(index) function pointer
    get_function__LabeledPointClouds__elements,  // get(index) function pointer
    fetch_function__LabeledPointClouds__elements,  // fetch(index, &value) function pointer
    assign_function__LabeledPointClouds__elements,  // assign(index, value) function pointer
    resize_function__LabeledPointClouds__elements  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers LabeledPointClouds_message_members = {
  "wzlscheduler_interfaces::msg",  // message namespace
  "LabeledPointClouds",  // message name
  1,  // number of fields
  sizeof(wzlscheduler_interfaces::msg::LabeledPointClouds),
  LabeledPointClouds_message_member_array,  // message members
  LabeledPointClouds_init_function,  // function to initialize message memory (memory has to be allocated)
  LabeledPointClouds_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t LabeledPointClouds_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &LabeledPointClouds_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace wzlscheduler_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<wzlscheduler_interfaces::msg::LabeledPointClouds>()
{
  return &::wzlscheduler_interfaces::msg::rosidl_typesupport_introspection_cpp::LabeledPointClouds_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, wzlscheduler_interfaces, msg, LabeledPointClouds)() {
  return &::wzlscheduler_interfaces::msg::rosidl_typesupport_introspection_cpp::LabeledPointClouds_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
