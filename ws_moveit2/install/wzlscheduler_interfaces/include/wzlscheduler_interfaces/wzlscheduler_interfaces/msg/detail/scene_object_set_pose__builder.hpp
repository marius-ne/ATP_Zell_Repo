// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:msg/SceneObjectSetPose.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_SET_POSE__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_SET_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/msg/detail/scene_object_set_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace msg
{

namespace builder
{

class Init_SceneObjectSetPose_coordinates
{
public:
  explicit Init_SceneObjectSetPose_coordinates(::wzlscheduler_interfaces::msg::SceneObjectSetPose & msg)
  : msg_(msg)
  {}
  ::wzlscheduler_interfaces::msg::SceneObjectSetPose coordinates(::wzlscheduler_interfaces::msg::SceneObjectSetPose::_coordinates_type arg)
  {
    msg_.coordinates = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::SceneObjectSetPose msg_;
};

class Init_SceneObjectSetPose_name
{
public:
  Init_SceneObjectSetPose_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SceneObjectSetPose_coordinates name(::wzlscheduler_interfaces::msg::SceneObjectSetPose::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_SceneObjectSetPose_coordinates(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::SceneObjectSetPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::msg::SceneObjectSetPose>()
{
  return wzlscheduler_interfaces::msg::builder::Init_SceneObjectSetPose_name();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_SET_POSE__BUILDER_HPP_
