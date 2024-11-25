#include "../include/Robot.h"
#include "../include/ObjectContainer.h"

#include <chrono>
#include "Robot.h"

using namespace std::chrono_literals;

bool WzlPlanner::RobotUR::MoveToPose(const std::shared_ptr<Pose> targetPose, const RobotMoveType moveType)
{
    auto request = std::make_shared<wzlscheduler_interfaces::srv::RobotMoveToPosition::Request>();

    while (!serviceRobotMoveToPosition_->wait_for_service(1s)) 
    {
        if (!rclcpp::ok()) 
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return false;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    request->movetype = moveType;
    request->pose = targetPose->GetGeometryMsgPoseFromPose();

    auto result = serviceRobotMoveToPosition_->async_send_request(request);

    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node_, result) == rclcpp::FutureReturnCode::SUCCESS)
    {
        auto success = result.get()->result;
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Result of MoveToPose: %d", success);

        return success;
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service RobotMoveToPosition");
        return false;
    }
}

bool WzlPlanner::RobotUR::FollowTrajectory(const std::vector<std::shared_ptr<Pose>> points)
{
    auto request = std::make_shared<wzlscheduler_interfaces::srv::RobotFollowTrajectory::Request>();

    while (!serviceRobotFollowTrajectory_->wait_for_service(1s)) 
    {
        if (!rclcpp::ok()) 
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return false;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    std::vector<geometry_msgs::msg::Pose> msg_poses;

    for (const auto& point : points)
    {
        msg_poses.push_back(point->GetGeometryMsgPoseFromPose());
    }

    request->supportpoints = msg_poses;

    auto result = serviceRobotFollowTrajectory_->async_send_request(request);

    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node_, result) == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Result: %d", result.get()->result);
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service RobotFollowTrajectory");
    }
    
    return true;
}

void WzlPlanner::RobotUR::PartAttach(const std::string partKey)
{
    auto msg = std::string("Trying to attach a part from the scene with the key: ") + partKey;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());

    auto request = std::make_shared<wzlscheduler_interfaces::srv::SceneObjectAttach::Request>();
    request->name = partKey;
    request->parentkey = partKey;

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

void WzlPlanner::RobotUR::PartDetach(const std::string partKey)
{
    auto request = std::make_shared<wzlscheduler_interfaces::srv::SceneObjectDetach::Request>();

    request->name = partKey;

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
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Successfully called service SceneObjectDetach");
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

// type: 0: ompl; 1: pilz industrial planner
void WzlPlanner::RobotUR::SetVelocity(const double velocity, const double acceleration, const int type)
{
    std::string plannerTypeStr = type == 0 ? std::string("ompl") : std::string("Pilz industrial planner");

    auto msg = std::string("Set relative robot velocity to value: ") + std::to_string(velocity)
        + std::string("and acceleration to value: ") + std::to_string(acceleration)
        + std::string("for the planner type: ") + plannerTypeStr;

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());

    auto request = std::make_shared<wzlscheduler_interfaces::srv::RobotSetVelocity::Request>();
    request->velocityscalingfactor = velocity;
    request->accelerationscalingfactor = acceleration;
    request->type = type;

    while (!this->serviceRobotSetVelocity_->wait_for_service(1s)) 
    {
        if (!rclcpp::ok()) 
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return;
        }

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = serviceRobotSetVelocity_->async_send_request(request);

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

bool WzlPlanner::RobotDummy::MoveToPose(const std::shared_ptr<Pose> targetPose, const RobotMoveType moveType)
{
    auto msg = std::string("Move dummy robot to target Pose; ") 
     + std::string(", X:") + std::to_string(targetPose->GetPositionX())
     + std::string(", Y:") + std::to_string(targetPose->GetPositionY())
     + std::string(", Z:") + std::to_string(targetPose->GetPositionZ())
     + std::string(", RotX:") + std::to_string(targetPose->GetRotationX())
     + std::string(", RotY:") + std::to_string(targetPose->GetRotationY())
     + std::string(", RotZ:") + std::to_string(targetPose->GetRotationZ())
     + std::string(", MoveType:") + std::to_string(moveType);
    
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());

    return true;
}

bool WzlPlanner::RobotDummy::FollowTrajectory(const std::vector<std::shared_ptr<Pose>> points)
{
    auto msg = std::string("Follow trajectory of fixed point size: ") + std::to_string(points.size());

    int index = 1;

    for (auto &point : points)
    {
        msg += std::to_string(index) + std::string(": ")
            + std::string(", X:") + std::to_string(point->GetPositionX())
            + std::string(", Y:") + std::to_string(point->GetPositionY())
            + std::string(", Z:") + std::to_string(point->GetPositionZ())
            + std::string(", RotX:") + std::to_string(point->GetRotationX())
            + std::string(", RotY:") + std::to_string(point->GetRotationY())
            + std::string(", RotZ:") + std::to_string(point->GetRotationZ())
            + std::string("\n");
    }

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());

    return true;
}

void WzlPlanner::RobotDummy::PartAttach(const std::string partKey)
{
    auto msg = std::string("Dummy attach part to robot") + partKey;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());
}   

void WzlPlanner::RobotDummy::PartDetach(const std::string partKey)
{
    // trigger ros node to detach the part from the robot
    auto msg = std::string("Dummy detach part from root");
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());
}

void WzlPlanner::RobotDummy::SetVelocity(const double velocity, const double acceleration, const int type)
{
    // set the relative movement velocity [0..1] of the robot
    std::string plannerTypeStr = type == 0 ? std::string("ompl") : std::string("Pilz industrial planner");

    auto msg = std::string("Set relative robot velocity to value: ") + std::to_string(velocity)
        + std::string("and acceleration to value: ") + std::to_string(acceleration)
        + std::string("for the planner type: ") + plannerTypeStr;
        
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());
}
