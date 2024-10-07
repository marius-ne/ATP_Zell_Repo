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

//#include <iterative_time_parameterization.h>

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

        void Init(std::shared_ptr<RobotUr> robot)
        {
            // initialize planning interface
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize planning scene interface"));
            this->planning_scene_interface_ = std::make_shared<moveit::planning_interface::PlanningSceneInterface>();

            // Create the MoveIt MoveGroup Interface
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize group interface"));
            move_group_interface_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(robot, PLANNING_GROUP);
            move_group_interface_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(robot, PLANNING_GROUP);

            //move_group_interface_->setPlannerId("PRMkConfigDefault");
            //move_group_interface_->setNumPlanningAttempts(20);
            //move_group_interface_->setPlanningTime(10);
            //move_group_interface_->setReplanAttempts(10);


            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize Collision boxes"));
            
            auto size = 1.9;
            auto size05 = size * 0.5;

            //move_group_interface_->setWorkspace(-size05, -size05, 0, size05, size05, 1);

            auto thickness = 0.04;            
            //add_collision_box("floor", 2, 2, 0.02, 0, 0, -0.01);
            //add_collision_box("gripper_change_station", 0.7, 0.4, 0.45, 0, -0.65, 0.225);
            add_collision_box("scan_tower", 0.3, 0.3, 1, +0.65, -0.25, 0.5);
            add_collision_box("scan_tower_sensor", 0.16, 0.1, 0.1, 0.56, -0.265334, 0.73);

            //WERKSTÜCK BOXEN
            add_hollow_box_collision("BOX1",0.56,0.36,0.125,0.012,-0.55,0.23,0.125/2);
            add_hollow_box_collision("BOX2",0.56,0.36,0.125,0.012,-0.55,-0.23,0.125/2);

            add_collision_box("wall1", size, thickness, 1.0, 0, size05, 0.5);
            add_collision_box("wall2", size, thickness, 1.0, 0, -size05, 0.5);
            add_collision_box("wall3", thickness, size, 1.0, size05, 0, 0.5);
            add_collision_box("wall4", thickness, size, 1.0, -size05, 0, 0.5);
            add_collision_box("gripper_change_station", 0.7, 0.4, 0.45, 0, -0.775, 0.225);
        
            //add_collision_box("ceiling", size, size, 0.1, 0, 0, 1);

            //BEMI BOXEN//
            //auto bemi_höhe = 0.215; // Gibt zwei Arten, einer is höher als der Andere
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
        void set_path_constraints()
        {
            moveit_msgs::msg::OrientationConstraint ocm;
            ocm.link_name = PLANNING_GROUP;
            ocm.header.frame_id = BASE_FRAME;
            ocm.orientation.w = 1.0;
            ocm.absolute_x_axis_tolerance = 0.001;
            ocm.absolute_y_axis_tolerance = 0.001;
            ocm.absolute_z_axis_tolerance = 0.001;
            ocm.weight = 1.0;
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
        
        void set_execute_duration_for_trajectory(moveit_msgs::msg::RobotTrajectory& input_trajectory, double execute_duration)
        {
            std::vector<trajectory_msgs::msg::JointTrajectoryPoint>& joint_trajectories = input_trajectory.joint_trajectory.points;
            size_t size = joint_trajectories.size();
            execute_duration = execute_duration/size;
            for (int i=0; i<size; i++)
            {
                builtin_interfaces::msg::Duration duration = builtin_interfaces::msg::Duration();
                duration.set__sec(execute_duration * i);
                joint_trajectories[i].time_from_start = duration;
            }
        }

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
                add_collision_box("gripper_change_station", 0.7, 0.45, 0.45, 0, -0.7, 0.225);
                add_collision_box("floor", 2, 2, 0.02, 0, 0, -0.011);

                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Set pipeline to ompl");
                move_group_interface_->setPlanningPipelineId("ompl");
                move_group_interface_->setPlannerId("RRTConnectkConfigDefault");
                //move_group_interface_->setPlannerId("SemiPersistentLazyPRMstar");

                move_group_interface_->setMaxVelocityScalingFactor(scaling_velocity_ompl);
                move_group_interface_->setMaxAccelerationScalingFactor(scaling_acceleration_ompl);

                move_group_interface_->setNumPlanningAttempts(5);
                move_group_interface_->setPlanningTime(5);
                

                auto size = 1.9;
                auto size05 = size * 0.5;

                //move_group_interface_->setWorkspace(-size05, -size05, 0, size05, size05, 1);                
            }
            else if (is_movement_cartesian)
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Set pipeline to pilz industrial planner");
                move_group_interface_->setPlanningPipelineId("pilz_industrial_motion_planner");
                move_group_interface_->setPlannerId("LIN");

                move_group_interface_->setMaxVelocityScalingFactor(scaling_velocity_pilz);
                move_group_interface_->setMaxAccelerationScalingFactor(scaling_acceleration_pilz);
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

                remove_collision_object("gripper_change_station");
                remove_collision_object("floor");
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
            }
            else
            {
                response->result = false;
            }
        }

        void service_callback_robot_follow_trajectory(const std::shared_ptr<wzlscheduler_interfaces::srv::RobotFollowTrajectory::Request> request,
            std::shared_ptr<wzlscheduler_interfaces::srv::RobotFollowTrajectory::Response> response)
        {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request (follow trajectory)");
            
            moveit_msgs::msg::RobotTrajectory trajectory;
            std::vector<geometry_msgs::msg::Pose> waypoints;

            waypoints.push_back(last_pose_);
            auto points = request->supportpoints;

            for (const auto& point : points)
            {
                waypoints.push_back(point);
            }

            waypoints.push_back(last_pose_);

            move_group_interface_->computeCartesianPath(waypoints, 0.002, 0, trajectory, false);


            auto const success = static_cast<bool>(move_group_interface_->execute(trajectory));
    
            response->result = true;
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
            // Attach the object to the end effector of the robot
            const std::string& endEffectorLink = move_group_interface_->getEndEffectorLink();
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Attach the object '%s' to the robots end effector link", request->name.c_str());
            std::vector<std::string> touch_links = {endEffectorLink};
            
            if (!move_group_interface_->attachObject(request->name, endEffectorLink, touch_links))
            {
                RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Attach object failed");
            }

            response->result = 1;
        }

        void service_callback_scene_object_detach(const std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectDetach::Request> request,
            std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectDetach::Response> response)
        {
            // Detach the object from the robot
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Detach the object '%s' from the robot", request->name.c_str());
            
            if (!move_group_interface_->detachObject(request->name))
            {
                RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Detach object failed");
            }

            geometry_msgs::msg::Pose msg;

            response->result = 1;
            response->name = request->name;
            response->coordinates = msg;
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
            const rclcpp::Logger logger = rclcpp::get_logger("addMeshCollisionObject_LOGGER");
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
        int current_mode_; // 0: ompl; 1: pilz industrial planner
        
        double scaling_velocity_ompl = 1.0;
        double scaling_acceleration_ompl = 1.0;
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
  node->Init(node);
  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();
  
  return 0;
}