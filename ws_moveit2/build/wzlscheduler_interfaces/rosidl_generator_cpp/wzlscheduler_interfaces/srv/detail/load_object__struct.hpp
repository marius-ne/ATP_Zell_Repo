// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from wzlscheduler_interfaces:srv/LoadObject.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__LOAD_OBJECT__STRUCT_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__LOAD_OBJECT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'coordinates'
#include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__srv__LoadObject_Request __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__LoadObject_Request __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct LoadObject_Request_
{
  using Type = LoadObject_Request_<ContainerAllocator>;

  explicit LoadObject_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : coordinates(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->scale = 0.0;
    }
  }

  explicit LoadObject_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc),
    coordinates(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->scale = 0.0;
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _coordinates_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _coordinates_type coordinates;
  using _scale_type =
    double;
  _scale_type scale;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__coordinates(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->coordinates = _arg;
    return *this;
  }
  Type & set__scale(
    const double & _arg)
  {
    this->scale = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__LoadObject_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__LoadObject_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::LoadObject_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LoadObject_Request_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->coordinates != other.coordinates) {
      return false;
    }
    if (this->scale != other.scale) {
      return false;
    }
    return true;
  }
  bool operator!=(const LoadObject_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LoadObject_Request_

// alias to use template instance with default allocator
using LoadObject_Request =
  wzlscheduler_interfaces::srv::LoadObject_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces


#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__srv__LoadObject_Response __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__LoadObject_Response __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct LoadObject_Response_
{
  using Type = LoadObject_Response_<ContainerAllocator>;

  explicit LoadObject_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0l;
    }
  }

  explicit LoadObject_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__LoadObject_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__LoadObject_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::LoadObject_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LoadObject_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const LoadObject_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LoadObject_Response_

// alias to use template instance with default allocator
using LoadObject_Response =
  wzlscheduler_interfaces::srv::LoadObject_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces

namespace wzlscheduler_interfaces
{

namespace srv
{

struct LoadObject
{
  using Request = wzlscheduler_interfaces::srv::LoadObject_Request;
  using Response = wzlscheduler_interfaces::srv::LoadObject_Response;
};

}  // namespace srv

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__LOAD_OBJECT__STRUCT_HPP_
