#include <rclcpp/rclcpp.hpp>
#include "tf2_eigen/tf2_eigen.hpp"

#include "../include/Pose.h"
#include "../include/SceneObjects/SceneObject.h"
#include "../include/Scene.h"

#include "../include/IoInterface.h"
#include "../include/ObjectContainer.h"

#include "../include/Tasks/TaskInclude.h"

#include <math.h>
#include <memory>



int TransformTest() {

  std::shared_ptr<WzlPlanner::Transform> trWorld = std::make_shared<WzlPlanner::Transform>("world");
  std::shared_ptr<WzlPlanner::Transform> trStation = std::make_shared<WzlPlanner::Transform>("station");
  trStation->SetParent(trWorld);

  std::shared_ptr<WzlPlanner::Transform> trSlot1 = std::make_shared<WzlPlanner::Transform>("slot1");
  trSlot1->SetParent(trStation);

  std::shared_ptr<WzlPlanner::Transform> trSlot2 = std::make_shared<WzlPlanner::Transform>("slot2");
  trSlot2->SetParent(trStation);

  std::shared_ptr<WzlPlanner::Transform> trSlot3 = std::make_shared<WzlPlanner::Transform>("slot3");
  trSlot3->SetParent(trStation);

  trStation->GetPoseRelative()->SetPositionXYZ(10, 0, 0);
  trStation->GetPoseRelative()->SetRotationZ(M_PI_2);
  trSlot1->GetPoseRelative()->SetPositionXYZ(0, -1, 2);
  trSlot2->GetPoseRelative()->SetPositionXYZ(0, 0, 2);
  trSlot3->GetPoseRelative()->SetPositionXYZ(0, 1, 2);

  trWorld->Update();
  trWorld->Print();

  return 0;
}

void CreateCell(const std::shared_ptr<rclcpp::Node> node)
{
  //auto robot = std::make_shared<WzlPlanner::RobotDummy>(node);
  auto robot = std::make_shared<WzlPlanner::RobotUR>(node);
  auto scene = std::make_shared<WzlPlanner::Scene>(robot, node);
  auto ioInterfaceOpcUa = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  
  RCLCPP_INFO(node->get_logger(), "Robot scheduler cell environment initialization start.");
  RCLCPP_INFO(node->get_logger(), "Initialize ObjectContainer");

  WzlPlanner::ObjectContainer::Get()->Initialize(
    ioInterfaceOpcUa, 
    robot, 
    scene,
    node);

  // gripper change station
  RCLCPP_INFO(node->get_logger(), "Initialize Gripper change station");
  auto gripperChangeStation = std::make_shared<WzlPlanner::SceneObjectGripperChangeStation>("GripperChangeStation");
  scene->AddSceneObject(gripperChangeStation, std::make_shared<WzlPlanner::Pose>(0, 10, 0));

  // clamping device jaws
  RCLCPP_INFO(node->get_logger(), "Initialize Clamping device jaw");
  auto clampingDeviceJaws = std::make_shared<WzlPlanner::SceneObjectClampingDeviceJaws>("ClampingDeviceJaw", 0, 1);
  scene->AddSceneObject(clampingDeviceJaws, std::make_shared<WzlPlanner::Pose>(5, 0, 0));

  // clamping device elevation
  RCLCPP_INFO(node->get_logger(), "Initialize clamping device elevation");
  auto clampingDeviceElevation = std::make_shared<WzlPlanner::SceneObjectClampingDeviceJaws>("ClampingDeviceElavation", 2, 3);
  scene->AddSceneObject(clampingDeviceElevation, std::make_shared<WzlPlanner::Pose>(5, 0, 0));

  // scanning tower
  RCLCPP_INFO(node->get_logger(), "Initialize visual scan tower");
  auto scanningTower = std::make_shared<WzlPlanner::SceneObjectVisualScanTower>("VisualScanTower");
  scene->AddSceneObject(scanningTower, std::make_shared<WzlPlanner::Pose>(5, 5, 0));

  // carrier
  RCLCPP_INFO(node->get_logger(), "Initialize carrier");
  auto carrier = std::make_shared<WzlPlanner::SceneObjectCarrier>("Carrier");
  scene->AddSceneObject(carrier, std::make_shared<WzlPlanner::Pose>(-5, 0, 0));

  RCLCPP_INFO(node->get_logger(), "Robot scheduler cell environment initialization end.");
}

