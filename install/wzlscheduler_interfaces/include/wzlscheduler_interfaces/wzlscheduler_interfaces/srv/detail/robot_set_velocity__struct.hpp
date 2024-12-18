// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from wzlscheduler_interfaces:srv/RobotSetVelocity.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_SET_VELOCITY__STRUCT_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_SET_VELOCITY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__srv__RobotSetVelocity_Request __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__RobotSetVelocity_Request __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct RobotSetVelocity_Request_
{
  using Type = RobotSetVelocity_Request_<ContainerAllocator>;

  explicit RobotSetVelocity_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocityscalingfactor = 0.0;
      this->accelerationscalingfactor = 0.0;
      this->type = 0l;
    }
  }

  explicit RobotSetVelocity_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocityscalingfactor = 0.0;
      this->accelerationscalingfactor = 0.0;
      this->type = 0l;
    }
  }

  // field types and members
  using _velocityscalingfactor_type =
    double;
  _velocityscalingfactor_type velocityscalingfactor;
  using _accelerationscalingfactor_type =
    double;
  _accelerationscalingfactor_type accelerationscalingfactor;
  using _type_type =
    int32_t;
  _type_type type;

  // setters for named parameter idiom
  Type & set__velocityscalingfactor(
    const double & _arg)
  {
    this->velocityscalingfactor = _arg;
    return *this;
  }
  Type & set__accelerationscalingfactor(
    const double & _arg)
  {
    this->accelerationscalingfactor = _arg;
    return *this;
  }
  Type & set__type(
    const int32_t & _arg)
  {
    this->type = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__RobotSetVelocity_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__RobotSetVelocity_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotSetVelocity_Request_ & other) const
  {
    if (this->velocityscalingfactor != other.velocityscalingfactor) {
      return false;
    }
    if (this->accelerationscalingfactor != other.accelerationscalingfactor) {
      return false;
    }
    if (this->type != other.type) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotSetVelocity_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotSetVelocity_Request_

// alias to use template instance with default allocator
using RobotSetVelocity_Request =
  wzlscheduler_interfaces::srv::RobotSetVelocity_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces


#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__srv__RobotSetVelocity_Response __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__RobotSetVelocity_Response __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct RobotSetVelocity_Response_
{
  using Type = RobotSetVelocity_Response_<ContainerAllocator>;

  explicit RobotSetVelocity_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0l;
    }
  }

  explicit RobotSetVelocity_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0l;
    }
  }

  // field types and members
  using _result_type =
    int32_t;
  _result_type result;

  // setters for named parameter idiom
  Type & set__result(
    const int32_t & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__RobotSetVelocity_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__RobotSetVelocity_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotSetVelocity_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotSetVelocity_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotSetVelocity_Response_

// alias to use template instance with default allocator
using RobotSetVelocity_Response =
  wzlscheduler_interfaces::srv::RobotSetVelocity_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces

namespace wzlscheduler_interfaces
{

namespace srv
{

struct RobotSetVelocity
{
  using Request = wzlscheduler_interfaces::srv::RobotSetVelocity_Request;
  using Response = wzlscheduler_interfaces::srv::RobotSetVelocity_Response;
};

}  // namespace srv

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_SET_VELOCITY__STRUCT_HPP_
