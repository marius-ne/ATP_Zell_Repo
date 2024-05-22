#ifndef ROSINTERFACE_HPP_
#define ROSINTERFACE_HPP_

#include "wzlscheduler_interfaces/srv/robot_move_to_position.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_attach.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_detach.hpp"

#include "wzlscheduler_interfaces/msg/scene_object_add.hpp"
#include "wzlscheduler_interfaces/msg/scene_object_remove.hpp"
#include "wzlscheduler_interfaces/msg/scene_object_set_pose.hpp"

#include "rclcpp/rclcpp.hpp"
#include "../include/Robot.h"

using namespace std;

class RosInterface : public rclcpp::Node
{
  public:
    RosInterface() 
        : Node("mockup_robot")
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Start mockup robot");

        // connect the ros services

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Register services");
        service_robot_move_toposition_ = this->create_service<wzlscheduler_interfaces::srv::RobotMoveToPosition>("robot_move_to_position", std::bind(&RosInterface::service_callback_robot_move_to_position, this, std::placeholders::_1, std::placeholders::_2));
        service_scene_object_attach = this->create_service<wzlscheduler_interfaces::srv::SceneObjectAttach>("service_callback_scene_object_attach", std::bind(&RosInterface::service_callback_scene_object_attach, this, std::placeholders::_1, std::placeholders::_2));
        service_scene_object_detach = this->create_service<wzlscheduler_interfaces::srv::SceneObjectDetach>("service_callback_scene_object_detach", std::bind(&RosInterface::service_callback_scene_object_detach, this, std::placeholders::_1, std::placeholders::_2));

        // connect topics
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Register topcis");
        subscription_scene_object_add_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectAdd>
          ("scene_object_add", 10, std::bind(&RosInterface::topic_callback_scene_object_add, this, std::placeholders::_1));

        subscription_scene_object_remove_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectRemove>
          ("scene_object_remove", 10, std::bind(&RosInterface::topic_callback_scene_object_remove, this, std::placeholders::_1));

        subscription_scene_object_set_pose_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectSetPose>
          ("scene_object_set_pose", 10, std::bind(&RosInterface::topic_callback_scene_object_set_pose, this, std::placeholders::_1));

          RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Initialization done");
    }

    void service_callback_scene_object_attach(const std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach::Request> request,
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach::Response> response)
    {
        string msg = "_____ Scene Object Attach _____\n";
        msg += "Name: " + request->name + "\n";
        msg += "ParentKey: " + request->parentkey + "\n"; 
        msg += "\n";

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());

        response->result = true;
    }

    void service_callback_scene_object_detach(const std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectDetach::Request> request,
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectDetach::Response> response)
    {
        string msg = "_____ Scene Object Detach _____\n";
        msg += "Name: " + request->name + "\n";
        msg += "\n";

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());

        response->result = true;
    }

    void service_callback_robot_move_to_position(const std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition::Request> request,
            std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition::Response> response)
    {
        string msg = "_____ Robot move to position _____\n";
        msg += "Move Type: " + to_string(request->movetype) + "\n";
        msg += "Position X: " + to_string(request->pose.position.x) + "\n";
        msg += "Position Y: " + to_string(request->pose.position.y) + "\n";
        msg += "Position Z: " + to_string(request->pose.position.z) + "\n";
        msg += "Position RotX: " + to_string(request->pose.orientation.x) + "\n";
        msg += "Position RotY: " + to_string(request->pose.orientation.y) + "\n";
        msg += "Position RotZ: " + to_string(request->pose.orientation.z) + "\n";
        msg += "Position RotW: " + to_string(request->pose.orientation.w) + "\n";
        msg += "\n";

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());

        response->result = true;
    }

    void topic_callback_scene_object_add(const wzlscheduler_interfaces::msg::SceneObjectAdd& request) const
    {
        string msg = "_____ Scene Object Add _____\n";
        msg += "Name: " + request.name + "\n";
        msg += "Collision object key: " + request.collisionobjectkey + "\n";
        msg += "Position X: " + to_string(request.coordinates.position.x) + "\n";
        msg += "Position Y: " + to_string(request.coordinates.position.y) + "\n";
        msg += "Position Z: " + to_string(request.coordinates.position.z) + "\n";
        msg += "Position RotX: " + to_string(request.coordinates.orientation.x) + "\n";
        msg += "Position RotY: " + to_string(request.coordinates.orientation.y) + "\n";
        msg += "Position RotZ: " + to_string(request.coordinates.orientation.z) + "\n";
        msg += "Position RotW: " + to_string(request.coordinates.orientation.w) + "\n";
        
        msg += "\n";

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());
    }

    void topic_callback_scene_object_remove(const wzlscheduler_interfaces::msg::SceneObjectRemove& request) const
    {
        string msg = "_____ Scene Object Remove _____\n";
        msg += "Name: " + request.name + "\n";    
        msg += "\n";

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());
    }

    void topic_callback_scene_object_set_pose(const wzlscheduler_interfaces::msg::SceneObjectSetPose& request) const
    {
        string msg = "_____ Scene Object Set Pose _____\n";
        msg += "Name: " + request.name + "\n";
        msg += "Position X: " + to_string(request.coordinates.position.x) + "\n";
        msg += "Position Y: " + to_string(request.coordinates.position.y) + "\n";
        msg += "Position Z: " + to_string(request.coordinates.position.z) + "\n";
        msg += "Position RotX: " + to_string(request.coordinates.orientation.x) + "\n";
        msg += "Position RotY: " + to_string(request.coordinates.orientation.y) + "\n";
        msg += "Position RotZ: " + to_string(request.coordinates.orientation.z) + "\n";
        msg += "Position RotW: " + to_string(request.coordinates.orientation.w) + "\n";
        
        msg += "\n";

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());
    }
    
    
  private:
    rclcpp::Node::SharedPtr node_;

    rclcpp::Service<wzlscheduler_interfaces::srv::RobotMoveToPosition>::SharedPtr service_robot_move_toposition_;
    rclcpp::Service<wzlscheduler_interfaces::srv::SceneObjectAttach>::SharedPtr service_scene_object_attach;
    rclcpp::Service<wzlscheduler_interfaces::srv::SceneObjectDetach>::SharedPtr service_scene_object_detach;

    rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectAdd>::SharedPtr subscription_scene_object_add_;
    rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectRemove>::SharedPtr subscription_scene_object_remove_;
    rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectSetPose>::SharedPtr subscription_scene_object_set_pose_;
};


int main(int argc, char * argv[])
{
  // Initialize ROS and create the Node
  rclcpp::init(argc, argv);
  auto const node = std::make_shared<RosInterface>();
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Services are ready");
  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();
  return 0;
}

#endif