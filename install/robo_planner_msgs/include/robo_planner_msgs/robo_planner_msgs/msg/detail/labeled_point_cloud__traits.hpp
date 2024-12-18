// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robo_planner_msgs:msg/LabeledPointCloud.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUD__TRAITS_HPP_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUD__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robo_planner_msgs/msg/detail/labeled_point_cloud__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'poseorigin'
// Member 'posecad'
#include "geometry_msgs/msg/detail/pose__traits.hpp"
// Member 'pointcloud'
#include "sensor_msgs/msg/detail/point_cloud2__traits.hpp"

namespace robo_planner_msgs
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

}  // namespace robo_planner_msgs

namespace rosidl_generator_traits
{

[[deprecated("use robo_planner_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robo_planner_msgs::msg::LabeledPointCloud & msg,
  std::ostream & out, size_t indentation = 0)
{
  robo_planner_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robo_planner_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const robo_planner_msgs::msg::LabeledPointCloud & msg)
{
  return robo_planner_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robo_planner_msgs::msg::LabeledPointCloud>()
{
  return "robo_planner_msgs::msg::LabeledPointCloud";
}

template<>
inline const char * name<robo_planner_msgs::msg::LabeledPointCloud>()
{
  return "robo_planner_msgs/msg/LabeledPointCloud";
}

template<>
struct has_fixed_size<robo_planner_msgs::msg::LabeledPointCloud>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robo_planner_msgs::msg::LabeledPointCloud>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robo_planner_msgs::msg::LabeledPointCloud>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUD__TRAITS_HPP_
