// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from opcua_interfaces_io_link:msg/SensorRead.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__BUILDER_HPP_
#define OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "opcua_interfaces_io_link/msg/detail/sensor_read__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace opcua_interfaces_io_link
{

namespace msg
{

namespace builder
{

class Init_SensorRead_sensor_value_int
{
public:
  explicit Init_SensorRead_sensor_value_int(::opcua_interfaces_io_link::msg::SensorRead & msg)
  : msg_(msg)
  {}
  ::opcua_interfaces_io_link::msg::SensorRead sensor_value_int(::opcua_interfaces_io_link::msg::SensorRead::_sensor_value_int_type arg)
  {
    msg_.sensor_value_int = std::move(arg);
    return std::move(msg_);
  }

private:
  ::opcua_interfaces_io_link::msg::SensorRead msg_;
};

class Init_SensorRead_sensor_value_bool
{
public:
  explicit Init_SensorRead_sensor_value_bool(::opcua_interfaces_io_link::msg::SensorRead & msg)
  : msg_(msg)
  {}
  Init_SensorRead_sensor_value_int sensor_value_bool(::opcua_interfaces_io_link::msg::SensorRead::_sensor_value_bool_type arg)
  {
    msg_.sensor_value_bool = std::move(arg);
    return Init_SensorRead_sensor_value_int(msg_);
  }

private:
  ::opcua_interfaces_io_link::msg::SensorRead msg_;
};

class Init_SensorRead_sensor_read_type
{
public:
  explicit Init_SensorRead_sensor_read_type(::opcua_interfaces_io_link::msg::SensorRead & msg)
  : msg_(msg)
  {}
  Init_SensorRead_sensor_value_bool sensor_read_type(::opcua_interfaces_io_link::msg::SensorRead::_sensor_read_type_type arg)
  {
    msg_.sensor_read_type = std::move(arg);
    return Init_SensorRead_sensor_value_bool(msg_);
  }

private:
  ::opcua_interfaces_io_link::msg::SensorRead msg_;
};

class Init_SensorRead_sensor_id
{
public:
  Init_SensorRead_sensor_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorRead_sensor_read_type sensor_id(::opcua_interfaces_io_link::msg::SensorRead::_sensor_id_type arg)
  {
    msg_.sensor_id = std::move(arg);
    return Init_SensorRead_sensor_read_type(msg_);
  }

private:
  ::opcua_interfaces_io_link::msg::SensorRead msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::opcua_interfaces_io_link::msg::SensorRead>()
{
  return opcua_interfaces_io_link::msg::builder::Init_SensorRead_sensor_id();
}

}  // namespace opcua_interfaces_io_link

#endif  // OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__BUILDER_HPP_
