// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ur16e_interfaces:msg/LoadObject.idl
// generated code does not contain a copyright notice

#ifndef UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__BUILDER_HPP_
#define UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ur16e_interfaces/msg/detail/load_object__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ur16e_interfaces
{

namespace msg
{

namespace builder
{

class Init_LoadObject_scale
{
public:
  explicit Init_LoadObject_scale(::ur16e_interfaces::msg::LoadObject & msg)
  : msg_(msg)
  {}
  ::ur16e_interfaces::msg::LoadObject scale(::ur16e_interfaces::msg::LoadObject::_scale_type arg)
  {
    msg_.scale = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur16e_interfaces::msg::LoadObject msg_;
};

class Init_LoadObject_coordinates
{
public:
  explicit Init_LoadObject_coordinates(::ur16e_interfaces::msg::LoadObject & msg)
  : msg_(msg)
  {}
  Init_LoadObject_scale coordinates(::ur16e_interfaces::msg::LoadObject::_coordinates_type arg)
  {
    msg_.coordinates = std::move(arg);
    return Init_LoadObject_scale(msg_);
  }

private:
  ::ur16e_interfaces::msg::LoadObject msg_;
};

class Init_LoadObject_name
{
public:
  Init_LoadObject_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LoadObject_coordinates name(::ur16e_interfaces::msg::LoadObject::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_LoadObject_coordinates(msg_);
  }

private:
  ::ur16e_interfaces::msg::LoadObject msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur16e_interfaces::msg::LoadObject>()
{
  return ur16e_interfaces::msg::builder::Init_LoadObject_name();
}

}  // namespace ur16e_interfaces

#endif  // UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__BUILDER_HPP_
