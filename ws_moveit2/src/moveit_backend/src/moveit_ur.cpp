#include <rclcpp/rclcpp.hpp>
#include "moveit/move_group_interface/move_group_interface.h"
#include "moveit/planning_scene_interface/planning_scene_interface.h"
#include "moveit/planning_scene_monitor/planning_scene_monitor.h"
#include "geometric_shapes/shape_operations.h"
#include "ament_index_cpp/get_package_share_directory.hpp"


#include "wzlscheduler_interfaces/srv/robot_move_to_position.hpp"
#include "wzlscheduler_interfaces/srv/robot_follow_trajectory.hpp"
#include "wzlscheduler_interfaces/srv/robot_set_velocity.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_attach.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_detach.hpp"

#include "wzlscheduler_interfaces/msg/scene_object_add.hpp"
#include "wzlscheduler_interfaces/msg/scene_object_remove.hpp"
#include "wzlscheduler_interfaces/msg/scene_object_set_pose.hpp"

#include <moveit/kinematic_constraints/utils.h>
#include <moveit_msgs/action/move_group_sequence.hpp>
#include <moveit_msgs/msg/motion_sequence_request.hpp>
//#include <iterative_time_parameterization.h>

using moveit_msgs::action::MoveGroupSequence;

static const std::string PLANNING_GROUP = "ur_manipulator";
static const std::string BASE_FRAME = "world";

