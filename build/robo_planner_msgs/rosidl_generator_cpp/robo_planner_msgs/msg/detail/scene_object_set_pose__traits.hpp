// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robo_planner_msgs:msg/SceneObjectSetPose.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_SET_POSE__TRAITS_HPP_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_SET_POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robo_planner_msgs/msg/detail/scene_object_set_pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'coordinates'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace robo_planner_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const SceneObjectSetPose & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: coordinates
  {
    out << "coordinates: ";
    to_flow_style_yaml(msg.coordinates, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SceneObjectSetPose & msg,
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

  // member: coordinates
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "coordinates:\n";
    to_block_style_yaml(msg.coordinates, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SceneObjectSetPose & msg, bool use_flow_style = false)
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
  const robo_planner_msgs::msg::SceneObjectSetPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  robo_planner_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robo_planner_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const robo_planner_msgs::msg::SceneObjectSetPose & msg)
{
  return robo_planner_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robo_planner_msgs::msg::SceneObjectSetPose>()
{
  return "robo_planner_msgs::msg::SceneObjectSetPose";
}

template<>
inline const char * name<robo_planner_msgs::msg::SceneObjectSetPose>()
{
  return "robo_planner_msgs/msg/SceneObjectSetPose";
}

template<>
struct has_fixed_size<robo_planner_msgs::msg::SceneObjectSetPose>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robo_planner_msgs::msg::SceneObjectSetPose>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robo_planner_msgs::msg::SceneObjectSetPose>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_SET_POSE__TRAITS_HPP_
