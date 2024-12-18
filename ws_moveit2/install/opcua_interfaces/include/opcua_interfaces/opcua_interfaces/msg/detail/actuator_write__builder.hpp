// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from opcua_interfaces:msg/ActuatorWrite.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__BUILDER_HPP_
#define OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "opcua_interfaces/msg/detail/actuator_write__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace opcua_interfaces
{

namespace msg
{

namespace builder
{

class Init_ActuatorWrite_actuator_command_bool2
{
public:
  explicit Init_ActuatorWrite_actuator_command_bool2(::opcua_interfaces::msg::ActuatorWrite & msg)
  : msg_(msg)
  {}
  ::opcua_interfaces::msg::ActuatorWrite actuator_command_bool2(::opcua_interfaces::msg::ActuatorWrite::_actuator_command_bool2_type arg)
  {
    msg_.actuator_command_bool2 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::opcua_interfaces::msg::ActuatorWrite msg_;
};

class Init_ActuatorWrite_actuator_command_bool1
{
public:
  explicit Init_ActuatorWrite_actuator_command_bool1(::opcua_interfaces::msg::ActuatorWrite & msg)
  : msg_(msg)
  {}
  Init_ActuatorWrite_actuator_command_bool2 actuator_command_bool1(::opcua_interfaces::msg::ActuatorWrite::_actuator_command_bool1_type arg)
  {
    msg_.actuator_command_bool1 = std::move(arg);
    return Init_ActuatorWrite_actuator_command_bool2(msg_);
  }

private:
  ::opcua_interfaces::msg::ActuatorWrite msg_;
};

class Init_ActuatorWrite_actuator_write_type
{
public:
  explicit Init_ActuatorWrite_actuator_write_type(::opcua_interfaces::msg::ActuatorWrite & msg)
  : msg_(msg)
  {}
  Init_ActuatorWrite_actuator_command_bool1 actuator_write_type(::opcua_interfaces::msg::ActuatorWrite::_actuator_write_type_type arg)
  {
    msg_.actuator_write_type = std::move(arg);
    return Init_ActuatorWrite_actuator_command_bool1(msg_);
  }

private:
  ::opcua_interfaces::msg::ActuatorWrite msg_;
};

class Init_ActuatorWrite_actuator_id
{
public:
  Init_ActuatorWrite_actuator_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ActuatorWrite_actuator_write_type actuator_id(::opcua_interfaces::msg::ActuatorWrite::_actuator_id_type arg)
  {
    msg_.actuator_id = std::move(arg);
    return Init_ActuatorWrite_actuator_write_type(msg_);
  }

private:
  ::opcua_interfaces::msg::ActuatorWrite msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::opcua_interfaces::msg::ActuatorWrite>()
{
  return opcua_interfaces::msg::builder::Init_ActuatorWrite_actuator_id();
}

}  // namespace opcua_interfaces

#endif  // OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__BUILDER_HPP_
