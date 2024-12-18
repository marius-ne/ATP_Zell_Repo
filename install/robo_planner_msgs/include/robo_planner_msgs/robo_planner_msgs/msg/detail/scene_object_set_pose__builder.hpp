// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robo_planner_msgs:msg/SceneObjectSetPose.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_SET_POSE__BUILDER_HPP_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_SET_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robo_planner_msgs/msg/detail/scene_object_set_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robo_planner_msgs
{

namespace msg
{

namespace builder
{

class Init_SceneObjectSetPose_coordinates
{
public:
  explicit Init_SceneObjectSetPose_coordinates(::robo_planner_msgs::msg::SceneObjectSetPose & msg)
  : msg_(msg)
  {}
  ::robo_planner_msgs::msg::SceneObjectSetPose coordinates(::robo_planner_msgs::msg::SceneObjectSetPose::_coordinates_type arg)
  {
    msg_.coordinates = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robo_planner_msgs::msg::SceneObjectSetPose msg_;
};

class Init_SceneObjectSetPose_name
{
public:
  Init_SceneObjectSetPose_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SceneObjectSetPose_coordinates name(::robo_planner_msgs::msg::SceneObjectSetPose::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_SceneObjectSetPose_coordinates(msg_);
  }

private:
  ::robo_planner_msgs::msg::SceneObjectSetPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robo_planner_msgs::msg::SceneObjectSetPose>()
{
  return robo_planner_msgs::msg::builder::Init_SceneObjectSetPose_name();
}

}  // namespace robo_planner_msgs

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_SET_POSE__BUILDER_HPP_
