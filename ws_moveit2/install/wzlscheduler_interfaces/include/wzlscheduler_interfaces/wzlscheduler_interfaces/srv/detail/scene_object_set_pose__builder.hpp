// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:srv/SceneObjectSetPose.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_SET_POSE__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_SET_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/srv/detail/scene_object_set_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_SceneObjectSetPose_Request_coordinates
{
public:
  explicit Init_SceneObjectSetPose_Request_coordinates(::wzlscheduler_interfaces::srv::SceneObjectSetPose_Request & msg)
  : msg_(msg)
  {}
  ::wzlscheduler_interfaces::srv::SceneObjectSetPose_Request coordinates(::wzlscheduler_interfaces::srv::SceneObjectSetPose_Request::_coordinates_type arg)
  {
    msg_.coordinates = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::SceneObjectSetPose_Request msg_;
};

class Init_SceneObjectSetPose_Request_name
{
public:
  Init_SceneObjectSetPose_Request_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SceneObjectSetPose_Request_coordinates name(::wzlscheduler_interfaces::srv::SceneObjectSetPose_Request::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_SceneObjectSetPose_Request_coordinates(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::SceneObjectSetPose_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::SceneObjectSetPose_Request>()
{
  return wzlscheduler_interfaces::srv::builder::Init_SceneObjectSetPose_Request_name();
}

}  // namespace wzlscheduler_interfaces


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_SceneObjectSetPose_Response_result
{
public:
  Init_SceneObjectSetPose_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wzlscheduler_interfaces::srv::SceneObjectSetPose_Response result(::wzlscheduler_interfaces::srv::SceneObjectSetPose_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::SceneObjectSetPose_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::SceneObjectSetPose_Response>()
{
  return wzlscheduler_interfaces::srv::builder::Init_SceneObjectSetPose_Response_result();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_SET_POSE__BUILDER_HPP_
