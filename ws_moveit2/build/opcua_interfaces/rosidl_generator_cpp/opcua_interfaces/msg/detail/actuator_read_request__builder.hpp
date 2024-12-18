// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from opcua_interfaces:msg/ActuatorReadRequest.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__BUILDER_HPP_
#define OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "opcua_interfaces/msg/detail/actuator_read_request__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace opcua_interfaces
{

namespace msg
{

namespace builder
{

class Init_ActuatorReadRequest_actuator_read_type
{
public:
  explicit Init_ActuatorReadRequest_actuator_read_type(::opcua_interfaces::msg::ActuatorReadRequest & msg)
  : msg_(msg)
  {}
  ::opcua_interfaces::msg::ActuatorReadRequest actuator_read_type(::opcua_interfaces::msg::ActuatorReadRequest::_actuator_read_type_type arg)
  {
    msg_.actuator_read_type = std::move(arg);
    return std::move(msg_);
  }

private:
  ::opcua_interfaces::msg::ActuatorReadRequest msg_;
};

class Init_ActuatorReadRequest_actuator_id
{
public:
  Init_ActuatorReadRequest_actuator_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ActuatorReadRequest_actuator_read_type actuator_id(::opcua_interfaces::msg::ActuatorReadRequest::_actuator_id_type arg)
  {
    msg_.actuator_id = std::move(arg);
    return Init_ActuatorReadRequest_actuator_read_type(msg_);
  }

private:
  ::opcua_interfaces::msg::ActuatorReadRequest msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::opcua_interfaces::msg::ActuatorReadRequest>()
{
  return opcua_interfaces::msg::builder::Init_ActuatorReadRequest_actuator_id();
}

}  // namespace opcua_interfaces

#endif  // OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__BUILDER_HPP_
