#include "../include/Robot.h"
#include "../include/ObjectContainer.h"

#include <chrono>
#include "Robot.h"

using namespace std::chrono_literals;

bool WzlPlanner::RobotUR::MoveToPose(std::shared_ptr<Pose> targetPose)
{
    auto request = std::make_shared<wzlscheduler_interfaces::srv::RobotMoveToPosition::Request>();

    while (!client_->wait_for_service(1s)) 
    {
        if (!rclcpp::ok()) 
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return false;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = client_->async_send_request(request);

    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node_, result) == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Result: %d", result.get()->result);
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service set_value_io_interface");
    }

    return result.get()->result;
}

void WzlPlanner::RobotUR::PartAttach(const std::string partKey)
{
    auto msg = std::string("Trying to attach a part from the scene with the key: ") + partKey;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());

    auto request = std::make_shared<wzlscheduler_interfaces::srv::SceneObjectAttach::Request>();

    while (!this->serviceSceenObjectAttach_->wait_for_service(1s)) 
    {
        if (!rclcpp::ok()) 
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return;
        }

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = serviceSceenObjectAttach_->async_send_request(request);

    // Wait for the result.
    if (rclcpp::spin_until_future_complete(ObjectContainer::Get()->GetNode(), result) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        auto output = result.get()->result;

        if (output == 1)
        {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Successfully called service SceneObjectAttach");
        }
        else
        {
            std::string msg = "Error in call service SceneObjectAttach: " + std::to_string(output);
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), msg.c_str());
        }
    } 
    else 
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service SceneObjectDetach");
    }
}

void WzlPlanner::RobotUR::PartDetach()
{
    auto request = std::make_shared<wzlscheduler_interfaces::srv::SceneObjectDetach::Request>();

    while (!this->serviceSceenObjectDetach_->wait_for_service(1s)) 
    {
        if (!rclcpp::ok()) 
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return;
        }

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = serviceSceenObjectDetach_->async_send_request(request);

    // Wait for the result.
    if (rclcpp::spin_until_future_complete(ObjectContainer::Get()->GetNode(), result) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        auto output = result.get()->result;

        if (output == 1)
        {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Successfully calles service SceneObjectDetach");

            auto coordinates = result.get()->coordinates;
            auto partName = result.get()->name;
            auto part = ObjectContainer::Get()->GetScene()->GetSceneObject(partName);

            ObjectContainer::Get()->GetScene()->SceneObjectSetPositionAbsolute(part, std::make_shared<WzlPlanner::Pose>(coordinates));
        }
        else
        {
            std::string msg = "Error in call service SceneObjectDetach: " + std::to_string(output);
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), msg.c_str());
        }
    } 
    else 
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service SceneObjectDetach");
    }
}

bool WzlPlanner::RobotDummy::MoveToPose(std::shared_ptr<Pose>  targetPose)
{
    auto msg = std::string("Move dummy robot to target Pose; X:") + std::to_string(targetPose->GetPositionX())
     + std::string(", Y:") + std::to_string(targetPose->GetPositionY())
     + std::string(", Z:") + std::to_string(targetPose->GetPositionZ())
     + std::string(", RotX:") + std::to_string(targetPose->GetRotationX())
     + std::string(", RotY:") + std::to_string(targetPose->GetRotationY())
     + std::string(", RotZ:") + std::to_string(targetPose->GetRotationZ());
    
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());

    return true;
}

void WzlPlanner::RobotDummy::PartAttach(const std::string partKey)
{
    auto msg = std::string("Dummy attach part to robot") + partKey;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());
}   

void WzlPlanner::RobotDummy::PartDetach()
{
    // trigger ros node to detah the part from the robot
    auto msg = std::string("Dummy detach part from root");
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());
}
