// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledPoses.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__TRAITS_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "wzlscheduler_interfaces/msg/detail/labeled_poses__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'elements'
#include "wzlscheduler_interfaces/msg/detail/labeled_pose__traits.hpp"

namespace wzlscheduler_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LabeledPoses & msg,
  std::ostream & out)
{
  out << "{";
  // member: elements
  {
    out << "elements: ";
    to_flow_style_yaml(msg.elements, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LabeledPoses & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: elements
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "elements:\n";
    to_block_style_yaml(msg.elements, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LabeledPoses & msg, bool use_flow_style = false)
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
  const wzlscheduler_interfaces::msg::LabeledPoses & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::msg::LabeledPoses & msg)
{
  return wzlscheduler_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::msg::LabeledPoses>()
{
  return "wzlscheduler_interfaces::msg::LabeledPoses";
}

template<>
inline const char * name<wzlscheduler_interfaces::msg::LabeledPoses>()
{
  return "wzlscheduler_interfaces/msg/LabeledPoses";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::msg::LabeledPoses>
  : std::integral_constant<bool, has_fixed_size<wzlscheduler_interfaces::msg::LabeledPose>::value> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::msg::LabeledPoses>
  : std::integral_constant<bool, has_bounded_size<wzlscheduler_interfaces::msg::LabeledPose>::value> {};

template<>
struct is_message<wzlscheduler_interfaces::msg::LabeledPoses>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__TRAITS_HPP_
