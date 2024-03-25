// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from wzlscheduler_interfaces:srv/RobotMoveToPosition.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__STRUCT_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__srv__RobotMoveToPosition_Request __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__RobotMoveToPosition_Request __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct RobotMoveToPosition_Request_
{
  using Type = RobotMoveToPosition_Request_<ContainerAllocator>;

  explicit RobotMoveToPosition_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->posx = 0.0;
      this->posy = 0.0;
      this->posz = 0.0;
      this->rotx = 0.0;
      this->roty = 0.0;
      this->rotz = 0.0;
      this->movetype = 0l;
    }
  }

  explicit RobotMoveToPosition_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->posx = 0.0;
      this->posy = 0.0;
      this->posz = 0.0;
      this->rotx = 0.0;
      this->roty = 0.0;
      this->rotz = 0.0;
      this->movetype = 0l;
    }
  }

  // field types and members
  using _posx_type =
    double;
  _posx_type posx;
  using _posy_type =
    double;
  _posy_type posy;
  using _posz_type =
    double;
  _posz_type posz;
  using _rotx_type =
    double;
  _rotx_type rotx;
  using _roty_type =
    double;
  _roty_type roty;
  using _rotz_type =
    double;
  _rotz_type rotz;
  using _movetype_type =
    int32_t;
  _movetype_type movetype;

  // setters for named parameter idiom
  Type & set__posx(
    const double & _arg)
  {
    this->posx = _arg;
    return *this;
  }
  Type & set__posy(
    const double & _arg)
  {
    this->posy = _arg;
    return *this;
  }
  Type & set__posz(
    const double & _arg)
  {
    this->posz = _arg;
    return *this;
  }
  Type & set__rotx(
    const double & _arg)
  {
    this->rotx = _arg;
    return *this;
  }
  Type & set__roty(
    const double & _arg)
  {
    this->roty = _arg;
    return *this;
  }
  Type & set__rotz(
    const double & _arg)
  {
    this->rotz = _arg;
    return *this;
  }
  Type & set__movetype(
    const int32_t & _arg)
  {
    this->movetype = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__RobotMoveToPosition_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__RobotMoveToPosition_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotMoveToPosition_Request_ & other) const
  {
    if (this->posx != other.posx) {
      return false;
    }
    if (this->posy != other.posy) {
      return false;
    }
    if (this->posz != other.posz) {
      return false;
    }
    if (this->rotx != other.rotx) {
      return false;
    }
    if (this->roty != other.roty) {
      return false;
    }
    if (this->rotz != other.rotz) {
      return false;
    }
    if (this->movetype != other.movetype) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotMoveToPosition_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotMoveToPosition_Request_

// alias to use template instance with default allocator
using RobotMoveToPosition_Request =
  wzlscheduler_interfaces::srv::RobotMoveToPosition_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces


#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__srv__RobotMoveToPosition_Response __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__RobotMoveToPosition_Response __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct RobotMoveToPosition_Response_
{
  using Type = RobotMoveToPosition_Response_<ContainerAllocator>;

  explicit RobotMoveToPosition_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0l;
    }
  }

  explicit RobotMoveToPosition_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__RobotMoveToPosition_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__RobotMoveToPosition_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotMoveToPosition_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotMoveToPosition_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotMoveToPosition_Response_

// alias to use template instance with default allocator
using RobotMoveToPosition_Response =
  wzlscheduler_interfaces::srv::RobotMoveToPosition_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces

namespace wzlscheduler_interfaces
{

namespace srv
{

struct RobotMoveToPosition
{
  using Request = wzlscheduler_interfaces::srv::RobotMoveToPosition_Request;
  using Response = wzlscheduler_interfaces::srv::RobotMoveToPosition_Response;
};

}  // namespace srv

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__STRUCT_HPP_
