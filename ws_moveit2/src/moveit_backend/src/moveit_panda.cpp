#include <memory>

#include "../include/FileLoader.h"

#include "wzlscheduler_interfaces/srv/robot_move_to_position.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_attach.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_detach.hpp"

#include "wzlscheduler_interfaces/msg/scene_object_add.hpp"
#include "wzlscheduler_interfaces/msg/scene_object_remove.hpp"
#include "wzlscheduler_interfaces/msg/scene_object_set_pose.hpp"


#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>

using moveit::planning_interface::MoveGroupInterface;

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

    //move_group_interface_->setPoseTarget(msg);

    //moveit::planning_interface::MoveGroupInterface::Plan msg2;
    //auto const success = static_cast<bool>(move_group_interface_->plan(msg2));
//
    //// Execute the plan
    //if(success) {
    //  move_group_interface_->execute(msg2);
    //} else {
    //  RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Planing failed!");
    //}
    
    response->result = true;
  }  


std::shared_ptr<MoveGroupInterface> move_group_interface_;

rclcpp::Service<wzlscheduler_interfaces::srv::RobotMoveToPosition>::SharedPtr service_robot_move_toposition_;
rclcpp::Service<wzlscheduler_interfaces::srv::SceneObjectAttach>::SharedPtr service_scene_object_attach;
rclcpp::Service<wzlscheduler_interfaces::srv::SceneObjectDetach>::SharedPtr service_scene_object_detach;

rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectAdd>::SharedPtr subscription_scene_object_add_;
rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectRemove>::SharedPtr subscription_scene_object_remove_;
rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectSetPose>::SharedPtr subscription_scene_object_set_pose_;

class RobotPanda : public rclcpp::Node
{
  public:
    RobotPanda()
      : Node("robot panda", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true))
    {
        // connect the ros services
        service_robot_move_toposition_ = this->create_service<wzlscheduler_interfaces::srv::RobotMoveToPosition>("robot_move_to_position", std::bind(&RobotPanda::service_callback_robot_move_to_position, this, std::placeholders::_1, std::placeholders::_2));
        service_scene_object_attach = this->create_service<wzlscheduler_interfaces::srv::SceneObjectAttach>("service_callback_scene_object_attach", std::bind(&RobotPanda::service_callback_scene_object_attach, this, std::placeholders::_1, std::placeholders::_2));
        service_scene_object_detach = this->create_service<wzlscheduler_interfaces::srv::SceneObjectDetach>("service_callback_scene_object_detach", std::bind(&RobotPanda::service_callback_scene_object_detach, this, std::placeholders::_1, std::placeholders::_2));

        // connect topics
        subscription_scene_object_add_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectAdd>
          ("scene_object_add", 10, std::bind(&RobotPanda::topic_callback_scene_object_add, this, std::placeholders::_1));

        subscription_scene_object_remove_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectRemove>
          ("scene_object_remove", 10, std::bind(&RobotPanda::topic_callback_scene_object_remove, this, std::placeholders::_1));

        subscription_scene_object_set_pose_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectSetPose>
          ("scene_object_set_pose", 10, std::bind(&RobotPanda::topic_callback_scene_object_set_pose, this, std::placeholders::_1));
    }

    void Initialize(std::shared_ptr<RobotPanda> robot)
    {
      // Create the MoveIt MoveGroup Interface
      move_group_interface_ = std::make_shared<MoveGroupInterface>(robot, "panda_arm");
    }

  private:
    void service_callback_scene_object_attach(const std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach::Request> request,
      std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach::Response> response)
    {

    }

    void service_callback_scene_object_detach(const std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectDetach::Request> request,
      std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectDetach::Response> response)
    {

    }


    void service_callback_robot_move_to_position(const std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition::Request> request,
            std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition::Response> response)
    {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request (move to position)\nX: %g" " Y: %g Z: %g RotX: %g RotY %g RotZ %g",
                    request->posx, request->posy, request->posz, request->rotx, request->roty, request->rotz);
      // Set a target Pose
      geometry_msgs::msg::Pose msg;
      msg.orientation.w = 1.0; // todo: set also the orientation
      msg.position.x = request->posx;
      msg.position.y = request->posy;
      msg.position.z = request->posz;
      msg.orientation.x = request->rotx;
      msg.orientation.y = request->roty;
      msg.orientation.z = request->rotz;
      msg.orientation.w = request->;
    
      move_group_interface_->setPoseTarget(msg);

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

    void topic_callback_scene_object_add(const wzlscheduler_interfaces::msg::SceneObjectAdd& msg) const
    {

    }

    void topic_callback_scene_object_remove(const wzlscheduler_interfaces::msg::SceneObjectRemove& msg) const
    {

    }

    void topic_callback_scene_object_set_pose(const wzlscheduler_interfaces::msg::SceneObjectSetPose& msg) const
    {

    }
};


int main(int argc, char * argv[])
{
  // Initialize ROS and create the Node
  rclcpp::init(argc, argv);
  auto const node = std::make_shared<RobotPanda>();
  node->Initialize(node);
  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();
  return 0;
}