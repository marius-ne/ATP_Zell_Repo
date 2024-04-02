#include "../include/SceneLoader.h"

#include "geometric_shapes/shapes.h"
#include <geometric_shapes/shape_operations.h>
#include <moveit_visual_tools/moveit_visual_tools.h>

WzlPlanner::SceneLoader::SceneLoader(moveit::planning_interface::MoveGroupInterface* moveGoupInterface)
{
    this->moveGoupInterface = moveGoupInterface;
}

void WzlPlanner::SceneLoader::Initialize(moveit::planning_interface::MoveGroupInterface* moveGoupInterface)
{
    this->moveGoupInterface = moveGoupInterface;
}

moveit_msgs::msg::CollisionObject WzlPlanner::SceneLoader::AddBoxCollisionBox(std::string id,
    double positionX, double positionY, double positionZ,
    double sizeX, double SizeY, double sizeZ)
{
    auto frame_id = moveGoupInterface->getPlanningFrame();

    moveit_msgs::msg::CollisionObject collision_object;
    collision_object.header.frame_id = frame_id;
    collision_object.id = id;
    shape_msgs::msg::SolidPrimitive primitive;

    // Define the size of the box in meters
    primitive.type = primitive.BOX;
    primitive.dimensions.resize(3);
    primitive.dimensions[primitive.BOX_X] = sizeX;
    primitive.dimensions[primitive.BOX_Y] = SizeY;
    primitive.dimensions[primitive.BOX_Z] = sizeZ;

    // Define the pose of the box (relative to the frame_id)
    geometry_msgs::msg::Pose box_pose;

    //todo:: make orientation adjustable through method parameters
    box_pose.orientation.w = 1.0;
    box_pose.position.x = positionX;
    box_pose.position.y = positionY;
    box_pose.position.z = positionZ;

    collision_object.primitives.push_back(primitive);
    collision_object.primitive_poses.push_back(box_pose);
    collision_object.operation = collision_object.ADD;


    planning_scene_interface.applyCollisionObject(collision_object);

    return collision_object;
}


// Method for constructing a mesh collision object
bool addMeshColllsionObject(
  const moveit::planning_interface::MoveGroupInterface& moveGroupInterface, 
  moveit::planning_interface::PlanningSceneInterface& planningSceneInterface,
  std::string pathToMesh, std::string meshId, float scaleFactor, geometry_msgs::msg::Pose meshPose) 
{
    // Get the planning frame
    std::string frame_id = moveGroupInterface.getPlanningFrame();

    // Create a CollisionObject
    moveit_msgs::msg::CollisionObject collision_object;
    collision_object.header.frame_id = frame_id;
    collision_object.id = meshId;

    // Create a mesh from the specified path
    shapes::Mesh * original_mesh = shapes::createMeshFromResource(pathToMesh);
    
    original_mesh->scale(scaleFactor);

    // Create a scaled copy of the original mesh with padding
    shapes::Mesh * scaled_mesh = new shapes::Mesh(*original_mesh);

    //scaled_mesh->scaleAndPadd(scaleFactor, 0.0);  // Adjust padding as needed
    //scaled_mesh->scale(scaleFactor);
    // Convert the scaled mesh to shape_msgs::Mesh
    shape_msgs::msg::Mesh shelf_mesh;
    shapes::ShapeMsg shelf_mesh_msg;
    shapes::constructMsgFromShape(original_mesh, shelf_mesh_msg);
    shelf_mesh = boost::get<shape_msgs::msg::Mesh>(shelf_mesh_msg);


    // Add the mesh and pose to the CollisionObject
    collision_object.meshes.push_back(shelf_mesh);
    collision_object.mesh_poses.push_back(meshPose);
    collision_object.operation = collision_object.ADD;

    // Add collision object to planning scene interface -> planningSceneInterface reference will be changed

    //if (planningSceneInterface.applyCollisionObject(collision_object))
    //{
    //  //ROS_INFO("Successfuölly added object to the scene");  
    //  RCLCPP_DEBUG(node->get_logger(), "uccessfuölly added object to the scene %d", 4);
    //} 
    //else
    //{
    //  //ROS_INFO("Failed to add object to the scene");  
    //  RCLCPP_DEBUG(node->get_logger(), "Failed to add object to the scene", 4);
    //}

    // Clean up the memory allocated for the scaled mesh
    delete scaled_mesh;

    return planningSceneInterface.applyCollisionObject(collision_object);
}
