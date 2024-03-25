#include <memory>

#include "wzlscheduler_interfaces/srv/robot_move_to_position.hpp"

#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>

using moveit::planning_interface::MoveGroupInterface;

std::shared_ptr<MoveGroupInterface> move_group_interface_;

void MoveToPosition(const std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition::Request> request,
          std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition::Response> response)
{
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request (move to position)\nX: %g" " Y: %g Z: %g RotX: %g RotY %g RotZ %g",
                request->posx, request->posy, request->posz, request->rotx, request->roty, request->rotz);
  //RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);

  // Set a target Pose
  geometry_msgs::msg::Pose msg;
  msg.orientation.w = 1.0; // todo: set also the orientation
  msg.position.x = request->posx;
  msg.position.y = request->posy;
  msg.position.z = request->posz;
  msg.orientation.x = request->rotx;
  msg.orientation.y = request->roty;
  msg.orientation.z = request->rotz;
  //msg.orientation.w = request->rotw;

  move_group_interface_->setPoseTarget(msg);

  // Create a plan to that target pose
  //auto const [success, plan] = [&move_group_interface]{
  //  moveit::planning_interface::MoveGroupInterface::Plan msg;
  //  auto const ok = static_cast<bool>(move_group_interface.plan(msg));
  //  return std::make_pair(ok, msg);
  //}();

    moveit::planning_interface::MoveGroupInterface::Plan msg2;
    auto const success = static_cast<bool>(move_group_interface_->plan(msg2));

  // Execute the plan
  if(success) {
    move_group_interface_->execute(msg2);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Planing failed!");
  }
  
  
  response->result = true;
}

int main(int argc, char * argv[])
{
  // Initialize ROS and create the Node
  rclcpp::init(argc, argv);
  auto const node = std::make_shared<rclcpp::Node>(
    "hello_moveit",
    rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true)
  );

  // Create the MoveIt MoveGroup Interface
  move_group_interface_ = std::make_shared<MoveGroupInterface>(node, "panda_arm");

  // Shutdown ROS
  rclcpp::shutdown();
  return 0;
}