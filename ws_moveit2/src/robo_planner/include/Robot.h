#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <memory>

#include "Pose.h"
#include "Gripper.h"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/client.hpp"
#include "rclcpp/clock.hpp"
#include "wzlscheduler_interfaces/srv/robot_move_to_position.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_detach.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_attach.hpp"

namespace WzlPlanner
{
    class Robot
    {
        protected:
            bool isProcessing_;
            std::shared_ptr<GripperBase> gripper_;

        public:
            Robot() {}

            bool GetIsProcessing() const { return isProcessing_; }
            
            bool HasGripper() const { return gripper_ != nullptr; }
            std::shared_ptr<GripperBase> GetGripper() const { return gripper_; }
            void SetGripper(const std::shared_ptr<GripperBase> gripper) { gripper_ = gripper; }

            virtual bool MoveToPose(Pose::ConstSharedPtr targetPose) = 0;
            
            // attaches a part with the given key in the scene to the robot
            virtual void PartAttach(const std::string partKey) = 0;

            // detaches an attached part from the robot and places it back into the scene 
            virtual void PartDetach() = 0;
    };

    class RobotDummy : public Robot
    {
        public:
            RobotDummy(const std::shared_ptr<rclcpp::Node> node)
            {
                node_ = node;
                client_ = node_->create_client<wzlscheduler_interfaces::srv::RobotMoveToPosition>("robot_move_to_position");
            }

            bool MoveToPose(Pose::ConstSharedPtr targetPose) override; 
            void PartAttach(const std::string partKey) override;
            void PartDetach() override;

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
                serviceSceenObjectAttach_ = node_->create_client<wzlscheduler_interfaces::srv::SceneObjectAttach>("scene_object_attach");
                serviceSceenObjectDetach_ = node_->create_client<wzlscheduler_interfaces::srv::SceneObjectDetach>("scene_object_detach");
            }

            bool MoveToPose(Pose::ConstSharedPtr targetPose) override; 
            void PartAttach(const std::string partKey) override;
            void PartDetach() override;

        private:
            std::shared_ptr<rclcpp::Node> node_;
            rclcpp::Client<wzlscheduler_interfaces::srv::RobotMoveToPosition>::SharedPtr client_;
            rclcpp::Client<wzlscheduler_interfaces::srv::SceneObjectAttach>::SharedPtr serviceSceenObjectAttach_;
            rclcpp::Client<wzlscheduler_interfaces::srv::SceneObjectDetach>::SharedPtr serviceSceenObjectDetach_;
    };

} // namespace WzlPlanner

#endif // ROBOT_HPP