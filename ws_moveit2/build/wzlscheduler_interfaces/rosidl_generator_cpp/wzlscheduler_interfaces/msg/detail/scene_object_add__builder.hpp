// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:msg/SceneObjectAdd.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_ADD__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_ADD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/msg/detail/scene_object_add__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace msg
{

namespace builder
{

class Init_SceneObjectAdd_coordinates
{
public:
  explicit Init_SceneObjectAdd_coordinates(::wzlscheduler_interfaces::msg::SceneObjectAdd & msg)
  : msg_(msg)
  {}
  ::wzlscheduler_interfaces::msg::SceneObjectAdd coordinates(::wzlscheduler_interfaces::msg::SceneObjectAdd::_coordinates_type arg)
  {
    msg_.coordinates = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::SceneObjectAdd msg_;
};

class Init_SceneObjectAdd_collisionobjectkey
{
public:
  explicit Init_SceneObjectAdd_collisionobjectkey(::wzlscheduler_interfaces::msg::SceneObjectAdd & msg)
  : msg_(msg)
  {}
  Init_SceneObjectAdd_coordinates collisionobjectkey(::wzlscheduler_interfaces::msg::SceneObjectAdd::_collisionobjectkey_type arg)
  {
    msg_.collisionobjectkey = std::move(arg);
    return Init_SceneObjectAdd_coordinates(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::SceneObjectAdd msg_;
};

class Init_SceneObjectAdd_name
{
public:
  Init_SceneObjectAdd_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SceneObjectAdd_collisionobjectkey name(::wzlscheduler_interfaces::msg::SceneObjectAdd::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_SceneObjectAdd_collisionobjectkey(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::SceneObjectAdd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::msg::SceneObjectAdd>()
{
  return wzlscheduler_interfaces::msg::builder::Init_SceneObjectAdd_name();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_ADD__BUILDER_HPP_
