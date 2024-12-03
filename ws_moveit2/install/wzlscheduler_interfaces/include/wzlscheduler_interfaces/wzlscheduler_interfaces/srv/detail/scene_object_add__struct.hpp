// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from wzlscheduler_interfaces:srv/SceneObjectAdd.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ADD__STRUCT_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ADD__STRUCT_HPP_

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
# define DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAdd_Request __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAdd_Request __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SceneObjectAdd_Request_
{
  using Type = SceneObjectAdd_Request_<ContainerAllocator>;

  explicit SceneObjectAdd_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : coordinates(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->collisionobjectkey = "";
    }
  }

  explicit SceneObjectAdd_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc),
    collisionobjectkey(_alloc),
    coordinates(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->collisionobjectkey = "";
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _collisionobjectkey_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _collisionobjectkey_type collisionobjectkey;
  using _coordinates_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _coordinates_type coordinates;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__collisionobjectkey(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->collisionobjectkey = _arg;
    return *this;
  }
  Type & set__coordinates(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->coordinates = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAdd_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAdd_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SceneObjectAdd_Request_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->collisionobjectkey != other.collisionobjectkey) {
      return false;
    }
    if (this->coordinates != other.coordinates) {
      return false;
    }
    return true;
  }
  bool operator!=(const SceneObjectAdd_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SceneObjectAdd_Request_

// alias to use template instance with default allocator
using SceneObjectAdd_Request =
  wzlscheduler_interfaces::srv::SceneObjectAdd_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces


#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAdd_Response __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAdd_Response __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SceneObjectAdd_Response_
{
  using Type = SceneObjectAdd_Response_<ContainerAllocator>;

  explicit SceneObjectAdd_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0l;
    }
  }

  explicit SceneObjectAdd_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAdd_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAdd_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SceneObjectAdd_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const SceneObjectAdd_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SceneObjectAdd_Response_

// alias to use template instance with default allocator
using SceneObjectAdd_Response =
  wzlscheduler_interfaces::srv::SceneObjectAdd_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces

namespace wzlscheduler_interfaces
{

namespace srv
{

struct SceneObjectAdd
{
  using Request = wzlscheduler_interfaces::srv::SceneObjectAdd_Request;
  using Response = wzlscheduler_interfaces::srv::SceneObjectAdd_Response;
};

}  // namespace srv

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ADD__STRUCT_HPP_
