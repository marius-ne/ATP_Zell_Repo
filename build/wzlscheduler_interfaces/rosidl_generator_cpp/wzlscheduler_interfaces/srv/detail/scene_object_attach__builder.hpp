// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:srv/SceneObjectAttach.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ATTACH__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ATTACH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/srv/detail/scene_object_attach__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_SceneObjectAttach_Request_parentkey
{
public:
  explicit Init_SceneObjectAttach_Request_parentkey(::wzlscheduler_interfaces::srv::SceneObjectAttach_Request & msg)
  : msg_(msg)
  {}
  ::wzlscheduler_interfaces::srv::SceneObjectAttach_Request parentkey(::wzlscheduler_interfaces::srv::SceneObjectAttach_Request::_parentkey_type arg)
  {
    msg_.parentkey = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::SceneObjectAttach_Request msg_;
};

class Init_SceneObjectAttach_Request_name
{
public:
  Init_SceneObjectAttach_Request_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SceneObjectAttach_Request_parentkey name(::wzlscheduler_interfaces::srv::SceneObjectAttach_Request::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_SceneObjectAttach_Request_parentkey(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::SceneObjectAttach_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::SceneObjectAttach_Request>()
{
  return wzlscheduler_interfaces::srv::builder::Init_SceneObjectAttach_Request_name();
}

}  // namespace wzlscheduler_interfaces


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_SceneObjectAttach_Response_result
{
public:
  Init_SceneObjectAttach_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wzlscheduler_interfaces::srv::SceneObjectAttach_Response result(::wzlscheduler_interfaces::srv::SceneObjectAttach_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::SceneObjectAttach_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::SceneObjectAttach_Response>()
{
  return wzlscheduler_interfaces::srv::builder::Init_SceneObjectAttach_Response_result();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ATTACH__BUILDER_HPP_
