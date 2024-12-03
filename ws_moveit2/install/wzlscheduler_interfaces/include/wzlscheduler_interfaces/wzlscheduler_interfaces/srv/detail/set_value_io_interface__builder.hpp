// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:srv/SetValueIoInterface.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__SET_VALUE_IO_INTERFACE__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__SET_VALUE_IO_INTERFACE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/srv/detail/set_value_io_interface__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetValueIoInterface_Request_value
{
public:
  explicit Init_SetValueIoInterface_Request_value(::wzlscheduler_interfaces::srv::SetValueIoInterface_Request & msg)
  : msg_(msg)
  {}
  ::wzlscheduler_interfaces::srv::SetValueIoInterface_Request value(::wzlscheduler_interfaces::srv::SetValueIoInterface_Request::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::SetValueIoInterface_Request msg_;
};

class Init_SetValueIoInterface_Request_slotindex
{
public:
  Init_SetValueIoInterface_Request_slotindex()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetValueIoInterface_Request_value slotindex(::wzlscheduler_interfaces::srv::SetValueIoInterface_Request::_slotindex_type arg)
  {
    msg_.slotindex = std::move(arg);
    return Init_SetValueIoInterface_Request_value(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::SetValueIoInterface_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::SetValueIoInterface_Request>()
{
  return wzlscheduler_interfaces::srv::builder::Init_SetValueIoInterface_Request_slotindex();
}

}  // namespace wzlscheduler_interfaces


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetValueIoInterface_Response_result
{
public:
  Init_SetValueIoInterface_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wzlscheduler_interfaces::srv::SetValueIoInterface_Response result(::wzlscheduler_interfaces::srv::SetValueIoInterface_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::SetValueIoInterface_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::SetValueIoInterface_Response>()
{
  return wzlscheduler_interfaces::srv::builder::Init_SetValueIoInterface_Response_result();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__SET_VALUE_IO_INTERFACE__BUILDER_HPP_
