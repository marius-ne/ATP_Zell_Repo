// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robo_planner_msgs:msg/SceneObjectRemove.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_REMOVE__BUILDER_HPP_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_REMOVE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robo_planner_msgs/msg/detail/scene_object_remove__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robo_planner_msgs
{

namespace msg
{

namespace builder
{

class Init_SceneObjectRemove_name
{
public:
  Init_SceneObjectRemove_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robo_planner_msgs::msg::SceneObjectRemove name(::robo_planner_msgs::msg::SceneObjectRemove::_name_type arg)
  {
    msg_.name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robo_planner_msgs::msg::SceneObjectRemove msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robo_planner_msgs::msg::SceneObjectRemove>()
{
  return robo_planner_msgs::msg::builder::Init_SceneObjectRemove_name();
}

}  // namespace robo_planner_msgs

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_REMOVE__BUILDER_HPP_
