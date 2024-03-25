#include "Robot.h"

#include <chrono>

using namespace std::chrono_literals;

bool WzlPlanner::RobotUR::MoveToPose(std::shared_ptr<WzlPlanner::Pose> targetPose)
{
    auto request = std::make_shared<wzlscheduler_interfaces::srv::RobotMoveToPosition::Request>();
    request->posx = targetPose->GetPositionX();
    request->posy = targetPose->GetPositionY();
    request->posz = targetPose->GetPositionZ();
    request->rotx = targetPose->GetRotationX();
    request->roty = targetPose->GetRotationY();
    request->rotz = targetPose->GetRotationZ();

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

bool WzlPlanner::RobotDummy::MoveToPose(std::shared_ptr<WzlPlanner::Pose> targetPose)
{
    auto request = std::make_shared<wzlscheduler_interfaces::srv::RobotMoveToPosition::Request>();
    request->posx = targetPose->GetPositionX();
    request->posy = targetPose->GetPositionY();
    request->posz = targetPose->GetPositionZ();
    request->rotx = targetPose->GetRotationX();
    request->roty = targetPose->GetRotationY();
    request->rotz = targetPose->GetRotationZ();

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
