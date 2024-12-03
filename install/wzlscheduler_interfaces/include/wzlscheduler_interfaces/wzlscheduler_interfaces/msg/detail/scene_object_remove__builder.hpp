// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:msg/SceneObjectRemove.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_REMOVE__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_REMOVE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/msg/detail/scene_object_remove__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
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
  ::wzlscheduler_interfaces::msg::SceneObjectRemove name(::wzlscheduler_interfaces::msg::SceneObjectRemove::_name_type arg)
  {
    msg_.name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::SceneObjectRemove msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::msg::SceneObjectRemove>()
{
  return wzlscheduler_interfaces::msg::builder::Init_SceneObjectRemove_name();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_REMOVE__BUILDER_HPP_
