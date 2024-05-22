#include <memory>

#include "../include/FileLoader.h"

#include "wzlscheduler_interfaces/srv/robot_move_to_position.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_attach.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_detach.hpp"

#include "wzlscheduler_interfaces/msg/scene_object_add.hpp"
#include "wzlscheduler_interfaces/msg/scene_object_remove.hpp"
#include "wzlscheduler_interfaces/msg/scene_object_set_pose.hpp"


#include <rclcpp/rclcpp.hpp>
#include "moveit/move_group_interface/move_group_interface.h"
#include "moveit/planning_scene_interface/planning_scene_interface.h"
#include "moveit/planning_scene_monitor/planning_scene_monitor.h"
#include "geometric_shapes/shape_operations.h"
#include "ament_index_cpp/get_package_share_directory.hpp"


std::shared_ptr<moveit::planning_interface::MoveGroupInterface> move_group_interface_;
moveit::planning_interface::PlanningSceneInterface planning_scene_interface_;

rclcpp::Service<wzlscheduler_interfaces::srv::RobotMoveToPosition>::SharedPtr service_robot_move_toposition_;
rclcpp::Service<wzlscheduler_interfaces::srv::SceneObjectAttach>::SharedPtr service_scene_object_attach;
rclcpp::Service<wzlscheduler_interfaces::srv::SceneObjectDetach>::SharedPtr service_scene_object_detach;

rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectAdd>::SharedPtr subscription_scene_object_add_;
rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectRemove>::SharedPtr subscription_scene_object_remove_;
rclcpp::Subscription<wzlscheduler_interfaces::msg::SceneObjectSetPose>::SharedPtr subscription_scene_object_set_pose_;

class RobotPanda : public rclcpp::Node
{
  public:
    RobotPanda()
      : Node("robot panda")//, rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true))
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize services"));

        // connect the ros services
        service_robot_move_toposition_ = this->create_service<wzlscheduler_interfaces::srv::RobotMoveToPosition>("robot_move_to_position", std::bind(&RobotPanda::service_callback_robot_move_to_position, this, std::placeholders::_1, std::placeholders::_2));
        service_scene_object_attach = this->create_service<wzlscheduler_interfaces::srv::SceneObjectAttach>("service_callback_scene_object_attach", std::bind(&RobotPanda::service_callback_scene_object_attach, this, std::placeholders::_1, std::placeholders::_2));
        service_scene_object_detach = this->create_service<wzlscheduler_interfaces::srv::SceneObjectDetach>("service_callback_scene_object_detach", std::bind(&RobotPanda::service_callback_scene_object_detach, this, std::placeholders::_1, std::placeholders::_2));

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize topics"));

        // connect topics
        subscription_scene_object_add_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectAdd>
          ("scene_object_add", 10, std::bind(&RobotPanda::topic_callback_scene_object_add, this, std::placeholders::_1));

        subscription_scene_object_remove_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectRemove>
          ("scene_object_remove", 10, std::bind(&RobotPanda::topic_callback_scene_object_remove, this, std::placeholders::_1));

        subscription_scene_object_set_pose_ = this->create_subscription<wzlscheduler_interfaces::msg::SceneObjectSetPose>
          ("scene_object_set_pose", 10, std::bind(&RobotPanda::topic_callback_scene_object_set_pose, this, std::placeholders::_1));
    }

    void Init(std::shared_ptr<RobotPanda> robot)
    {
      // Create the MoveIt MoveGroup Interface
      move_group_interface_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(robot, "panda_arm");
    }

  private:
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
      //msg.orientation.w = 1.0; // todo: set also the orientation
      //msg.position.x = request->posx;
      //msg.position.y = request->posy;
      //msg.position.z = request->posz;
      //msg.orientation.x = request->rotx;
      //msg.orientation.y = request->roty;
      //msg.orientation.z = request->rotz;

      response->result = 1;
      response->name = request->name;
      response->coordinates = msg;
    }


    void service_callback_robot_move_to_position(const std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition::Request> request,
            std::shared_ptr<wzlscheduler_interfaces::srv::RobotMoveToPosition::Response> response)
    {
      auto position = request->pose.position;
      auto orientation = request->pose.orientation;

      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request (move to position)\nX: %g" " Y: %g Z: %g RotX: %g RotY %g RotZ %g RotW %g",
                    position.x,position.y, position.z, orientation.x, orientation.y, orientation.z, orientation.w);
      // Set a target Pose
      geometry_msgs::msg::Pose msg;
      msg.position = position;
      msg.orientation = orientation;
    
      move_group_interface_->setPoseTarget(msg);

      moveit::planning_interface::MoveGroupInterface::Plan msg2;
      auto const success = static_cast<bool>(move_group_interface_->plan(msg2));

      // Execute the plan
      if(success) {
        move_group_interface_->execute(msg2);
      } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Planing failed!");
      }

      response->result = true;
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
    }

    void topic_callback_scene_object_remove(const wzlscheduler_interfaces::msg::SceneObjectRemove& msg) const
    {
      // Convert the message to a string
      std::string objectId = msg.name;

      // Contruct the collision object
      moveit_msgs::msg::CollisionObject collision_object;
      collision_object.id = objectId;
      collision_object.operation = collision_object.REMOVE; 

      // Remove collision object to planning scene interface -> planningSceneInterface reference will be changed
      planning_scene_interface_.applyCollisionObject(collision_object);

      // Create a ROS logger
      const rclcpp::Logger logger = rclcpp::get_logger("rclcpp");
      RCLCPP_INFO(logger, ("Collision mesh: " + objectId + " removed from scene!").c_str());

    }

    void topic_callback_scene_object_set_pose(const wzlscheduler_interfaces::msg::SceneObjectSetPose& msg) const
    {
    }
};


int main(int argc, char * argv[])
{
  std::cout << "Run node moveit backend" << std::endl;
/*
  // Initialize ROS and create the Node
  rclcpp::init(argc, argv);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), ("Initialize robot"));
  auto const node = std::make_shared<RobotPanda>();
  node->Init(node);
  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();
  */
  return 0;
}