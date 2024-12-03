// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robo_planner_msgs:msg/SceneObjectAdd.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_ADD__BUILDER_HPP_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_ADD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robo_planner_msgs/msg/detail/scene_object_add__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robo_planner_msgs
{

namespace msg
{

namespace builder
{

class Init_SceneObjectAdd_coordinates
{
public:
  explicit Init_SceneObjectAdd_coordinates(::robo_planner_msgs::msg::SceneObjectAdd & msg)
  : msg_(msg)
  {}
  ::robo_planner_msgs::msg::SceneObjectAdd coordinates(::robo_planner_msgs::msg::SceneObjectAdd::_coordinates_type arg)
  {
    msg_.coordinates = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robo_planner_msgs::msg::SceneObjectAdd msg_;
};

class Init_SceneObjectAdd_collisionobjectkey
{
public:
  explicit Init_SceneObjectAdd_collisionobjectkey(::robo_planner_msgs::msg::SceneObjectAdd & msg)
  : msg_(msg)
  {}
  Init_SceneObjectAdd_coordinates collisionobjectkey(::robo_planner_msgs::msg::SceneObjectAdd::_collisionobjectkey_type arg)
  {
    msg_.collisionobjectkey = std::move(arg);
    return Init_SceneObjectAdd_coordinates(msg_);
  }

private:
  ::robo_planner_msgs::msg::SceneObjectAdd msg_;
};

class Init_SceneObjectAdd_name
{
public:
  Init_SceneObjectAdd_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SceneObjectAdd_collisionobjectkey name(::robo_planner_msgs::msg::SceneObjectAdd::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_SceneObjectAdd_collisionobjectkey(msg_);
  }

private:
  ::robo_planner_msgs::msg::SceneObjectAdd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robo_planner_msgs::msg::SceneObjectAdd>()
{
  return robo_planner_msgs::msg::builder::Init_SceneObjectAdd_name();
}

}  // namespace robo_planner_msgs

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_ADD__BUILDER_HPP_
