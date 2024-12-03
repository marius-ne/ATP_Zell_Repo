// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledBoundingBox.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOX__TRAITS_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOX__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "wzlscheduler_interfaces/msg/detail/labeled_bounding_box__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace wzlscheduler_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LabeledBoundingBox & msg,
  std::ostream & out)
{
  out << "{";
  // member: label
  {
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: width
  {
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << ", ";
  }

  // member: height
  {
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LabeledBoundingBox & msg,
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

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << "\n";
  }

  // member: height
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "height: ";
    rosidl_generator_traits::value_to_yaml(msg.height, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LabeledBoundingBox & msg, bool use_flow_style = false)
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
  const wzlscheduler_interfaces::msg::LabeledBoundingBox & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::msg::LabeledBoundingBox & msg)
{
  return wzlscheduler_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::msg::LabeledBoundingBox>()
{
  return "wzlscheduler_interfaces::msg::LabeledBoundingBox";
}

template<>
inline const char * name<wzlscheduler_interfaces::msg::LabeledBoundingBox>()
{
  return "wzlscheduler_interfaces/msg/LabeledBoundingBox";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::msg::LabeledBoundingBox>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::msg::LabeledBoundingBox>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<wzlscheduler_interfaces::msg::LabeledBoundingBox>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOX__TRAITS_HPP_
