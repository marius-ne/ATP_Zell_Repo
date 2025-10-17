#include <rclcpp/rclcpp.hpp>
#include "moveit/move_group_interface/move_group_interface.h"
#include "moveit/planning_scene_interface/planning_scene_interface.h"
#include "moveit/planning_scene_monitor/planning_scene_monitor.h"
#include "geometric_shapes/shape_operations.h"
#include "ament_index_cpp/get_package_share_directory.hpp"

#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

#include "geometric_shapes/shapes.h"
#include "geometric_shapes/mesh_operations.h"
#include "geometric_shapes/shape_operations.h"



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

static const std::string PLANNING_GROUP = "iiwa_arm";
static const std::string BASE_FRAME = "world";

class RobotIiwaServer : public rclcpp::Node
{
     // RAII-Guard-Klasse, um sicherzustellen, dass Kollisionsobjekte wiederhergestellt werden
     class CollisionObjectGuard {
        public:
            CollisionObjectGuard(RobotIiwaServer* robot_node, const std::vector<std::string>& object_ids)
                : robot_node_(robot_node), object_ids_(object_ids) {}
    
            ~CollisionObjectGuard() {
                for (const auto& obj_id : object_ids_) {
                    robot_node_->re_add_stored_collision_object(obj_id);
                }
            }
    
            // Verhindere das Kopieren und Verschieben des Guards
            CollisionObjectGuard(const CollisionObjectGuard&) = delete;
            CollisionObjectGuard& operator=(const CollisionObjectGuard&) = delete;
            CollisionObjectGuard(CollisionObjectGuard&&) = delete;
            CollisionObjectGuard& operator=(CollisionObjectGuard&&) = delete;
    
        private:
            RobotIiwaServer* robot_node_;
            const std::vector<std::string>& object_ids_;
        };

