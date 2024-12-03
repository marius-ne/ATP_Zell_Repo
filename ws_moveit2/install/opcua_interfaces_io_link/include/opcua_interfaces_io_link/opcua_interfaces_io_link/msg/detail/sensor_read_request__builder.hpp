// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from opcua_interfaces_io_link:msg/SensorReadRequest.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ_REQUEST__BUILDER_HPP_
#define OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ_REQUEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "opcua_interfaces_io_link/msg/detail/sensor_read_request__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace opcua_interfaces_io_link
{

namespace msg
{

namespace builder
{

class Init_SensorReadRequest_sensor_read_type
{
public:
  explicit Init_SensorReadRequest_sensor_read_type(::opcua_interfaces_io_link::msg::SensorReadRequest & msg)
  : msg_(msg)
  {}
  ::opcua_interfaces_io_link::msg::SensorReadRequest sensor_read_type(::opcua_interfaces_io_link::msg::SensorReadRequest::_sensor_read_type_type arg)
  {
    msg_.sensor_read_type = std::move(arg);
    return std::move(msg_);
  }

private:
  ::opcua_interfaces_io_link::msg::SensorReadRequest msg_;
};

class Init_SensorReadRequest_sensor_id
{
public:
  Init_SensorReadRequest_sensor_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SensorReadRequest_sensor_read_type sensor_id(::opcua_interfaces_io_link::msg::SensorReadRequest::_sensor_id_type arg)
  {
    msg_.sensor_id = std::move(arg);
    return Init_SensorReadRequest_sensor_read_type(msg_);
  }

private:
  ::opcua_interfaces_io_link::msg::SensorReadRequest msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::opcua_interfaces_io_link::msg::SensorReadRequest>()
{
  return opcua_interfaces_io_link::msg::builder::Init_SensorReadRequest_sensor_id();
}

}  // namespace opcua_interfaces_io_link

#endif  // OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ_REQUEST__BUILDER_HPP_
