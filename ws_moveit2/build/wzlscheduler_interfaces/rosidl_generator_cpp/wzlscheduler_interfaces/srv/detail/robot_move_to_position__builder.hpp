// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:srv/RobotMoveToPosition.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/srv/detail/robot_move_to_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_RobotMoveToPosition_Request_movetype
{
public:
  explicit Init_RobotMoveToPosition_Request_movetype(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request & msg)
  : msg_(msg)
  {}
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request movetype(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request::_movetype_type arg)
  {
    msg_.movetype = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request msg_;
};

class Init_RobotMoveToPosition_Request_rotz
{
public:
  explicit Init_RobotMoveToPosition_Request_rotz(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request & msg)
  : msg_(msg)
  {}
  Init_RobotMoveToPosition_Request_movetype rotz(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request::_rotz_type arg)
  {
    msg_.rotz = std::move(arg);
    return Init_RobotMoveToPosition_Request_movetype(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request msg_;
};

class Init_RobotMoveToPosition_Request_roty
{
public:
  explicit Init_RobotMoveToPosition_Request_roty(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request & msg)
  : msg_(msg)
  {}
  Init_RobotMoveToPosition_Request_rotz roty(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request::_roty_type arg)
  {
    msg_.roty = std::move(arg);
    return Init_RobotMoveToPosition_Request_rotz(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request msg_;
};

class Init_RobotMoveToPosition_Request_rotx
{
public:
  explicit Init_RobotMoveToPosition_Request_rotx(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request & msg)
  : msg_(msg)
  {}
  Init_RobotMoveToPosition_Request_roty rotx(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request::_rotx_type arg)
  {
    msg_.rotx = std::move(arg);
    return Init_RobotMoveToPosition_Request_roty(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request msg_;
};

class Init_RobotMoveToPosition_Request_posz
{
public:
  explicit Init_RobotMoveToPosition_Request_posz(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request & msg)
  : msg_(msg)
  {}
  Init_RobotMoveToPosition_Request_rotx posz(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request::_posz_type arg)
  {
    msg_.posz = std::move(arg);
    return Init_RobotMoveToPosition_Request_rotx(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request msg_;
};

class Init_RobotMoveToPosition_Request_posy
{
public:
  explicit Init_RobotMoveToPosition_Request_posy(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request & msg)
  : msg_(msg)
  {}
  Init_RobotMoveToPosition_Request_posz posy(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request::_posy_type arg)
  {
    msg_.posy = std::move(arg);
    return Init_RobotMoveToPosition_Request_posz(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request msg_;
};

class Init_RobotMoveToPosition_Request_posx
{
public:
  Init_RobotMoveToPosition_Request_posx()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotMoveToPosition_Request_posy posx(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request::_posx_type arg)
  {
    msg_.posx = std::move(arg);
    return Init_RobotMoveToPosition_Request_posy(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request>()
{
  return wzlscheduler_interfaces::srv::builder::Init_RobotMoveToPosition_Request_posx();
}

}  // namespace wzlscheduler_interfaces


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_RobotMoveToPosition_Response_result
{
public:
  Init_RobotMoveToPosition_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Response result(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::RobotMoveToPosition_Response>()
{
  return wzlscheduler_interfaces::srv::builder::Init_RobotMoveToPosition_Response_result();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__BUILDER_HPP_
