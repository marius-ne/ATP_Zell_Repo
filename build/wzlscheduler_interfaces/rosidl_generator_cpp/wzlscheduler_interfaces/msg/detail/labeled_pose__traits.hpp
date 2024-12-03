// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledPose.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSE__TRAITS_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "wzlscheduler_interfaces/msg/detail/labeled_pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace wzlscheduler_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LabeledPose & msg,
  std::ostream & out)
{
  out << "{";
  // member: label
  {
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
    out << ", ";
  }

  // member: drillholeindexx
  {
    out << "drillholeindexx: ";
    rosidl_generator_traits::value_to_yaml(msg.drillholeindexx, out);
    out << ", ";
  }

  // member: drillholeindexy
  {
    out << "drillholeindexy: ";
    rosidl_generator_traits::value_to_yaml(msg.drillholeindexy, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LabeledPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: label
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << "\n";
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }

  // member: drillholeindexx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drillholeindexx: ";
    rosidl_generator_traits::value_to_yaml(msg.drillholeindexx, out);
    out << "\n";
  }

  // member: drillholeindexy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drillholeindexy: ";
    rosidl_generator_traits::value_to_yaml(msg.drillholeindexy, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LabeledPose & msg, bool use_flow_style = false)
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
  const wzlscheduler_interfaces::msg::LabeledPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::msg::LabeledPose & msg)
{
  return wzlscheduler_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::msg::LabeledPose>()
{
  return "wzlscheduler_interfaces::msg::LabeledPose";
}

template<>
inline const char * name<wzlscheduler_interfaces::msg::LabeledPose>()
{
  return "wzlscheduler_interfaces/msg/LabeledPose";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::msg::LabeledPose>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::msg::LabeledPose>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<wzlscheduler_interfaces::msg::LabeledPose>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSE__TRAITS_HPP_
