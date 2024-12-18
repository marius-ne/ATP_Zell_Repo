// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledPointClouds.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUDS__TRAITS_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUDS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "wzlscheduler_interfaces/msg/detail/labeled_point_clouds__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'elements'
#include "wzlscheduler_interfaces/msg/detail/labeled_point_cloud__traits.hpp"

namespace wzlscheduler_interfaces
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

}  // namespace wzlscheduler_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use wzlscheduler_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const wzlscheduler_interfaces::msg::LabeledPointClouds & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::msg::LabeledPointClouds & msg)
{
  return wzlscheduler_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::msg::LabeledPointClouds>()
{
  return "wzlscheduler_interfaces::msg::LabeledPointClouds";
}

template<>
inline const char * name<wzlscheduler_interfaces::msg::LabeledPointClouds>()
{
  return "wzlscheduler_interfaces/msg/LabeledPointClouds";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::msg::LabeledPointClouds>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::msg::LabeledPointClouds>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<wzlscheduler_interfaces::msg::LabeledPointClouds>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUDS__TRAITS_HPP_
