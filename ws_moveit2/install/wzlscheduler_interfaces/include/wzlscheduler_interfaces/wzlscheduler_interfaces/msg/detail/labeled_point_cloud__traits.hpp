// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledPointCloud.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__TRAITS_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "wzlscheduler_interfaces/msg/detail/labeled_point_cloud__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'poseorigin'
// Member 'posecad'
#include "geometry_msgs/msg/detail/pose__traits.hpp"
// Member 'pointcloud'
#include "sensor_msgs/msg/detail/point_cloud2__traits.hpp"

namespace wzlscheduler_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LabeledPointCloud & msg,
  std::ostream & out)
{
  out << "{";
  // member: label
  {
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << ", ";
  }

  // member: poseorigin
  {
    out << "poseorigin: ";
    to_flow_style_yaml(msg.poseorigin, out);
    out << ", ";
  }

  // member: posecad
  {
    out << "posecad: ";
    to_flow_style_yaml(msg.posecad, out);
    out << ", ";
  }

  // member: pointcloud
  {
    out << "pointcloud: ";
    to_flow_style_yaml(msg.pointcloud, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LabeledPointCloud & msg,
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

  // member: poseorigin
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "poseorigin:\n";
    to_block_style_yaml(msg.poseorigin, out, indentation + 2);
  }

  // member: posecad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "posecad:\n";
    to_block_style_yaml(msg.posecad, out, indentation + 2);
  }

  // member: pointcloud
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pointcloud:\n";
    to_block_style_yaml(msg.pointcloud, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LabeledPointCloud & msg, bool use_flow_style = false)
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
  const wzlscheduler_interfaces::msg::LabeledPointCloud & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::msg::LabeledPointCloud & msg)
{
  return wzlscheduler_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::msg::LabeledPointCloud>()
{
  return "wzlscheduler_interfaces::msg::LabeledPointCloud";
}

template<>
inline const char * name<wzlscheduler_interfaces::msg::LabeledPointCloud>()
{
  return "wzlscheduler_interfaces/msg/LabeledPointCloud";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::msg::LabeledPointCloud>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::msg::LabeledPointCloud>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<wzlscheduler_interfaces::msg::LabeledPointCloud>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__TRAITS_HPP_