class RobotUr : public rclcpp::Node
{
    public:
        RobotUr()
        : Node("robot_ur", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true))
        {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize services"));

            // connect the ros services
            service_robot_move_toposition_ = this->create_service<wzlscheduler_interfaces::srv::RobotMoveToPosition>("robot_move_to_position", std::bind(&RobotUr::service_callback_robot_move_to_position, this, std::placeholders::_1, std::placeholders::_2));
            service_robot_follow_trajectory_ = this->create_service<wzlscheduler_interfaces::srv::RobotFollowTrajectory>("robot_follow_trajectory", std::bind(&RobotUr::service_callback_robot_follow_trajectory, this, std::placeholders::_1, std::placeholders::_2));
            service_robot_set_velocity_ = this->create_service<wzlscheduler_interfaces::srv::RobotSetVelocity>("robot_set_velocity", std::bind(&RobotUr::service_callback_robot_set_velocity, this, std::placeholders::_1, std::placeholders::_2));
            service_scene_object_attach = this->create_service<wzlscheduler_interfaces::srv::SceneObjectAttach>("scene_object_attach", std::bind(&RobotUr::service_callback_scene_object_attach, this, std::placeholders::_1, std::placeholders::_2));
            service_scene_object_detach = this->create_service<wzlscheduler_interfaces::srv::SceneObjectDetach>("scene_object_detach", std::bind(&RobotUr::service_callback_scene_object_detach, this, std::placeholders::_1, std::placeholders::_2));

            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize topics"));

            // connect topics
            subscription_scene_object_add_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectAdd>
                ("scene_object_add", 10, std::bind(&RobotUr::topic_callback_scene_object_add, this, std::placeholders::_1));

            subscription_scene_object_remove_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectRemove>
                ("scene_object_remove", 10, std::bind(&RobotUr::topic_callback_scene_object_remove, this, std::placeholders::_1));

            subscription_scene_object_set_pose_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectSetPose>
                ("scene_object_set_pose", 10, std::bind(&RobotUr::topic_callback_scene_object_set_pose, this, std::placeholders::_1));

        }

        void Init(std::shared_ptr<rclcpp::Node> robot)
        {
            // MoveGroupSequence service client
            action_client = rclcpp_action::create_client<moveit_msgs::action::MoveGroupSequence>(robot, "/sequence_move_group");

            // initialize planning interface
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize planning scene interface"));
            this->planning_scene_interface_ = std::make_shared<moveit::planning_interface::PlanningSceneInterface>();

            // Create the MoveIt MoveGroup Interface
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize move group interface"));
            move_group_interface_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(robot, PLANNING_GROUP);

            move_group_interface_->startStateMonitor();

            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize Collision boxes"));
            
            auto size = 1.9;
            auto size05 = size * 0.5;
            auto thickness = 0.04;    

            //WERKSTÜCK BOXEN
            add_hollow_box_collision("BOX1",0.56,0.36,0.125,0.012,-0.55,0.23,0.125/2);
            add_hollow_box_collision("BOX2",0.56,0.36,0.125,0.012,-0.55,-0.23,0.125/2);

            //ZELLE
            add_collision_box("wall1", size, thickness, 1.0, 0, size05, 0.5);
            add_collision_box("wall2", size, thickness, 1.0, 0, -size05, 0.5);
            add_collision_box("wall3", thickness, size, 1.0, size05, 0, 0.5);
            add_collision_box("wall4", thickness, size, 1.0, -size05, 0, 0.5);
            
            add_collision_box("gripper_change_station", 0.7, 0.5, 0.5, 0, -0.7, 0.25);
            add_collision_box("floor", 2, 2, 0.02, 0, 0, -0.01);
            add_collision_box("scan_tower", 0.3, 0.3, 1, +0.65, -0.25, 0.5);
            add_collision_box("scan_tower_sensor", 0.16, 0.15, 0.15, 0.56, -0.265334, 0.73);
            //add_collision_box("ceiling", size, size, 0.1, 0, 0, 1);

            //BEMI BOXEN//
            auto bemi_höhe = 0.235;
            auto bemi_breite = 0.065;
            auto bemi_tiefe = 0.1;
            //BEMI_1
            auto bemi_1_x = 0.375;
            auto bemi_1_y = 0.51;
            add_collision_box("BEMI_1_1",bemi_tiefe,bemi_breite,bemi_höhe,bemi_1_x,bemi_1_y,bemi_höhe/2);
            add_collision_box("BEMI_1_2",bemi_tiefe,bemi_breite,bemi_höhe,bemi_1_x+0.03,bemi_1_y+0.26,bemi_höhe/2);
            //BEMI_2
            auto bemi_2_x = 0.109;
            auto bemi_2_y = 0.443;
            add_collision_box("BEMI_2_1",bemi_tiefe,bemi_breite,bemi_höhe,bemi_2_x,bemi_2_y,bemi_höhe/2);
            add_collision_box("BEMI_2_2",bemi_breite,bemi_tiefe,bemi_höhe,bemi_2_x-0.08,bemi_2_y+0.215,bemi_höhe/2);
            //BEMI_3
            auto bemi_3_x = 0.53;
            auto bemi_3_y = 0.258;
            add_collision_box("BEMI_3_1",bemi_breite,bemi_tiefe,bemi_höhe,bemi_3_x,bemi_3_y,bemi_höhe/2);
            add_collision_box("BEMI_3_2",bemi_breite,bemi_tiefe,bemi_höhe,bemi_3_x+0.26,bemi_3_y+0.02,bemi_höhe/2);
            add_collision_box("BEMI_3_3",bemi_tiefe,bemi_breite,bemi_höhe,bemi_3_x+0.075,bemi_3_y-0.215,bemi_höhe/2);

            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialization done"));
        }

    private:

        void add_composite_spindel(const std::string name, const geometry_msgs::msg::Pose& pose)
        {
            moveit_msgs::msg::CollisionObject collision_object;
            collision_object.header.frame_id = move_group_interface_->getPlanningFrame();
            collision_object.id = name;

            // Define both parts
            std::vector<shape_msgs::msg::SolidPrimitive> primitives;
            std::vector<geometry_msgs::msg::Pose> poses;

            // Upper cylinder part
            shape_msgs::msg::SolidPrimitive upper;
            upper.type = upper.CYLINDER;
            upper.dimensions.resize(2);
            upper.dimensions[0] = 0.22;  // Length
            upper.dimensions[1] = 0.045; // Radius
            primitives.push_back(upper);

            geometry_msgs::msg::Pose upper_pose = pose;
            upper_pose.position.z -= 0.1102; // Offset down from the top
            poses.push_back(upper_pose);

            // Lower cylinder part  
            shape_msgs::msg::SolidPrimitive lower;
            lower.type = lower.CYLINDER;
            lower.dimensions.resize(2);
            lower.dimensions[0] = 0.10;  // Length
            lower.dimensions[1] = 0.014; // Radius
            primitives.push_back(lower);

            geometry_msgs::msg::Pose lower_pose = pose;
            lower_pose.position.z -= 0.2704; // Offset further down from the top
            poses.push_back(lower_pose);

            // Add both parts to collision object
            collision_object.primitives = primitives;
            collision_object.primitive_poses = poses;
            collision_object.operation = collision_object.ADD;

            planning_scene_interface_->applyCollisionObject(collision_object);
        }

        void add_gripper(const std::string name, const geometry_msgs::msg::Pose& pose)
        {
            // add a cylinder with dimensions radius 0.055 length 0.19
            moveit_msgs::msg::CollisionObject collision_object;
            collision_object.header.frame_id = move_group_interface_->getPlanningFrame();
            collision_object.id = name;

            shape_msgs::msg::SolidPrimitive primitive;
            primitive.type = primitive.CYLINDER;
            primitive.dimensions.resize(2);
            primitive.dimensions[0] = 0.19; // Length
            primitive.dimensions[1] = 0.055; // Radius

            // Offset the position down by half the length to place top at pose
            geometry_msgs::msg::Pose adjusted_pose = pose;
            adjusted_pose.position.z -= primitive.dimensions[0] / 2.0;

            collision_object.primitives.push_back(primitive);
            collision_object.primitive_poses.push_back(adjusted_pose);
            collision_object.operation = collision_object.ADD;

            planning_scene_interface_->applyCollisionObject(collision_object);
        }

        void add_small_gripper(const std::string name, const geometry_msgs::msg::Pose& pose)
        {
            // add a cylinder with dimensions radius 0.055 length 0.19
            moveit_msgs::msg::CollisionObject collision_object;
            collision_object.header.frame_id = move_group_interface_->getPlanningFrame();
            collision_object.id = name;

            shape_msgs::msg::SolidPrimitive primitive;
            primitive.type = primitive.CYLINDER;
            primitive.dimensions.resize(2);
            primitive.dimensions[0] = 0.18; // Length
            primitive.dimensions[1] = 0.035; // Radius

            // Offset the position down by half the length to place top at pose
            geometry_msgs::msg::Pose adjusted_pose = pose;
            adjusted_pose.position.z -= primitive.dimensions[0] / 2.0;

            collision_object.primitives.push_back(primitive);
            collision_object.primitive_poses.push_back(adjusted_pose);
            collision_object.operation = collision_object.ADD;

            planning_scene_interface_->applyCollisionObject(collision_object);
        }
        
        void add_hollow_box_collision(const std::string name, const float width, const float depth, const float height,
            const float wall_thickness, const float x, const float y, const float z)
        {
            // Collision object initialization
            moveit_msgs::msg::CollisionObject collision_object;
            collision_object.header.frame_id = this->move_group_interface_->getPlanningFrame();
            collision_object.id = name;

            shape_msgs::msg::SolidPrimitive primitive;
            primitive.type = primitive.BOX;
            primitive.dimensions.resize(3);

            geometry_msgs::msg::Pose box_pose;
            box_pose.orientation.w = 1.0;

            // Create and add the four walls of the hollow box

            // Wall 1 (front)
            primitive.dimensions[primitive.BOX_X] = width;
            primitive.dimensions[primitive.BOX_Y] = wall_thickness;
            primitive.dimensions[primitive.BOX_Z] = height;

            box_pose.position.x = x;
            box_pose.position.y = y + (depth / 2) - (wall_thickness / 2);
            box_pose.position.z = z;

            collision_object.primitives.push_back(primitive);
            collision_object.primitive_poses.push_back(box_pose);

            // Wall 2 (back)
            box_pose.position.y = y - (depth / 2) + (wall_thickness / 2);

            collision_object.primitives.push_back(primitive);
            collision_object.primitive_poses.push_back(box_pose);

            // Wall 3 (left)
            primitive.dimensions[primitive.BOX_X] = wall_thickness;
            primitive.dimensions[primitive.BOX_Y] = depth;
            primitive.dimensions[primitive.BOX_Z] = height;

            box_pose.position.x = x - (width / 2) + (wall_thickness / 2);
            box_pose.position.y = y;

            collision_object.primitives.push_back(primitive);
            collision_object.primitive_poses.push_back(box_pose);

            // Wall 4 (right)
            box_pose.position.x = x + (width / 2) - (wall_thickness / 2);

            collision_object.primitives.push_back(primitive);
            collision_object.primitive_poses.push_back(box_pose);

            // Apply the collision object
            collision_object.operation = collision_object.ADD;
            this->planning_scene_interface_->applyCollisionObject(collision_object);
        }

        void add_collision_box(const std::string name, const float width, const float depth, const float height,
            const float x, const float y, const float z)
            {
                moveit_msgs::msg::CollisionObject collision_object;
                collision_object.header.frame_id = this->move_group_interface_->getPlanningFrame();
                collision_object.id = name;
                shape_msgs::msg::SolidPrimitive primitive;

                primitive.type = primitive.BOX;
                primitive.dimensions.resize(3);
                primitive.dimensions[primitive.BOX_X] = width;
                primitive.dimensions[primitive.BOX_Y] = depth;
                primitive.dimensions[primitive.BOX_Z] = height;

                // Define the pose of the box (relative to the frame_id)
                geometry_msgs::msg::Pose box_pose;
                box_pose.orientation.w = 1.0;
                box_pose.position.x = x;
                box_pose.position.y = y;
                box_pose.position.z = z;

                collision_object.primitives.push_back(primitive);
                collision_object.primitive_poses.push_back(box_pose);
                collision_object.operation = collision_object.ADD;
                
                this->planning_scene_interface_->applyCollisionObject(collision_object);
            
        }

        void add_collision_box(const std::string name, const float width, const float depth, const float height, const geometry_msgs::msg::Pose& pose)
            {
                moveit_msgs::msg::CollisionObject collision_object;
                collision_object.header.frame_id = this->move_group_interface_->getPlanningFrame();
                collision_object.id = name;
                shape_msgs::msg::SolidPrimitive primitive;

                primitive.type = primitive.BOX;
                primitive.dimensions.resize(3);
                primitive.dimensions[primitive.BOX_X] = width;
                primitive.dimensions[primitive.BOX_Y] = depth;
                primitive.dimensions[primitive.BOX_Z] = height;

                collision_object.primitives.push_back(primitive);
                collision_object.primitive_poses.push_back(pose);
                collision_object.operation = collision_object.ADD;

                this->planning_scene_interface_->applyCollisionObject(collision_object);
            
        }

        void remove_collision_object(const std::string& objectId) const
        {
            // Contruct the collision object
            moveit_msgs::msg::CollisionObject collision_object;
            collision_object.id = objectId;
            collision_object.operation = collision_object.REMOVE; 

            // Remove collision object to planning scene interface -> planningSceneInterface reference will be changed
            planning_scene_interface_->applyCollisionObject(collision_object);

            // Create a ROS logger
            const rclcpp::Logger logger = rclcpp::get_logger("rclcpp");
            RCLCPP_INFO(logger, ("Collision mesh: " + objectId + " removed from scene!").c_str());
        }
        
        // void set_execute_duration_for_trajectory(moveit_msgs::msg::RobotTrajectory& input_trajectory, double execute_duration)
        // {
        //     std::vector<trajectory_msgs::msg::JointTrajectoryPoint>& joint_trajectories = input_trajectory.joint_trajectory.points;
        //     size_t size = joint_trajectories.size();
        //     execute_duration = execute_duration/size;
        //     for (int i=0; i<size; i++)
        //     {
        //         builtin_interfaces::msg::Duration duration = builtin_interfaces::msg::Duration();
        //         duration.set__sec(execute_duration * i);
        //         joint_trajectories[i].time_from_start = duration;
        //     }
        // }

        void service_callback_robot_move_to_position(const std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition::Request> request,
            std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition::Response> response)
        {
            auto position = request->pose.position;
            auto orientation = request->pose.orientation;
            auto moveType = request->movetype;

            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request (move to position)\nX: %g Y: %g Z: %g RotX: %g RotY %g RotZ %g RotW %g",
                            position.x, position.y, position.z, orientation.x, orientation.y, orientation.z, orientation.w);
            
            // Set a target Pose
            geometry_msgs::msg::Pose msg;
            msg.position = position;
            msg.orientation = orientation;

            auto is_movement_normal = moveType == 1 || moveType == 2;
            auto is_movement_cartesian = moveType == 3 || moveType == 4;
        
            
            moveit_msgs::msg::RobotTrajectory trajectory;
            
            if (is_movement_normal)
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Set pipeline to ompl");
                move_group_interface_->setPlanningPipelineId("ompl");
                move_group_interface_->setPlannerId("RRTConnectkConfigDefault");
                //move_group_interface_->setPlannerId("PersistentPRMstar");

                move_group_interface_->setMaxVelocityScalingFactor(scaling_velocity_ompl);
                move_group_interface_->setMaxAccelerationScalingFactor(scaling_acceleration_ompl);

                move_group_interface_->setNumPlanningAttempts(3);
                move_group_interface_->setPlanningTime(2.0);
            }
            else if (is_movement_cartesian)
            {
                remove_collision_object("gripper_change_station");
                remove_collision_object("floor");

                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Set pipeline to pilz industrial planner");
                move_group_interface_->setPlanningPipelineId("pilz_industrial_motion_planner");
                move_group_interface_->setPlannerId("LIN");

                move_group_interface_->setMaxVelocityScalingFactor(scaling_velocity_pilz);
                move_group_interface_->setMaxAccelerationScalingFactor(scaling_acceleration_pilz);
                move_group_interface_->setNumPlanningAttempts(1);
                move_group_interface_->setPlanningTime(1.0);
            }

            if (moveType == 1) // absolute pose
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "MoveType: Absolute pose normal movement");
                move_group_interface_->setPoseTarget(msg);
                last_pose_ = msg;
            }
            else if (moveType == 2) // relative pose
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "MoveType: Relative pose normal movement");
                geometry_msgs::msg::Pose target_pose = move_group_interface_->getCurrentPose().pose;
                target_pose.position.x += position.x;
                target_pose.position.y += position.y;
                target_pose.position.z += position.z; 

                msg.position = target_pose.position;

                move_group_interface_->setPoseTarget(msg);
                last_pose_ = target_pose;
            }
            else if (moveType == 3) // absolute pose cartesian movement
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "MoveType: Absolute pose cartesian movement");
                
                move_group_interface_->setPoseTarget(msg);
                last_pose_ = msg;
            }
            else if (moveType == 4) // relative pose cartesian movement
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "MoveType: Relative pose cartesian movement");
                const moveit::core::JointModelGroup* joint_model_group = move_group_interface_->getCurrentState()->getJointModelGroup(PLANNING_GROUP);
                
                moveit::core::RobotStatePtr current_state = move_group_interface_->getCurrentState(10);
                
                std::vector<double> joint_group_positions;
                current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
        
                move_group_interface_->setStartStateToCurrentState();

                std::vector<geometry_msgs::msg::Pose> waypoints;

                waypoints.push_back(move_group_interface_->getCurrentPose().pose);
                geometry_msgs::msg::Pose target_pose = move_group_interface_->getCurrentPose().pose;
                target_pose.position.x += position.x;
                target_pose.position.y += position.y;
                target_pose.position.z += position.z;
                waypoints.push_back(target_pose);  

                move_group_interface_->computeCartesianPath(waypoints, 0.01, 0, trajectory, false);

                last_pose_ = target_pose;

                move_group_interface_->setPlannerId("LIN");
            }

            if (is_movement_normal )
            {
                moveit::planning_interface::MoveGroupInterface::Plan msg2;
                auto const success = static_cast<bool>(move_group_interface_->plan(msg2));
                
                // Execute the plan
                if(success) 
                {
                    if (!move_group_interface_->execute(msg2))
                    {
                        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "OMPL Planner - Execution failed!");
                        response->result = false;
                    }
                    else
                    {
                        response->result = true;
                    }
                
                } else {
                    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "OMPL Planner - Planning failed!");
                    response->result = false;
                }
            }
            else if (is_movement_cartesian)
            {
                //auto const success = static_cast<bool>(move_group_interface_->execute(trajectory));
    
                //response->result = true;

                moveit::planning_interface::MoveGroupInterface::Plan msg2;
                auto const success = static_cast<bool>(move_group_interface_->plan(msg2));
                
                // Execute the plan
                if(success) 
                {
                    if (!move_group_interface_->execute(msg2))
                    {
                        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "PILZ planner - Execution failed!");
                        response->result = false;
                    }
                    else
                    {
                        response->result = true;
                    }
                } else {
                    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "PILZ planner - Planning failed!");
                    response->result = false;
                }

                add_collision_box("gripper_change_station", 0.7, 0.5, 0.5, 0, -0.7, 0.25);
                add_collision_box("floor", 2, 2, 0.02, 0, 0, -0.011);
            }
            else
            {
                response->result = false;
            }
        }

        void service_callback_robot_follow_trajectory(const std::shared_ptr<wzlscheduler_interfaces::srv::RobotFollowTrajectory::Request> request,
            std::shared_ptr<wzlscheduler_interfaces::srv::RobotFollowTrajectory::Response> response)
        {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming Trajectory request");

            std::promise<bool> action_completed;
            std::future<bool> action_completed_future = action_completed.get_future();

            moveit_msgs::msg::MotionSequenceRequest sequence_request;  

            geometry_msgs::msg::PoseStamped pose;
            pose.header.frame_id = BASE_FRAME;
            pose.header.stamp = this->now();
            
            moveit_msgs::msg::MotionSequenceItem item;
            item.blend_radius = 0.0;
            item.req.group_name = PLANNING_GROUP;
            item.req.pipeline_id = "pilz_industrial_motion_planner";
            item.req.planner_id = "LIN";
            item.req.allowed_planning_time = 2.0;
            item.req.max_acceleration_scaling_factor = scaling_acceleration_pilz;
            item.req.max_velocity_scaling_factor = scaling_velocity_pilz;

            for (const auto& point : request->supportpoints)
            {
                pose.pose.position = point.position;
                pose.pose.orientation = point.orientation;
                
                item.req.goal_constraints = {kinematic_constraints::constructGoalConstraints("wrist_3_link", pose)};
                sequence_request.items.push_back(item);
            }

            sequence_request.items.back().blend_radius = 0.0;

            auto goal_msg = moveit_msgs::action::MoveGroupSequence::Goal();
            goal_msg.request = sequence_request;

            goal_msg.planning_options.planning_scene_diff.is_diff = true;
            goal_msg.planning_options.planning_scene_diff.robot_state.is_diff = true;

            auto send_goal_options = rclcpp_action::Client<moveit_msgs::action::MoveGroupSequence>::SendGoalOptions();
            send_goal_options.goal_response_callback = [](std::shared_ptr<rclcpp_action::ClientGoalHandle<moveit_msgs::action::MoveGroupSequence>> goal_handle) {
                if (!goal_handle) {
                    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Goal was rejected by server");
                } else {
                    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Goal accepted by server, waiting for result");
                }
            };
            send_goal_options.result_callback = [&action_completed](const rclcpp_action::ClientGoalHandle<moveit_msgs::action::MoveGroupSequence>::WrappedResult& result) {
                switch (result.code) {
                    case rclcpp_action::ResultCode::SUCCEEDED:
                        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Goal succeeded");
                        action_completed.set_value(true);
                        break;
                    case rclcpp_action::ResultCode::ABORTED:
                        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Goal was aborted. Status: %d", result.result->response.error_code.val);
                        action_completed.set_value(false);
                        break;
                    case rclcpp_action::ResultCode::CANCELED:
                        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Goal was canceled");
                        action_completed.set_value(false);
                        break;
                    default:
                        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Unknown result code");
                        action_completed.set_value(false);
                        break;
                }
            };

            auto goal_handle_future = action_client->async_send_goal(goal_msg, send_goal_options);
            if (!goal_handle_future.get()) {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Goal was rejected by server");
                response->result = false;
                return;
            }

            // Wait for the action to complete and get the result
            if (action_completed_future.wait_for(std::chrono::seconds(60)) == std::future_status::timeout) {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Action timed out");
                response->result = false;
                return;
            }

            response->result = action_completed_future.get();
        }

        void service_callback_robot_set_velocity(const std::shared_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity::Request> request,
            std::shared_ptr<wzlscheduler_interfaces::srv::RobotSetVelocity::Response> response)
        {
            auto movementType = request->type;
            auto scalingVelocity = request->velocityscalingfactor;
            auto scalingAcceleration = request->accelerationscalingfactor;

            if (movementType == 0)
            {
                // ompl
                scaling_velocity_ompl = scalingVelocity;
                scaling_acceleration_ompl = scalingAcceleration;
            }
            else if (movementType == 1)
            {
                scaling_velocity_pilz = scalingVelocity;
                scaling_acceleration_pilz = scalingAcceleration;
            }
            
            response->result = true;
        }

        void service_callback_scene_object_attach(const std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach::Request> request,
            std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach::Response> response)
        {
            auto pose = move_group_interface_->getCurrentPose().pose;
            auto name = request->name;

            if (name == "spindel")
            {
                add_composite_spindel(name, pose);

                if (!move_group_interface_->attachObject(name))
                {
                    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Attach object '%s' failed", name.c_str());
                    response->result = 0;
                    return;
                }
                response->result = 1;
            } else if (name == "gripper")
            {
                add_gripper(name, pose);
            
                if (!move_group_interface_->attachObject(name))
                {
                    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Attach object '%s' failed", name.c_str());
                    response->result = 0;
                    return;
                }
                response->result = 1;
            } else if (name == "small_gripper")
            {
                add_small_gripper(name, pose);

                if (!move_group_interface_->attachObject(name))
                {
                    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Attach object '%s' failed", name.c_str());
                    response->result = 0;
                    return;
                }
                response->result = 1;
            } else {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Object '%s' not defined", name.c_str());
                response->result = 0;
            }

        }

        void service_callback_scene_object_detach(const std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectDetach::Request> request,
            std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectDetach::Response> response)
        {
            auto name = request->name;
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Attempting to detach object '%s'", name.c_str());

            if (name == "spindel" || name == "gripper" || name == "small_gripper")
            {
                if (!move_group_interface_->detachObject(name))
                {
                    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Detach object '%s' failed", name.c_str());
                    response->result = 0;
                    return;
                }
                
                std::this_thread::sleep_for(std::chrono::milliseconds(200));

                remove_collision_object(name);
                response->result = 1;
            }
            else
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Object '%s' not recognized", name.c_str());
                response->result = 0;
            }
        }

        // Callback method for constructing a mesh collision object and addding it to the planning scene interface
        // the path of the mesh is defined in the config file in the resource folder of the package
        void topic_callback_scene_object_add(const wzlscheduler_interfaces::msg::SceneObjectAdd& msg) const
        {
            /*
            // Get the planning frame
            std::string frame_id = move_group_interface_->getPlanningFrame();

            // Create a CollisionObject
            moveit_msgs::msg::CollisionObject collision_object;
            collision_object.header.frame_id = frame_id;
            std::string objectName = msg.name;
            collision_object.id = objectName;

            // Get the path to the config file in the package directory
            std::string package_path = ament_index_cpp::get_package_share_directory("ur16e");
            std::string configPath = package_path + "/config/mesh_config.csv";

            // Retrieve the path to the mesh from the config fill
            std::string filePath = std::make_shared<FileLoader>()->get_object_path(objectName, configPath);

            // Create a mesh from the specified path from the config file
            shapes::Mesh * original_mesh = shapes::createMeshFromResource(filePath);

            // Create a scaled copy of the original mesh with padding (scale factor extracted from the LoadObject message)
            shapes::Mesh * scaled_mesh = new shapes::Mesh(*original_mesh);
            //scaled_mesh->scaleAndPadd(msg.scale, 0.0);  
            scaled_mesh->scaleAndPadd(1, 0.0);  
            
            // Convert the scaled mesh to shape_msgs::Mesh
            shape_msgs::msg::Mesh shelf_mesh;
            shapes::ShapeMsg shelf_mesh_msg;
            shapes::constructMsgFromShape(scaled_mesh, shelf_mesh_msg);
            shelf_mesh = boost::get<shape_msgs::msg::Mesh>(shelf_mesh_msg);

            // Convert the coordinates from the LoadObject message to a geometry_msgs::Pose
            geometry_msgs::msg::Pose meshPose;
            meshPose.position = msg.coordinates.position;
            meshPose.orientation = msg.coordinates.orientation;

            // Add the mesh and pose to the CollisionObject
            collision_object.meshes.push_back(shelf_mesh);
            collision_object.mesh_poses.push_back(meshPose);
            collision_object.operation = collision_object.ADD;

            // Add collision object to planning scene interface -> planningSceneInterface reference will be changed
            planning_scene_interface_.applyCollisionObject(collision_object);

            // Create a ROS logger
            const rclcpp::Logger logger = rclcpp::get_logger("addMeshCollisionObject_rclcpp::get_logger("rclcpp")");
            RCLCPP_INFO(logger, ("Collision mesh: " + objectName + " added to scene!").c_str());

            // Clean up the memory allocated for the scaled mesh
            delete scaled_mesh;
            */
        }

        void topic_callback_scene_object_remove(const wzlscheduler_interfaces::msg::SceneObjectRemove& msg) const
        {
            // Convert the message to a string
            std::string objectId = msg.name;

            remove_collision_object(objectId);
        }

        void topic_callback_scene_object_set_pose(const wzlscheduler_interfaces::msg::SceneObjectSetPose& msg) const
        {
        }

        geometry_msgs::msg::Pose last_pose_;

        // Default speed values
        double scaling_velocity_ompl = 0.2;
        double scaling_acceleration_ompl = 0.2;
        double scaling_velocity_pilz = 0.03;
        double scaling_acceleration_pilz = 0.03;

        std::shared_ptr<moveit::planning_interface::MoveGroupInterface> move_group_interface_;
        std::shared_ptr<moveit::planning_interface::PlanningSceneInterface> planning_scene_interface_;

        rclcpp::Service<wzlscheduler_interfaces::srv::RobotMoveToPosition>::SharedPtr service_robot_move_toposition_;
        rclcpp::Service<wzlscheduler_interfaces::srv::RobotFollowTrajectory>::SharedPtr service_robot_follow_trajectory_;
        rclcpp::Service<wzlscheduler_interfaces::srv::RobotSetVelocity>::SharedPtr service_robot_set_velocity_;
        rclcpp::Service<wzlscheduler_interfaces::srv::SceneObjectAttach>::SharedPtr service_scene_object_attach;
        rclcpp::Service<wzlscheduler_interfaces::srv::SceneObjectDetach>::SharedPtr service_scene_object_detach;

        rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectAdd>::SharedPtr subscription_scene_object_add_;
        rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectRemove>::SharedPtr subscription_scene_object_remove_;
        rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectSetPose>::SharedPtr subscription_scene_object_set_pose_;
        rclcpp_action::Client<moveit_msgs::action::MoveGroupSequence>::SharedPtr action_client;
};

int main(int argc, char * argv[])
{
  std::cout << "Run node moveit backend" << std::endl;

    // Initialize ROS and create the Node
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize robot"));

    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    auto const node = std::make_shared<RobotUr>();

    auto const node_move_group = std::make_shared<rclcpp::Node>("move_group_node");

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("spin node"));

    rclcpp::executors::SingleThreadedExecutor executor;
    //executor.add_node(node);
    executor.add_node(node_move_group);
    auto spinner = std::thread([&executor]() { executor.spin(); });

    node->Init(node_move_group);

    // Spin node
    rclcpp::spin(node);

    // Shutdown ROS
    spinner.join();
    rclcpp::shutdown();

    return 0;
}