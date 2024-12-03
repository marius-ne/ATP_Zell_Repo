// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from wzlscheduler_interfaces:srv/SetValueIoInterface.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__SET_VALUE_IO_INTERFACE__STRUCT_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__SET_VALUE_IO_INTERFACE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__srv__SetValueIoInterface_Request __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__SetValueIoInterface_Request __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetValueIoInterface_Request_
{
  using Type = SetValueIoInterface_Request_<ContainerAllocator>;

  explicit SetValueIoInterface_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->slotindex = 0ll;
      this->value = 0ll;
    }
  }

  explicit SetValueIoInterface_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->slotindex = 0ll;
      this->value = 0ll;
    }
  }

  // field types and members
  using _slotindex_type =
    int64_t;
  _slotindex_type slotindex;
  using _value_type =
    int64_t;
  _value_type value;

  // setters for named parameter idiom
  Type & set__slotindex(
    const int64_t & _arg)
  {
    this->slotindex = _arg;
    return *this;
  }
  Type & set__value(
    const int64_t & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SetValueIoInterface_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SetValueIoInterface_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetValueIoInterface_Request_ & other) const
  {
    if (this->slotindex != other.slotindex) {
      return false;
    }
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetValueIoInterface_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetValueIoInterface_Request_

// alias to use template instance with default allocator
using SetValueIoInterface_Request =
  wzlscheduler_interfaces::srv::SetValueIoInterface_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces


#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__srv__SetValueIoInterface_Response __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__SetValueIoInterface_Response __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetValueIoInterface_Response_
{
  using Type = SetValueIoInterface_Response_<ContainerAllocator>;

  explicit SetValueIoInterface_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = false;
    }
  }

  explicit SetValueIoInterface_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = false;
    }
  }

  // field types and members
  using _result_type =
    bool;
  _result_type result;

  // setters for named parameter idiom
  Type & set__result(
    const bool & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SetValueIoInterface_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SetValueIoInterface_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetValueIoInterface_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetValueIoInterface_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetValueIoInterface_Response_

// alias to use template instance with default allocator
using SetValueIoInterface_Response =
  wzlscheduler_interfaces::srv::SetValueIoInterface_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces

namespace wzlscheduler_interfaces
{

namespace srv
{

struct SetValueIoInterface
{
  using Request = wzlscheduler_interfaces::srv::SetValueIoInterface_Request;
  using Response = wzlscheduler_interfaces::srv::SetValueIoInterface_Response;
};

}  // namespace srv

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__SET_VALUE_IO_INTERFACE__STRUCT_HPP_
