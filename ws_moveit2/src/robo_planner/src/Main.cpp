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
  
  robot->SetGripper(std::make_shared<WzlPlanner::GripperMockup>("TestGripper"));
  
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
  //scene->AddSceneObject(gripperChangeStation, std::make_shared<WzlPlanner::Pose>(0, 10, 0));

  // clamping device jaws
  RCLCPP_INFO(node->get_logger(), "Initialize Clamping device jaw");
  auto clampingDeviceJaws = std::make_shared<WzlPlanner::SceneObjectClampingDeviceJaws>("ClampingDeviceJaw", 0, 1);
  //scene->AddSceneObject(clampingDeviceJaws, std::make_shared<WzlPlanner::Pose>(5, 0, 0));

  // clamping device elevation
  RCLCPP_INFO(node->get_logger(), "Initialize clamping device elevation");
  auto clampingDeviceElevation = std::make_shared<WzlPlanner::SceneObjectClampingDeviceJaws>("ClampingDeviceElavation", 2, 3);
  //scene->AddSceneObject(clampingDeviceElevation, std::make_shared<WzlPlanner::Pose>(5, 0, 0));

  // scanning tower
  RCLCPP_INFO(node->get_logger(), "Initialize visual scan tower");
  auto scanningTower = std::make_shared<WzlPlanner::SceneObjectVisualScanTower>("VisualScanTower");
  //scene->AddSceneObject(scanningTower, std::make_shared<WzlPlanner::Pose>(5, 5, 0));

  // carrier
  RCLCPP_INFO(node->get_logger(), "Initialize carrier");
  auto carrier = std::make_shared<WzlPlanner::SceneObjectCarrier>("Carrier");
  //scene->AddSceneObject(carrier, std::make_shared<WzlPlanner::Pose>(-5, 0, 0));

  RCLCPP_INFO(node->get_logger(), "Robot scheduler cell environment initialization end.");

}

void PickAndPlaceTest()
{
  auto node = WzlPlanner::ObjectContainer::Get()->GetNode();
  
  RCLCPP_INFO(node->get_logger(), "Initialize Pick & Place test.");
  
  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceDummy>();
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);
  
  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("RoboGripper", 0, 1);

  robot->SetGripper(gripper);

  RCLCPP_INFO(node->get_logger(), "Initialize Task Pick & Place");

  auto taskPickAndPlace = std::make_shared<WzlPlanner::TaskPickAndPlace>();
  auto taskPick = taskPickAndPlace->GetTaskPick();
  auto taskPlace = taskPickAndPlace->GetTaskPlace();

  auto taskPickAndPlace2 = std::make_shared<WzlPlanner::TaskPickAndPlace>();
  auto taskPick2 = taskPickAndPlace2->GetTaskPick();
  auto taskPlace2 = taskPickAndPlace2->GetTaskPlace();
  
  auto taskSetRobotSpeed = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>();
  taskSetRobotSpeed->SetValue(0.3);
  

  // use just absolute poses
  
  /*
  auto posePickApproach = std::make_shared<WzlPlanner::Pose>(0.30, -0.30, 0.4, M_PI, 0, 0);
  auto posePickExceute = std::make_shared<WzlPlanner::Pose>(0.30, -0.30, 0.3, M_PI, 0, 0);
  auto posePickEnd = std::make_shared<WzlPlanner::Pose>(0.30, -0.30, 0.4, M_PI, 0, 0);

  auto posePlaceApproach = std::make_shared<WzlPlanner::Pose>(0.5, -0.5, 0.4, M_PI, 0, 0);
  auto posePlaceExceute = std::make_shared<WzlPlanner::Pose>(0.5, -0.5, 0.3, M_PI, 0, 0);
  auto posePlaceEnd = std::make_shared<WzlPlanner::Pose>(0.5, -0.5, 0.4, M_PI, 0, 0);

  auto posePickApproach2 = std::make_shared<WzlPlanner::Pose>(-0.30, -0.30, 0.4, M_PI, 0, 0);
  auto posePickExceute2 = std::make_shared<WzlPlanner::Pose>(-0.30, -0.30, 0.3, M_PI, 0, 0);
  auto posePickEnd2 = std::make_shared<WzlPlanner::Pose>(-0.30, -0.30, 0.4, M_PI, 0, 0);

  auto posePlaceApproach2 = std::make_shared<WzlPlanner::Pose>(-0.5, -0.5, 0.4, M_PI, 0, 0);
  auto posePlaceExceute2 = std::make_shared<WzlPlanner::Pose>(-0.5, -0.5, 0.3, M_PI, 0, 0);
  auto posePlaceEnd2 = std::make_shared<WzlPlanner::Pose>(-0.5, -0.5, 0.4, M_PI, 0, 0);
  */

  // BEMI 1

  auto offset_z = 0.58 -0.182;

  auto posePickApproach = std::make_shared<WzlPlanner::Pose>(0.0934, 0.61288, -0.023 + offset_z, M_PI, 0, 0);
  auto posePickExceute = std::make_shared<WzlPlanner::Pose>(0.0934, 0.61288, 0.123 + offset_z, M_PI, 0, 0);
  auto posePickEnd = std::make_shared<WzlPlanner::Pose>(0.0934, 0.61288, -0.023 + offset_z, M_PI, 0, 0);

  auto posePlaceApproach = std::make_shared<WzlPlanner::Pose>(0.5, 0.5, 0.2 + offset_z, M_PI, 0, 0);
  auto posePlaceExceute = std::make_shared<WzlPlanner::Pose>(0.5, 0.5, 0.1 + offset_z, M_PI, 0, 0);
  auto posePlaceEnd = std::make_shared<WzlPlanner::Pose>(0.5, 0.5, 0.2 + offset_z, M_PI, 0, 0);

  // BEMI 2
  auto posePickApproach2 = std::make_shared<WzlPlanner::Pose>(0.0934, 0.023, 0.08 + offset_z, M_PI, 0, 0);
  auto posePickExceute2 = std::make_shared<WzlPlanner::Pose>(0.0934, 0.123, 0.18 + offset_z, M_PI, 0, 0);
  auto posePickEnd2 = std::make_shared<WzlPlanner::Pose>(0.0934, 0.023, 0.08 + offset_z, M_PI, 0, 0);

  auto posePlaceApproach2 = std::make_shared<WzlPlanner::Pose>(0.7, 0.2, 0.4 + offset_z, M_PI, 0, 0);
  auto posePlaceExceute2 = std::make_shared<WzlPlanner::Pose>(0.7, 0.1, 0.3 + offset_z, M_PI, 0, 0);
  auto posePlaceEnd2 = std::make_shared<WzlPlanner::Pose>(0.7, 0.7, 0.2 + offset_z, M_PI, 0, 0);

  
