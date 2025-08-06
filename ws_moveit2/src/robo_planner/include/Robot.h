#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <memory>
#include <vector>

#include "Pose.h"
#include "Gripper.h"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/client.hpp"
#include "rclcpp/clock.hpp"
#include "wzlscheduler_interfaces/srv/robot_move_to_position.hpp"
#include "wzlscheduler_interfaces/srv/robot_follow_trajectory.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_detach.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_attach.hpp"
#include "wzlscheduler_interfaces/srv/robot_set_velocity.hpp"

namespace WzlPlanner
{
    enum RobotMoveType
    {
        AbsolutePTP = 1,
        RelativePTP = 2,
        AbsoluteCartesian = 3,
        RelativeCartesian = 4
    };

    class Robot
    {
        protected:
            bool isProcessing_;
            std::shared_ptr<GripperBase> gripper_;

        public:
            Robot() {}
            virtual ~Robot() = default;

            bool GetIsProcessing() const { return isProcessing_; }
            
            bool HasGripper() const { return gripper_ != nullptr; }
            std::shared_ptr<GripperBase> GetGripper() const { return gripper_; }
            void SetGripper(const std::shared_ptr<GripperBase> gripper) { gripper_ = gripper; }

            // service calll of a move to pose cmd to the robot backend which then calculates the robot trajectory and send it to the simulated or real robot 
            virtual bool MoveToPose(const std::shared_ptr<Pose> targetPose, const RobotMoveType moveType = AbsolutePTP) = 0;

            // the robot tcp follows a trjaevtory containing a list of fixed points
            virtual bool FollowTrajectory(const std::vector<std::shared_ptr<Pose>> points) = 0;
            
            // attaches a part with the given key in the scene to the robot
            virtual void PartAttach(const std::string partKey) = 0;

            // detaches an attached part from the robot and places it back into the scene 
            virtual void PartDetach(const std::string partKey) = 0;

            // sets the movement velocity 
            virtual void SetVelocity(const double velocity = 1.0, const double acceleration = 1.0, const int type = 0) = 0;
    };

    class RobotDummy : public Robot
    {
        public:
            RobotDummy(const std::shared_ptr<rclcpp::Node> node)
            {
                node_ = node;
                client_ = node_->create_client<wzlscheduler_interfaces::srv::RobotMoveToPosition>("robot_move_to_position");
            }

            bool MoveToPose(const std::shared_ptr<Pose> targetPose, const RobotMoveType moveType = AbsolutePTP) override; 
            bool FollowTrajectory(const std::vector<std::shared_ptr<Pose>> points) override;
            void PartAttach(const std::string partKey) override;
            void PartDetach(const std::string partKey) override;
            void SetVelocity(const double velocity = 1.0, const double acceleration = 1.0, const int type = 0) override;

        private:
            std::shared_ptr<rclcpp::Node> node_;
            rclcpp::Client<wzlscheduler_interfaces::srv::RobotMoveToPosition>::SharedPtr client_;
    };

    class RobotIiwa : public Robot
    {
        public:
            RobotIiwa(const std::shared_ptr<rclcpp::Node> node)
            {
                node_ = node;
                serviceRobotMoveToPosition_ = node_->create_client<wzlscheduler_interfaces::srv::RobotMoveToPosition>("robot_move_to_position");
                serviceRobotFollowTrajectory_ = node_->create_client<wzlscheduler_interfaces::srv::RobotFollowTrajectory>("robot_follow_trajectory");
                serviceRobotSetVelocity_ = node_->create_client<wzlscheduler_interfaces::srv::RobotSetVelocity>("robot_set_velocity");
                serviceSceenObjectAttach_ = node_->create_client<wzlscheduler_interfaces::srv::SceneObjectAttach>("scene_object_attach");
                serviceSceenObjectDetach_ = node_->create_client<wzlscheduler_interfaces::srv::SceneObjectDetach>("scene_object_detach");
            }

            bool MoveToPose(const std::shared_ptr<Pose> targetPose, const RobotMoveType moveType = AbsolutePTP) override; 
            bool FollowTrajectory(const std::vector<std::shared_ptr<Pose>> points) override;
            void PartAttach(const std::string partKey) override;
            void PartDetach(const std::string partKey) override;
            void SetVelocity(const double velocity = 1.0, const double acceleration = 1.0, const int type = 0) override;

        private:
            std::shared_ptr<rclcpp::Node> node_;
            rclcpp::Client<wzlscheduler_interfaces::srv::RobotMoveToPosition>::SharedPtr serviceRobotMoveToPosition_;
            rclcpp::Client<wzlscheduler_interfaces::srv::RobotFollowTrajectory>::SharedPtr serviceRobotFollowTrajectory_;
            rclcpp::Client<wzlscheduler_interfaces::srv::RobotSetVelocity>::SharedPtr serviceRobotSetVelocity_;
            rclcpp::Client<wzlscheduler_interfaces::srv::SceneObjectAttach>::SharedPtr serviceSceenObjectAttach_;
            rclcpp::Client<wzlscheduler_interfaces::srv::SceneObjectDetach>::SharedPtr serviceSceenObjectDetach_;
    };

} // namespace WzlPlanner

#endif // ROBOT_HPP