#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>

#include "geometric_shapes/shapes.h"
#include <geometric_shapes/shape_operations.h>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <thread>
#include <iostream>

#include "SceneLoader.h"
#include "Pose.h"
#include "Task.h"



int main(int argc, char* argv[])
{
  // Initialize ROS and create the Node
  rclcpp::init(argc, argv);
  auto const node = std::make_shared<rclcpp::Node>(
      "hello_moveit", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));

  // Create a ROS logger
  auto const logger = rclcpp::get_logger("hello_moveit");
  RCLCPP_DEBUG(node->get_logger(), "Lets start! %d", 4);
  // We spin up a SingleThreadedExecutor for the current state monitor to get
  // information about the robot's state.
  //rclcpp::executors::SingleThreadedExecutor executor;
  //executor.add_node(node);
  //auto spinner = std::thread([&executor]() { executor.spin(); });
  std::cout << "Test" << std::endl;
  // Create the MoveIt MoveGroup Interface
  using moveit::planning_interface::MoveGroupInterface;
  auto move_group_interface = MoveGroupInterface(node, "panda_arm");

  // Construct and initialize MoveItVisualTools
  //auto moveit_visual_tools =
  //    moveit_visual_tools::MoveItVisualTools{ node, "base_link", rviz_visual_tools::RVIZ_MARKER_TOPIC,
  //                                            move_group_interface.getRobotModel() };
  //moveit_visual_tools.deleteAllMarkers();
  //moveit_visual_tools.loadRemoteControl();


  // set pose for collision mesh
  geometry_msgs::msg::Pose shelf_pose;
    shelf_pose.orientation.w = 0;
    shelf_pose.orientation.x = 0;
    shelf_pose.orientation.y = 0;
    shelf_pose.orientation.z = 0;
    shelf_pose.position.x = 0;
    shelf_pose.position.y = 0;
    shelf_pose.position.z = 0;
    
WzlPlanner::TaskList taskList;


WzlPlanner::Pose pose;
pose.SetPositionXYZ(0, 0, 0);

  //addMeshColllsionObject(move_group_interface, planning_scene_interface, meshPath, "meshTest2", 1.0f, shelf_pose);

/*
  // Create a closure for updating the text in rviz
  auto const draw_title = [&moveit_visual_tools](auto text) {
    auto const text_pose = [] {
      auto msg = Eigen::Isometry3d::Identity();
      msg.translation().z() = 1.0;
      return msg;
    }();
    moveit_visual_tools.publishText(text_pose, text, rviz_visual_tools::WHITE, rviz_visual_tools::XLARGE);
  };
  auto const prompt = [&moveit_visual_tools](auto text) { moveit_visual_tools.prompt(text); };
  auto const draw_trajectory_tool_path =
      [&moveit_visual_tools, jmg = move_group_interface.getRobotModel()->getJointModelGroup("panda_arm")](
          auto const trajectory) { moveit_visual_tools.publishTrajectoryLine(trajectory, jmg); };

  // Set a target Pose with updated values !!!
  auto const target_pose = [] {
    geometry_msgs::msg::Pose msg;
    msg.orientation.y = 0.8;
    msg.orientation.w = 0.6;
    msg.position.x = 0.1;
    msg.position.y = 0.4;
    msg.position.z = 0.4;
    return msg;
  }();
  //move_group_interface.setPoseTarget(target_pose);

WzlPlanner::SceneLoader sceneLoader(&move_group_interface);
sceneLoader.AddBoxCollisionBox("testBox", 
1, 1, 1, 1, 1, 1);


  // Create a plan to that target pose
  /*
  prompt("Press 'next' in the RvizVisualToolsGui window to plan");
  draw_title("Planning");
  moveit_visual_tools.trigger();
  auto const [success, plan] = [&move_group_interface] {
    moveit::planning_interface::MoveGroupInterface::Plan msg;
    auto const ok = static_cast<bool>(move_group_interface.plan(msg));
    return std::make_pair(ok, msg);
  }();

  // Execute the plan
  if (success)
  {
    //draw_trajectory_tool_path(plan.trajectory);
    moveit_visual_tools.trigger();
    prompt("Press 'next' in the RvizVisualToolsGui window to execute");
    draw_title("Executing");
    moveit_visual_tools.trigger();
    move_group_interface.execute(plan);
  }
  else
  {
    draw_title("Planning Failed!");
    moveit_visual_tools.trigger();
    RCLCPP_ERROR(logger, "Planning failed!");
  }
  */


  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();
  //spinner.join();
  return 0;
}