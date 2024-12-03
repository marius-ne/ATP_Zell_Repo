// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from opcua_interfaces_io_link:msg/SensorRead.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__STRUCT_HPP_
#define OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__opcua_interfaces_io_link__msg__SensorRead __attribute__((deprecated))
#else
# define DEPRECATED__opcua_interfaces_io_link__msg__SensorRead __declspec(deprecated)
#endif

namespace opcua_interfaces_io_link
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SensorRead_
{
  using Type = SensorRead_<ContainerAllocator>;

  explicit SensorRead_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sensor_id = "";
      this->sensor_read_type = 0;
      this->sensor_value_bool = false;
      this->sensor_value_int = 0;
    }
  }

  explicit SensorRead_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : sensor_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sensor_id = "";
      this->sensor_read_type = 0;
      this->sensor_value_bool = false;
      this->sensor_value_int = 0;
    }
  }

  // field types and members
  using _sensor_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _sensor_id_type sensor_id;
  using _sensor_read_type_type =
    int8_t;
  _sensor_read_type_type sensor_read_type;
  using _sensor_value_bool_type =
    bool;
  _sensor_value_bool_type sensor_value_bool;
  using _sensor_value_int_type =
    uint16_t;
  _sensor_value_int_type sensor_value_int;

  // setters for named parameter idiom
  Type & set__sensor_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->sensor_id = _arg;
    return *this;
  }
  Type & set__sensor_read_type(
    const int8_t & _arg)
  {
    this->sensor_read_type = _arg;
    return *this;
  }
  Type & set__sensor_value_bool(
    const bool & _arg)
  {
    this->sensor_value_bool = _arg;
    return *this;
  }
  Type & set__sensor_value_int(
    const uint16_t & _arg)
  {
    this->sensor_value_int = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator> *;
  using ConstRawPtr =
    const opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__opcua_interfaces_io_link__msg__SensorRead
    std::shared_ptr<opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__opcua_interfaces_io_link__msg__SensorRead
    std::shared_ptr<opcua_interfaces_io_link::msg::SensorRead_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorRead_ & other) const
  {
    if (this->sensor_id != other.sensor_id) {
      return false;
    }
    if (this->sensor_read_type != other.sensor_read_type) {
      return false;
    }
    if (this->sensor_value_bool != other.sensor_value_bool) {
      return false;
    }
    if (this->sensor_value_int != other.sensor_value_int) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorRead_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorRead_

// alias to use template instance with default allocator
using SensorRead =
  opcua_interfaces_io_link::msg::SensorRead_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace opcua_interfaces_io_link

#endif  // OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__STRUCT_HPP_