/*
  auto posePickApproach = std::make_shared<WzlPlanner::Pose>(-0.39255, -0.611, 0.4, M_PI, 0, 0);
  auto posePickExceute = std::make_shared<WzlPlanner::Pose>(-0.39255, -0.611, 0.2, M_PI, 0, 0);
  auto posePickEnd = std::make_shared<WzlPlanner::Pose>(-0.39255, -0.611, 0.4, M_PI, 0, 0);

  auto posePlaceApproach = std::make_shared<WzlPlanner::Pose>(-0.393, -0.611, 0.4, M_PI, 0, 0);
  auto posePlaceExceute = std::make_shared<WzlPlanner::Pose>(-0.393, -0.611, 0.2, M_PI, 0, 0);
  auto posePlaceEnd = std::make_shared<WzlPlanner::Pose>(-0.393, -0.611, 0.4, M_PI, 0, 0);
*/
  /*
  // use relative movements
  auto posePickApproach = std::make_shared<WzlPlanner::Pose>(0.30, 0.30, 0.3, M_PI, 0, 0);
  auto posePickExceute = std::make_shared<WzlPlanner::Pose>(0.0, 0.0, -0.1, 0, 0, 0);
  auto posePickEnd = std::make_shared<WzlPlanner::Pose>(0.0, 0.0, 0.1, 0, 0, 0);

  auto posePlaceApproach = std::make_shared<WzlPlanner::Pose>(0.5, 0.5, 0.3, M_PI, 0, 0);
  auto posePlaceExceute = std::make_shared<WzlPlanner::Pose>(0.0, 0.0, -0.1, 0, 0, 0);
  auto posePlaceEnd = std::make_shared<WzlPlanner::Pose>(0.0, 0.0, 0.1, 0, 0, 0);
  */

  taskPickAndPlace->SetId("TestTask");

  taskPick->GetTaskMoveToPoseApproach()->SetTargetPose(posePickApproach)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPick->GetTaskMoveToPosePick()->SetTargetPose(posePickExceute)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPick->GetTaskMoveToEnd()->SetTargetPose(posePickEnd)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);

  taskPlace->GetTaskMoveToPoseApproach()->SetTargetPose(posePlaceApproach)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPlace->GetTaskMoveToPosePlace()->SetTargetPose(posePlaceExceute)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPlace->GetTaskMoveToEnd()->SetTargetPose(posePlaceEnd)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);

  taskPickAndPlace2->SetId("TestTask2");

  taskPick2->GetTaskMoveToPoseApproach()->SetTargetPose(posePickApproach2)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPick2->GetTaskMoveToPosePick()->SetTargetPose(posePickExceute2)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPick2->GetTaskMoveToEnd()->SetTargetPose(posePickEnd2)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);

  taskPlace2->GetTaskMoveToPoseApproach()->SetTargetPose(posePlaceApproach2)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPlace2->GetTaskMoveToPosePlace()->SetTargetPose(posePlaceExceute2)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPlace2->GetTaskMoveToEnd()->SetTargetPose(posePlaceEnd2)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);



  RCLCPP_INFO(node->get_logger(), "Execute Task Pick & Place");
  taskSetRobotSpeed->Execute();

  while (true)
  {
    taskPickAndPlace->Execute();
    taskPickAndPlace2->Execute();
  }
  

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