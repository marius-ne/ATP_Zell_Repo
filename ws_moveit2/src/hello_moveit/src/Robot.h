#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <memory>

#include "Pose.h"
#include "rclcpp/rclcpp.hpp"
#include "wzlscheduler_interfaces/srv/robot_move_to_position.hpp"

namespace WzlPlanner
{
    class Robot
    {
        protected:
            bool isProcessing_;

        public:
            Robot() {}

            bool GetIsProcessing() const { return isProcessing_; }

            virtual bool MoveToPose(std::shared_ptr<WzlPlanner::Pose> targetPose) = 0;
    };

    class RobotDummy : public Robot
    {
        public:
            RobotDummy(const std::shared_ptr<rclcpp::Node> node)
            {
                node_ = node;
                client_ = node_->create_client<wzlscheduler_interfaces::srv::RobotMoveToPosition>("robot_move_to_position");
            }

            bool MoveToPose(std::shared_ptr<WzlPlanner::Pose> targetPose) override; 

        private:
            std::shared_ptr<rclcpp::Node> node_;
            rclcpp::Client<wzlscheduler_interfaces::srv::RobotMoveToPosition>::SharedPtr client_;
    };

    class RobotUR : public Robot
    {
        public:
            RobotUR(const std::shared_ptr<rclcpp::Node> node)
            {
                node_ = node;
                client_ = node_->create_client<wzlscheduler_interfaces::srv::RobotMoveToPosition>("robot_move_to_position");
            }

            bool MoveToPose(std::shared_ptr<WzlPlanner::Pose> targetPose) override; 

        private:
            std::shared_ptr<rclcpp::Node> node_;
            rclcpp::Client<wzlscheduler_interfaces::srv::RobotMoveToPosition>::SharedPtr client_;
    };

} // namespace WzlPlanner

#endif // ROBOT_HPP