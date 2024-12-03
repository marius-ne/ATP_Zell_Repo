// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from opcua_interfaces:msg/ActuatorRead.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ__BUILDER_HPP_
#define OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "opcua_interfaces/msg/detail/actuator_read__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace opcua_interfaces
{

namespace msg
{

namespace builder
{

class Init_ActuatorRead_actuator_value_int
{
public:
  explicit Init_ActuatorRead_actuator_value_int(::opcua_interfaces::msg::ActuatorRead & msg)
  : msg_(msg)
  {}
  ::opcua_interfaces::msg::ActuatorRead actuator_value_int(::opcua_interfaces::msg::ActuatorRead::_actuator_value_int_type arg)
  {
    msg_.actuator_value_int = std::move(arg);
    return std::move(msg_);
  }

private:
  ::opcua_interfaces::msg::ActuatorRead msg_;
};

class Init_ActuatorRead_actuator_value_bool
{
public:
  explicit Init_ActuatorRead_actuator_value_bool(::opcua_interfaces::msg::ActuatorRead & msg)
  : msg_(msg)
  {}
  Init_ActuatorRead_actuator_value_int actuator_value_bool(::opcua_interfaces::msg::ActuatorRead::_actuator_value_bool_type arg)
  {
    msg_.actuator_value_bool = std::move(arg);
    return Init_ActuatorRead_actuator_value_int(msg_);
  }

private:
  ::opcua_interfaces::msg::ActuatorRead msg_;
};

class Init_ActuatorRead_actuator_read_type
{
public:
  explicit Init_ActuatorRead_actuator_read_type(::opcua_interfaces::msg::ActuatorRead & msg)
  : msg_(msg)
  {}
  Init_ActuatorRead_actuator_value_bool actuator_read_type(::opcua_interfaces::msg::ActuatorRead::_actuator_read_type_type arg)
  {
    msg_.actuator_read_type = std::move(arg);
    return Init_ActuatorRead_actuator_value_bool(msg_);
  }

private:
  ::opcua_interfaces::msg::ActuatorRead msg_;
};

class Init_ActuatorRead_actuator_id
{
public:
  Init_ActuatorRead_actuator_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ActuatorRead_actuator_read_type actuator_id(::opcua_interfaces::msg::ActuatorRead::_actuator_id_type arg)
  {
    msg_.actuator_id = std::move(arg);
    return Init_ActuatorRead_actuator_read_type(msg_);
  }

private:
  ::opcua_interfaces::msg::ActuatorRead msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::opcua_interfaces::msg::ActuatorRead>()
{
  return opcua_interfaces::msg::builder::Init_ActuatorRead_actuator_id();
}

}  // namespace opcua_interfaces

#endif  // OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ__BUILDER_HPP_