    public:
        RobotIiwaServer()
        : Node("robot_iiwa_server", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true))
        {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize services"));

            // connect the ros services
            service_robot_move_toposition_ = this->create_service<wzlscheduler_interfaces::srv::RobotMoveToPosition>("robot_move_to_position", std::bind(&RobotIiwaServer::service_callback_robot_move_to_position, this, std::placeholders::_1, std::placeholders::_2));
            service_robot_follow_trajectory_ = this->create_service<wzlscheduler_interfaces::srv::RobotFollowTrajectory>("robot_follow_trajectory", std::bind(&RobotIiwaServer::service_callback_robot_follow_trajectory, this, std::placeholders::_1, std::placeholders::_2));
            service_robot_set_velocity_ = this->create_service<wzlscheduler_interfaces::srv::RobotSetVelocity>("robot_set_velocity", std::bind(&RobotIiwaServer::service_callback_robot_set_velocity, this, std::placeholders::_1, std::placeholders::_2));
            service_scene_object_attach = this->create_service<wzlscheduler_interfaces::srv::SceneObjectAttach>("scene_object_attach", std::bind(&RobotIiwaServer::service_callback_scene_object_attach, this, std::placeholders::_1, std::placeholders::_2));
            service_scene_object_detach = this->create_service<wzlscheduler_interfaces::srv::SceneObjectDetach>("scene_object_detach", std::bind(&RobotIiwaServer::service_callback_scene_object_detach, this, std::placeholders::_1, std::placeholders::_2));

            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize topics"));

            // connect topics
            subscription_scene_object_add_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectAdd>
                ("scene_object_add", 10, std::bind(&RobotIiwaServer::topic_callback_scene_object_add, this, std::placeholders::_1));

            subscription_scene_object_remove_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectRemove>
                ("scene_object_remove", 10, std::bind(&RobotIiwaServer::topic_callback_scene_object_remove, this, std::placeholders::_1));

            subscription_scene_object_set_pose_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectSetPose>
                ("scene_object_set_pose", 10, std::bind(&RobotIiwaServer::topic_callback_scene_object_set_pose, this, std::placeholders::_1));

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
            
            auto size = 1.4;
            auto size05 = size * 0.5;
            auto thickness = 0.05;    

            //WERKSTÜCK BOXEN
            
            add_hollow_box_collision("BOX1",0.56,0.36,0.125,0.012, 0.1,-0.515,0.125/2);
            add_hollow_box_collision("BOX2",0.56,0.36,0.125,0.012, 0.1,0.515,0.125/2);
            //Bemi1
            //add_hollow_box_collision("Bemi1", 0.125, 0.2, 0.09, 0.012, 0.54, 0.05, 0.09/2);
            // Neue Mesh-Kollision für Bemi1 hinzufügen
            geometry_msgs::msg::Pose bemi1_pose;
            bemi1_pose.position.x = 0.54;
            bemi1_pose.position.y = 0.05;
            bemi1_pose.position.z = 0.09/2;
            bemi1_pose.orientation.w = 1.0; // Keine Rotation
            add_mesh_from_file("Bemi1", "BEMI(Meshed).dae", bemi1_pose); 

            
            //Schraubenbox
            add_collision_box("Box 4", 0.25, 0.12, 0.165, -0.55, -0.55, 0.0825);
            
           //ZELLE
            add_collision_box("wall1", size, thickness, 1.0, 0, size05, 0.5);
            add_collision_box("wall2", size, thickness, 1.0, 0, -size05, 0.5);
            add_collision_box("wall3", thickness, size, 1.0, size05, 0, 0.5);
            add_collision_box("wall4", thickness, size, 1.0, -size05, 0, 0.5);

            //Monitor
            add_collision_box("Monitor", 0.05, 0.6, 0.4, 0.9, -0.8, 0.3);
            
            add_collision_box("floor", 2, 2, 0.0198, 0, 0, -0.01);
            //add_collision_box("ceiling", size, size, 0.1, 0, 0, 1);

            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialization done"));
        }

    private:
    mutable std::map<std::string, moveit_msgs::msg::CollisionObject> temporary_removed_objects_; // zwischenspeier für temporär entfernte Kollisionsobjekte
    
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
            adjusted_pose.position.z -= (primitive.dimensions[0] / 2.0)+ 0.01; // Adjusted to place the top at the pose
            adjusted_pose.position.y += 0.01; // Adjusted to center the gripper
            adjusted_pose.position.x -= 0.02; // Adjusted to center the gripper

            collision_object.primitives.push_back(primitive);
            collision_object.primitive_poses.push_back(adjusted_pose);
            collision_object.operation = collision_object.ADD;

            planning_scene_interface_->applyCollisionObject(collision_object);

        }
        void add_mesh_gripper(const std::string name, const geometry_msgs::msg::Pose& pose)
        {
            std::string meshPath = "package://moveit_backend/meshes/parts/Gripper(Meshed).dae";
            double scale  = 1; // scale factor for the mesh
                
            // load the mesh from the resource
            shapes::Mesh* mesh = shapes::createMeshFromResource(meshPath);
            if (!mesh) {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to load mesh from %s - falling back to primitive shape", meshPath.c_str());
                // Fallback to primitive shape
                add_gripper(name, pose);
                return;
            }

            mesh->scale(scale);

            // TCP-relativer Offset (im lokalen Koordinatensystem von link_7)
            geometry_msgs::msg::Pose adjusted_pose = pose;
            
            // Offset-Vektor im TCP-Koordinatensystem (X, Y, Z im TCP-Frame)
            tf2::Vector3 local_offset(0.0, 0.004, 0.04); // Angepasste Werte für den Gripper
            
            // Aktuelle TCP-Orientierung als Quaternion
            tf2::Quaternion tcp_orientation;
            tf2::fromMsg(pose.orientation, tcp_orientation);
            
            // Rotiere den Offset-Vektor in das Welt-Koordinatensystem
            tf2::Vector3 world_offset = tf2::quatRotate(tcp_orientation, local_offset);
            
            // Addiere den rotierten Offset zur Position
            adjusted_pose.position.x += world_offset.x();
            adjusted_pose.position.y += world_offset.y();
            adjusted_pose.position.z += world_offset.z();
                      
            // create the collision object
            moveit_msgs::msg::CollisionObject collision_object;
            collision_object.header.frame_id = move_group_interface_->getPlanningFrame();
            collision_object.id = name;

            // converting the mesh to a collision object
            shapes::ShapeMsg mesh_msg;
            shapes::constructMsgFromShape(mesh, mesh_msg);
            shape_msgs::msg::Mesh mesh_shape = boost::get<shape_msgs::msg::Mesh>(mesh_msg);
            
    
            // add the mesh to the collision object
            collision_object.meshes.push_back(mesh_shape);
            collision_object.mesh_poses.push_back(adjusted_pose);
            collision_object.operation = collision_object.ADD;
            
            // add the collision object to the planning scene
            planning_scene_interface_->applyCollisionObject(collision_object);
            
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), 
                "Added mesh gripper: %s", name.c_str());
                
            delete mesh;
        }
        void add_mesh_workpiece(const std::string name, const geometry_msgs::msg::Pose& pose, 
            int partType = 0, int workpieceOrientation = 0)
            {
                geometry_msgs::msg::Pose adjusted_pose = pose;

                
                if (partType != 3) {
                double offset_x = 0.005;//0.006 davor -> Crash beim aufnehmen     
                double offset_y = -0.041;  //-0.045   

                double angle_rad = workpieceOrientation * M_PI / 180.0;

                // Offset-Transformation
                double rotated_offset_x = offset_x * cos(angle_rad) - offset_y * sin(angle_rad);
                double rotated_offset_y = offset_x * sin(angle_rad) + offset_y * cos(angle_rad);

                adjusted_pose.position.x += rotated_offset_x;
                adjusted_pose.position.y += rotated_offset_y;
                }

                // Offset the position down by half the length to place top at pose
                double length_gripper = 0.19;
                adjusted_pose.position.z -= length_gripper - 0.02; //- 0.05 damit nicht zu weil oben
                // Rotation for workpiece orientation
                
                // create a quaternion for the gripper orientation
                tf2::Quaternion gripper_orientation;
                tf2::fromMsg(pose.orientation, gripper_orientation);

                // create a quaternion for the workpiece orientation
                tf2::Quaternion workpiece_rotation;
                double angle_rad = (workpieceOrientation - 10.0) * M_PI / 180.0;
                workpiece_rotation.setRPY(0,  M_PI, angle_rad);

                // combine the orientations
                tf2::Quaternion final_orientation = gripper_orientation * workpiece_rotation;
                final_orientation.normalize();

                // add the orientation to the adjusted pose
                adjusted_pose.orientation = tf2::toMsg(final_orientation);

                // create the collision object
                moveit_msgs::msg::CollisionObject collision_object;
                collision_object.header.frame_id = move_group_interface_->getPlanningFrame();
                collision_object.id = name;

                // path to the mesh file based on partType
                std::string meshPath;
                double scale  = 1; // scale factor for the mesh

                if (partType == 3) {
                meshPath = "package://moveit_backend/meshes/parts/kugellager1.stl";
                } else if (partType == 2) {
                meshPath = "package://moveit_backend/meshes/parts/Workpiece_Oben(Meshed).dae";
                } else {
                meshPath = "package://moveit_backend/meshes/parts/Workpiece_Unten(Meshed).dae";
                }

                // load the mesh from the resource
                shapes::Mesh* mesh = shapes::createMeshFromResource(meshPath);
                if (!mesh) {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to load mesh from %s - falling back to primitive shape", meshPath.c_str());
                // Fallback to primitive shape
                add_workpiece(name, pose, partType, workpieceOrientation);
                return;
                }

                mesh->scale(scale);

                // converting the mesh to a collision object
                shapes::ShapeMsg mesh_msg;
                shapes::constructMsgFromShape(mesh, mesh_msg);
                shape_msgs::msg::Mesh mesh_shape = boost::get<shape_msgs::msg::Mesh>(mesh_msg);

                // add the mesh to the collision object
                collision_object.meshes.push_back(mesh_shape);
                collision_object.mesh_poses.push_back(adjusted_pose);
                collision_object.operation = collision_object.ADD;

                // add the collision object to the planning scene
                planning_scene_interface_->applyCollisionObject(collision_object);

                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), 
                "Adding mesh workpiece of type %d with orientation: %d, quaternion: [%f, %f, %f, %f]",
                partType,
                workpieceOrientation, 
                adjusted_pose.orientation.x,
                adjusted_pose.orientation.y,
                adjusted_pose.orientation.z,
                adjusted_pose.orientation.w);

                delete mesh; // delete the mesh to avoid memory leak
                }

                void add_workpiece(const std::string name, const geometry_msgs::msg::Pose& pose, int partType = 0, int workpieceOrientation = 0)
                {
                // Add collision object
                moveit_msgs::msg::CollisionObject collision_object;
                collision_object.header.frame_id = move_group_interface_->getPlanningFrame();
                collision_object.id = name;

                shape_msgs::msg::SolidPrimitive primitive;
                primitive.type = primitive.BOX;
                primitive.dimensions.resize(3);

                //pose gripper
                geometry_msgs::msg::Pose adjusted_pose = pose;

                /*
                if(partType == 3) //Kugellager
                {
                primitive.dimensions[primitive.BOX_X] = 0.01;
                primitive.dimensions[primitive.BOX_Y] = 0.01;
                primitive.dimensions[primitive.BOX_Z] = 0.01;
                }
                else
                {*/
                primitive.dimensions[primitive.BOX_X] = 0.1;
                primitive.dimensions[primitive.BOX_Y] = 0.18;
                primitive.dimensions[primitive.BOX_Z] = 0.03;

                // Offset for the gripper position
                double offset_x = 0.005;     
                double offset_y = -0.045;     


                double angle_rad = workpieceOrientation * M_PI / 180.0;

                // offset transformation
                double rotated_offset_x = offset_x * cos(angle_rad) - offset_y * sin(angle_rad);
                double rotated_offset_y = offset_x * sin(angle_rad) + offset_y * cos(angle_rad);

                adjusted_pose.position.x += rotated_offset_x;
                adjusted_pose.position.y += rotated_offset_y;
                //}

                // Offset the position down by half the length to place top at pose
                double length_gripper = 0.19; // Length
                adjusted_pose.position.z -= length_gripper - 0.05;

                // Rotation for workpiece orientation
                tf2::Quaternion orientation_quaternion;
                angle_rad = workpieceOrientation * M_PI / 180.0;

                // Rotation around Z-axis
                orientation_quaternion.setRPY(0, 0, angle_rad);
                orientation_quaternion.normalize();

                adjusted_pose.orientation.x = orientation_quaternion.x();
                adjusted_pose.orientation.y = orientation_quaternion.y();
                adjusted_pose.orientation.z = orientation_quaternion.z();
                adjusted_pose.orientation.w = orientation_quaternion.w();

                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), 
                "Adding workpiece with orientation: %d, quaternion: [%f, %f, %f, %f]",
                workpieceOrientation, 
                adjusted_pose.orientation.x,
                adjusted_pose.orientation.y,
                adjusted_pose.orientation.z,
                adjusted_pose.orientation.w);

                collision_object.primitives.push_back(primitive);
                collision_object.primitive_poses.push_back(adjusted_pose);
                collision_object.operation = collision_object.ADD;

                planning_scene_interface_->applyCollisionObject(collision_object);
                }
        /*void add_workpiece_from_bemi(const std::string name, const geometry_msgs::msg::Pose& pose)
        {
            // add a cylinder with dimensions radius 0.055 length 0.19
            moveit_msgs::msg::CollisionObject collision_object;
            collision_object.header.frame_id = move_group_interface_->getPlanningFrame();
            collision_object.id = name;

            shape_msgs::msg::SolidPrimitive primitive;
            primitive.type = primitive.BOX;
            primitive.dimensions.resize(3);
            primitive.dimensions[primitive.BOX_X] = 0.1;
            primitive.dimensions[primitive.BOX_Y] = 0.18;
            primitive.dimensions[primitive.BOX_Z] = 0.03;
            double length_gripper = 0.19; // Length

            // Offset the position down by half the length to place top at pose
            geometry_msgs::msg::Pose adjusted_pose = pose;
            adjusted_pose.position.z -= length_gripper - 0.05;
            adjusted_pose.position.y += 0.045;
            adjusted_pose.position.x -= 0.005;
            adjusted_pose.orientation.x = 0.0;
            adjusted_pose.orientation.y = 0.0;
            adjusted_pose.orientation.z = 0.0;
            adjusted_pose.orientation.w = 1.0;

            collision_object.primitives.push_back(primitive);
            collision_object.primitive_poses.push_back(adjusted_pose);
            collision_object.operation = collision_object.ADD;

            planning_scene_interface_->applyCollisionObject(collision_object);
        }

        void add_workpiece_from_PC(const std::string name, const geometry_msgs::msg::Pose& pose)
        {
            // add a cylinder with dimensions radius 0.055 length 0.19
            moveit_msgs::msg::CollisionObject collision_object;
            collision_object.header.frame_id = move_group_interface_->getPlanningFrame();
            collision_object.id = name;

            shape_msgs::msg::SolidPrimitive primitive;
            primitive.type = primitive.BOX;
            primitive.dimensions.resize(3);
            primitive.dimensions[primitive.BOX_X] = 0.18;
            primitive.dimensions[primitive.BOX_Y] = 0.10;
            primitive.dimensions[primitive.BOX_Z] = 0.03;
            double length_gripper = 0.19; // Length

            // Offset the position down by half the length to place top at pose
            geometry_msgs::msg::Pose adjusted_pose = pose;
            adjusted_pose.position.z -= length_gripper - 0.05;
            adjusted_pose.position.y += 0.005;
            adjusted_pose.position.x += 0.045;
            adjusted_pose.orientation.x = 0.0;
            adjusted_pose.orientation.y = 0.0;
            adjusted_pose.orientation.z = 0.0;
            adjusted_pose.orientation.w = 1.0;

            collision_object.primitives.push_back(primitive);
            collision_object.primitive_poses.push_back(adjusted_pose);
            collision_object.operation = collision_object.ADD;

            planning_scene_interface_->applyCollisionObject(collision_object);
        }
*/
        
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

                // Define the center pose of the box (relative to the frame_id)
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

        void add_mesh_from_file(const std::string& object_id, const std::string& mesh_filename, const geometry_msgs::msg::Pose& pose)
        {
            moveit_msgs::msg::CollisionObject collision_object;
            collision_object.header.frame_id = move_group_interface_->getPlanningFrame();
            collision_object.id = object_id;

            // Pfad zur Mesh-Datei erstellen
            std::string meshPath = "package://moveit_backend/meshes/parts/" + mesh_filename;

            // Mesh aus der Datei laden
            shapes::Mesh* mesh = shapes::createMeshFromResource(meshPath);
            if (!mesh) {
                RCLCPP_ERROR(this->get_logger(), "Failed to load mesh from %s", meshPath.c_str());
                return;
            }

            // Mesh in eine Shape-Nachricht konvertieren
            shapes::ShapeMsg mesh_msg;
            shapes::constructMsgFromShape(mesh, mesh_msg);
            shape_msgs::msg::Mesh mesh_shape = boost::get<shape_msgs::msg::Mesh>(mesh_msg);
            
            // Mesh und Pose zum Kollisionsobjekt hinzufügen
            collision_object.meshes.push_back(mesh_shape);
            collision_object.mesh_poses.push_back(pose);
            collision_object.operation = collision_object.ADD;
            
            // Kollisionsobjekt zur Szene hinzufügen
            planning_scene_interface_->applyCollisionObject(collision_object);
            
            RCLCPP_INFO(this->get_logger(), "Added mesh collision object '%s' from file '%s'", object_id.c_str(), mesh_filename.c_str());
                
            delete mesh; // Speicher freigeben
        }


        void remove_collision_object(const std::string& objectId) const
        {
            if(objectId=="floor"||objectId== "Bemi1"||objectId==  "BOX1"||objectId== "BOX2")
            {
                if (temporary_removed_objects_.count(objectId)) {
                RCLCPP_WARN(this->get_logger(), "Object '%s' is already in temporary storage, not removing again.", objectId.c_str());
                return;
                }
            }
            // Get all collision objects from the planning scene
            std::map<std::string, moveit_msgs::msg::CollisionObject> scene_objects = planning_scene_interface_->getObjects();

            // Find the object to remove
            auto it = scene_objects.find(objectId);
            if (it != scene_objects.end())
            {
                if(objectId=="floor"||objectId== "Bemi1"||objectId==  "BOX1"||objectId== "BOX2")
            {
                // Store the object for later re-adding
                temporary_removed_objects_[objectId] = it->second;

                // Construct the collision object for removal
                moveit_msgs::msg::CollisionObject collision_object_to_remove;
                collision_object_to_remove.id = objectId;
                collision_object_to_remove.operation = collision_object_to_remove.REMOVE; 

                // Remove collision object from planning scene
                planning_scene_interface_->applyCollisionObject(collision_object_to_remove);
            }
            else
            {
                // Directly remove the object from the planning scene
                std::vector<std::string> object_ids_to_remove = {objectId};
                planning_scene_interface_->removeCollisionObjects(object_ids_to_remove);
            }
                RCLCPP_INFO(this->get_logger(), "Collision object '%s' temporarily removed and stored.", objectId.c_str());
            }
            else
            {
                RCLCPP_WARN(this->get_logger(), "Could not find collision object '%s' to remove.", objectId.c_str());
            }
        }
        void re_add_stored_collision_object(const std::string& objectId)
        {
            auto it = temporary_removed_objects_.find(objectId);
            if (it != temporary_removed_objects_.end())
            {
                moveit_msgs::msg::CollisionObject object_to_add = it->second;
                object_to_add.operation = object_to_add.ADD;

                planning_scene_interface_->applyCollisionObject(object_to_add);
                
                // Remove from temporary storage
                temporary_removed_objects_.erase(it);

                RCLCPP_INFO(this->get_logger(), "Stored collision object '%s' re-added to the scene.", objectId.c_str());
            }
            else
            {
                RCLCPP_WARN(this->get_logger(), "Could not find stored collision object '%s' to re-add.", objectId.c_str());
            }
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
            //std::vector<std::string> objects_to_handle;

            if (is_movement_normal)
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Set pipeline to ompl");
                move_group_interface_->setPlanningPipelineId("ompl");
                move_group_interface_->setPlannerId("RRTConnectkConfigDefault");

                move_group_interface_->setMaxVelocityScalingFactor(scaling_velocity_ompl);
                move_group_interface_->setMaxAccelerationScalingFactor(scaling_acceleration_ompl);

                move_group_interface_->setNumPlanningAttempts(3);
                move_group_interface_->setPlanningTime(2.0);

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
                
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Set pipeline to pilz industrial planner");
                move_group_interface_->setPlanningPipelineId("pilz");

                // Temporarily remove collision objects for cartesian planning
                std::vector<std::string> objects_to_handle = {"floor", "Bemi1", "BOX1", "BOX2"};
                
                // Guard erstellen, der das Aufräumen automatisch übernimmt
                CollisionObjectGuard guard(this, objects_to_handle);
                
                for (const auto& obj_id : objects_to_handle) {
                    remove_collision_object(obj_id);
                }

                move_group_interface_->setPlannerId("LIN");

                move_group_interface_->setMaxVelocityScalingFactor(scaling_velocity_pilz);
                move_group_interface_->setMaxAccelerationScalingFactor(scaling_acceleration_pilz);
                move_group_interface_->setNumPlanningAttempts(1);
                move_group_interface_->setPlanningTime(1.0);
            
                if (moveType == 3) // absolute pose cartesian movement
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

                // Re-add the temporarily removed collision objects, durch guard abgelöst
                /*for (const auto& obj_id : objects_to_handle) {
                    re_add_stored_collision_object(obj_id);}
                */
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
            item.req.pipeline_id = "pilz";
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
            int partType = request->part_type; 
            int workpieceOrientation = request->workpiece_orientation;
            
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
                add_mesh_gripper(name, pose);
                 //add_mesh_gripper(name, pose);//CAD modell for gripper -> slows down planning
                if (!move_group_interface_->attachObject(name))
                {
                    RCLCPP_WARN(rclcpp::get_logger("rclcpp"), "Attach object '%s' failed", name.c_str());
                    response->result = 0;
                    return;
                }
                response->result = 1;
            }else if (name == "workpiece")
            {
                add_mesh_workpiece(name, pose, partType, workpieceOrientation);//CAD Modell  for workpiece -> slows down planning
                //add_workpiece(name, pose, partType, workpieceOrientation);
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

            if (name == "spindel" || name == "gripper" || name == "small_gripper" || name == "workpiece")
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Object '%s' recognized for detachment", name.c_str());
                
                // Detach the object from the robot
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
            else if (name == "Box 4" || name == "BOX1" || name == "BOX2")
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
                        
            // Get the planning frame
            std::string frame_id = move_group_interface_->getPlanningFrame();

            // Create a CollisionObject
            moveit_msgs::msg::CollisionObject collision_object;
            collision_object.header.frame_id = frame_id;
            std::string objectName = msg.name;
            collision_object.id = objectName;

            // direct path to the mesh file
            std::string meshPath = "package://moveit_backend/meshes/parts/" + objectName + ".stl";

            // Create a mesh from the specified path
            shapes::Mesh* original_mesh = shapes::createMeshFromResource(meshPath);
            if (!original_mesh) {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Could not load mesh from path: %s", meshPath.c_str());
                return;
            }

            // Create a scaled copy of the original mesh with padding
            shapes::Mesh* scaled_mesh = new shapes::Mesh(*original_mesh);
            scaled_mesh->scaleAndPadd(0.001, 0.0);  
            
            // Convert the scaled mesh to shape_msgs::Mesh
            shape_msgs::msg::Mesh shelf_mesh;
            geometry_msgs::msg::Pose meshPose = msg.coordinates;
            collision_object.mesh_poses.push_back(meshPose);
            collision_object.operation = collision_object.ADD;

            // Add collision object to planning scene interface
            planning_scene_interface_->applyCollisionObject(collision_object);

            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Collision mesh: %s added to scene!", objectName.c_str());

            // Clean up the memory
            delete scaled_mesh;
            delete original_mesh;
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
        double scaling_acceleration_pilz = 0.02;

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

    auto const node = std::make_shared<RobotIiwaServer>();

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