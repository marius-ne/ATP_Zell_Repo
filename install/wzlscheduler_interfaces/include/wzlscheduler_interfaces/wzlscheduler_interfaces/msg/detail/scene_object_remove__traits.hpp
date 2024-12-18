// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from wzlscheduler_interfaces:msg/SceneObjectRemove.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_REMOVE__TRAITS_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_REMOVE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "wzlscheduler_interfaces/msg/detail/scene_object_remove__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace wzlscheduler_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SceneObjectRemove & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SceneObjectRemove & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SceneObjectRemove & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace wzlscheduler_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use wzlscheduler_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const wzlscheduler_interfaces::msg::SceneObjectRemove & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::msg::SceneObjectRemove & msg)
{
  return wzlscheduler_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::msg::SceneObjectRemove>()
{
  return "wzlscheduler_interfaces::msg::SceneObjectRemove";
}

template<>
inline const char * name<wzlscheduler_interfaces::msg::SceneObjectRemove>()
{
  return "wzlscheduler_interfaces/msg/SceneObjectRemove";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::msg::SceneObjectRemove>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::msg::SceneObjectRemove>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<wzlscheduler_interfaces::msg::SceneObjectRemove>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_REMOVE__TRAITS_HPP_
