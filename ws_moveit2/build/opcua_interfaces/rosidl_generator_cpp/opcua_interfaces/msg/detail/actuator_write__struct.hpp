// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from opcua_interfaces:msg/ActuatorWrite.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__STRUCT_HPP_
#define OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__opcua_interfaces__msg__ActuatorWrite __attribute__((deprecated))
#else
# define DEPRECATED__opcua_interfaces__msg__ActuatorWrite __declspec(deprecated)
#endif

namespace opcua_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ActuatorWrite_
{
  using Type = ActuatorWrite_<ContainerAllocator>;

  explicit ActuatorWrite_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->actuator_id = "";
      this->actuator_write_type = 0;
      this->actuator_command_bool1 = false;
      this->actuator_command_bool2 = false;
    }
  }

  explicit ActuatorWrite_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : actuator_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->actuator_id = "";
      this->actuator_write_type = 0;
      this->actuator_command_bool1 = false;
      this->actuator_command_bool2 = false;
    }
  }

  // field types and members
  using _actuator_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _actuator_id_type actuator_id;
  using _actuator_write_type_type =
    int8_t;
  _actuator_write_type_type actuator_write_type;
  using _actuator_command_bool1_type =
    bool;
  _actuator_command_bool1_type actuator_command_bool1;
  using _actuator_command_bool2_type =
    bool;
  _actuator_command_bool2_type actuator_command_bool2;

  // setters for named parameter idiom
  Type & set__actuator_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->actuator_id = _arg;
    return *this;
  }
  Type & set__actuator_write_type(
    const int8_t & _arg)
  {
    this->actuator_write_type = _arg;
    return *this;
  }
  Type & set__actuator_command_bool1(
    const bool & _arg)
  {
    this->actuator_command_bool1 = _arg;
    return *this;
  }
  Type & set__actuator_command_bool2(
    const bool & _arg)
  {
    this->actuator_command_bool2 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator> *;
  using ConstRawPtr =
    const opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__opcua_interfaces__msg__ActuatorWrite
    std::shared_ptr<opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__opcua_interfaces__msg__ActuatorWrite
    std::shared_ptr<opcua_interfaces::msg::ActuatorWrite_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ActuatorWrite_ & other) const
  {
    if (this->actuator_id != other.actuator_id) {
      return false;
    }
    if (this->actuator_write_type != other.actuator_write_type) {
      return false;
    }
    if (this->actuator_command_bool1 != other.actuator_command_bool1) {
      return false;
    }
    if (this->actuator_command_bool2 != other.actuator_command_bool2) {
      return false;
    }
    return true;
  }
  bool operator!=(const ActuatorWrite_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ActuatorWrite_

// alias to use template instance with default allocator
using ActuatorWrite =
  opcua_interfaces::msg::ActuatorWrite_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace opcua_interfaces

#endif  // OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__STRUCT_HPP_
