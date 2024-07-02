// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robo_planner_msgs:msg/LabeledPointClouds.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__TRAITS_HPP_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robo_planner_msgs/msg/detail/labeled_point_clouds__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'elements'
#include "robo_planner_msgs/msg/detail/labeled_point_cloud__traits.hpp"

namespace robo_planner_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const LabeledPointClouds & msg,
  std::ostream & out)
{
  out << "{";
  // member: elements
  {
    if (msg.elements.size() == 0) {
      out << "elements: []";
    } else {
      out << "elements: [";
      size_t pending_items = msg.elements.size();
      for (auto item : msg.elements) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LabeledPointClouds & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: elements
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.elements.size() == 0) {
      out << "elements: []\n";
    } else {
      out << "elements:\n";
      for (auto item : msg.elements) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LabeledPointClouds & msg, bool use_flow_style = false)
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

}  // namespace robo_planner_msgs

namespace rosidl_generator_traits
{

[[deprecated("use robo_planner_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robo_planner_msgs::msg::LabeledPointClouds & msg,
  std::ostream & out, size_t indentation = 0)
{
  robo_planner_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robo_planner_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const robo_planner_msgs::msg::LabeledPointClouds & msg)
{
  return robo_planner_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robo_planner_msgs::msg::LabeledPointClouds>()
{
  return "robo_planner_msgs::msg::LabeledPointClouds";
}

template<>
inline const char * name<robo_planner_msgs::msg::LabeledPointClouds>()
{
  return "robo_planner_msgs/msg/LabeledPointClouds";
}

template<>
struct has_fixed_size<robo_planner_msgs::msg::LabeledPointClouds>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robo_planner_msgs::msg::LabeledPointClouds>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robo_planner_msgs::msg::LabeledPointClouds>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__TRAITS_HPP_
