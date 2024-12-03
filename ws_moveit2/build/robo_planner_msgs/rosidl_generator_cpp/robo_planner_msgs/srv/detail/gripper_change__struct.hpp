// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robo_planner_msgs:srv/GripperChange.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE__STRUCT_HPP_
#define ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robo_planner_msgs__srv__GripperChange_Request __attribute__((deprecated))
#else
# define DEPRECATED__robo_planner_msgs__srv__GripperChange_Request __declspec(deprecated)
#endif

namespace robo_planner_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GripperChange_Request_
{
  using Type = GripperChange_Request_<ContainerAllocator>;

  explicit GripperChange_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->subtaskgripperhangepick = 0l;
      this->subtaskgripperhangeplace = 0l;
    }
  }

  explicit GripperChange_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->subtaskgripperhangepick = 0l;
      this->subtaskgripperhangeplace = 0l;
    }
  }

  // field types and members
  using _subtaskgripperhangepick_type =
    int32_t;
  _subtaskgripperhangepick_type subtaskgripperhangepick;
  using _subtaskgripperhangeplace_type =
    int32_t;
  _subtaskgripperhangeplace_type subtaskgripperhangeplace;

  // setters for named parameter idiom
  Type & set__subtaskgripperhangepick(
    const int32_t & _arg)
  {
    this->subtaskgripperhangepick = _arg;
    return *this;
  }
  Type & set__subtaskgripperhangeplace(
    const int32_t & _arg)
  {
    this->subtaskgripperhangeplace = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robo_planner_msgs__srv__GripperChange_Request
    std::shared_ptr<robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robo_planner_msgs__srv__GripperChange_Request
    std::shared_ptr<robo_planner_msgs::srv::GripperChange_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GripperChange_Request_ & other) const
  {
    if (this->subtaskgripperhangepick != other.subtaskgripperhangepick) {
      return false;
    }
    if (this->subtaskgripperhangeplace != other.subtaskgripperhangeplace) {
      return false;
    }
    return true;
  }
  bool operator!=(const GripperChange_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GripperChange_Request_

// alias to use template instance with default allocator
using GripperChange_Request =
  robo_planner_msgs::srv::GripperChange_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace robo_planner_msgs


#ifndef _WIN32
# define DEPRECATED__robo_planner_msgs__srv__GripperChange_Response __attribute__((deprecated))
#else
# define DEPRECATED__robo_planner_msgs__srv__GripperChange_Response __declspec(deprecated)
#endif

namespace robo_planner_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GripperChange_Response_
{
  using Type = GripperChange_Response_<ContainerAllocator>;

  explicit GripperChange_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0l;
    }
  }

  explicit GripperChange_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robo_planner_msgs__srv__GripperChange_Response
    std::shared_ptr<robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robo_planner_msgs__srv__GripperChange_Response
    std::shared_ptr<robo_planner_msgs::srv::GripperChange_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GripperChange_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const GripperChange_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GripperChange_Response_

// alias to use template instance with default allocator
using GripperChange_Response =
  robo_planner_msgs::srv::GripperChange_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace robo_planner_msgs

namespace robo_planner_msgs
{

namespace srv
{

struct GripperChange
{
  using Request = robo_planner_msgs::srv::GripperChange_Request;
  using Response = robo_planner_msgs::srv::GripperChange_Response;
};

}  // namespace srv

}  // namespace robo_planner_msgs

#endif  // ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE__STRUCT_HPP_