void PickAndPlaceTest()
{
  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceDummy>();
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);
  auto node = WzlPlanner::ObjectContainer::Get()->GetNode();
  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("RoboGripper", 0, 1);

  robot->SetGripper(gripper);

  RCLCPP_INFO(node->get_logger(), "Initialize Task Pick & Place");

  auto taskPickAndPlace = std::make_shared<WzlPlanner::TaskPickAndPlace>();
  auto taskPick = taskPickAndPlace->GetTaskPick();
  auto taskPlace = taskPickAndPlace->GetTaskPlace();
  /*
  auto posePickApproach = std::make_shared<WzlPlanner::Pose>(10, 10, 2);
  auto posePickExceute = std::make_shared<WzlPlanner::Pose>(10, 10, 0);
  auto posePickEnd = std::make_shared<WzlPlanner::Pose>(10, 10, 2);

  auto posePlaceApproach = std::make_shared<WzlPlanner::Pose>(5, 5, 2);
  auto posePlaceExceute = std::make_shared<WzlPlanner::Pose>(5, 5, 0);
  auto posePlaceEnd = std::make_shared<WzlPlanner::Pose>(5, 5, 2);
*/



  auto posePickApproach = std::make_shared<WzlPlanner::Pose>(0.30, 0.30, 0.3, M_PI, 0, 0);
  auto posePickExceute = std::make_shared<WzlPlanner::Pose>(0.0, 0.0, -0.1, 0, 0, 0);
  auto posePickEnd = std::make_shared<WzlPlanner::Pose>(0.0, 0.0, 0.1, 0, 0, 0);

  auto posePlaceApproach = std::make_shared<WzlPlanner::Pose>(0.5, 0.5, 0.3, M_PI, 0, 0);
  auto posePlaceExceute = std::make_shared<WzlPlanner::Pose>(0.0, 0.0, -0.1, 0, 0, 0);
  auto posePlaceEnd = std::make_shared<WzlPlanner::Pose>(0.0, 0.0, 0.1, 0, 0, 0);
  taskPickAndPlace->SetId("TestTask");

  taskPick->GetTaskMoveToPoseApproach()->SetTargetPose(posePickApproach)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPick->GetTaskMoveToPosePick()->SetTargetPose(posePickExceute)->SetMoveType(WzlPlanner::RobotMoveType::RelativeCartesian);
  taskPick->GetTaskMoveToEnd()->SetTargetPose(posePlaceEnd)->SetMoveType(WzlPlanner::RobotMoveType::RelativeCartesian);

  taskPlace->GetTaskMoveToPoseApproach()->SetTargetPose(posePlaceApproach)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPlace->GetTaskMoveToPosePlace()->SetTargetPose(posePlaceExceute)->SetMoveType(WzlPlanner::RobotMoveType::RelativeCartesian);
  taskPlace->GetTaskMoveToEnd()->SetTargetPose(posePlaceEnd)->SetMoveType(WzlPlanner::RobotMoveType::RelativeCartesian);

  RCLCPP_INFO(node->get_logger(), "Execute Task Pick & Place");

  taskPickAndPlace->Execute();

  RCLCPP_INFO(node->get_logger(), "Excecution successful");

}

void OpcUaTest(const std::shared_ptr<rclcpp::Node> node)
{
  auto ioInterfaceOpcUa = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  auto testCall = ioInterfaceOpcUa->SetValueBool(0, 0);

  if (testCall)
  {
    RCLCPP_INFO(node->get_logger(), "OpcUa Test Call was successful.");
  }
  else 
  {
    RCLCPP_INFO(node->get_logger(), "OpcUa Test Call failed.");
  }
}

int main(int argc, char* argv[])
{
  // Initialize ROS and create the Node
  rclcpp::init(argc, argv);

  //auto trWorld = std::make_shared<WzlPlanner::Transform>("world");

  rclcpp::sleep_for(500ms);

  auto const node = std::make_shared<rclcpp::Node>(
      "robot_planer", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));
  
  RCLCPP_DEBUG(node->get_logger(), "My log message %d", 4);

  CreateCell(node);
  PickAndPlaceTest();
  //OpcUaTest(node);

  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();
  //spinner.join();
  return 0;
}