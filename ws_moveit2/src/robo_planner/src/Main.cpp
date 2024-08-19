#include <rclcpp/rclcpp.hpp>
#include "tf2_eigen/tf2_eigen.hpp"

#include "../include/Pose.h"
#include "../include/SceneObjects/SceneObject.h"
#include "../include/Scene.h"

#include "../include/IoInterface.h"
#include "../include/ObjectContainer.h"

#include "../include/Tasks/TaskInclude.h"
#include "../include/OpcUaData.h"

#include <math.h>
#include <memory>
#include <chrono>

using namespace std::chrono_literals;


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
  auto useOpcua = false;
  
  RCLCPP_INFO(node->get_logger(), "Initialize Pick & Place test.");
  
  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);
  
  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("RoboGripper", 0, 1);

  robot->SetGripper(gripper);

  RCLCPP_INFO(node->get_logger(), "Initialize Task Pick & Place");

  auto taskIoBemi1Open = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi1WriteAuf());
  taskIoBemi1Open->SetId("taskIoBemi1Open");

  auto taskIoBemi1Close = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi1WriteZu());
  taskIoBemi1Close->SetId("taskIoBemi1Close");

  auto taskIoBemi2Open = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi2WriteAuf());
    taskIoBemi2Open->SetId("taskIoBemi2Open");

  auto taskIoBemi2Close = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi2WriteZu());
    taskIoBemi2Close->SetId("taskIoBemi2Close");

  auto taskIoGripperOpen = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_GreiferWriteAuf());
    taskIoGripperOpen->SetId("taskIoGripperOpen");

  auto taskIoGripperClose = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_GreiferWritZu());
    taskIoGripperClose->SetId("taskIoGripperClose");


  auto taskPickAndPlace = std::make_shared<WzlPlanner::TaskPickAndPlace>();
  auto taskPick = taskPickAndPlace->GetTaskPick();
  auto taskPlace = taskPickAndPlace->GetTaskPlace();

  auto taskPickAndPlace2 = std::make_shared<WzlPlanner::TaskPickAndPlace>();
  auto taskPick2 = taskPickAndPlace2->GetTaskPick();
  auto taskPlace2 = taskPickAndPlace2->GetTaskPlace();
  
  auto taskSetRobotSpeed = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>();
  taskSetRobotSpeed->SetValue(0.3);
  

  // use just absolute poses

  // BEMI 1
  auto posePickApproach = std::make_shared<WzlPlanner::Pose>(0.48967, 0.15907, 0.45, M_PI, 0, 0);
  auto posePickExceute = std::make_shared<WzlPlanner::Pose>(0.48967, 0.15907, 0.253, M_PI, 0, 0);
  auto posePickEnd = std::make_shared<WzlPlanner::Pose>(0.48967, 0.15907, 0.45, M_PI, 0, 0);

  auto posePlaceApproach = std::make_shared<WzlPlanner::Pose>(-0.099852, 0.646, 0.45, M_PI, 0, 0);
  auto posePlaceExceute = std::make_shared<WzlPlanner::Pose>(-0.099852, 0.646, 0.31, M_PI, 0, 0);
  auto posePlaceEnd = std::make_shared<WzlPlanner::Pose>(-0.099852, 0.646, 0.45, M_PI, 0, 0);

  // perform on bemi 1 again
  auto posePickApproach2 = std::make_shared<WzlPlanner::Pose>(-0.099852, 0.646, 0.45, M_PI, 0, 0);
  auto posePickExceute2 = std::make_shared<WzlPlanner::Pose>(-0.099852, 0.646, 0.31, M_PI, 0, 0);
  auto posePickEnd2 = std::make_shared<WzlPlanner::Pose>(-0.099852, 0.646, 0.45, M_PI, 0, 0);

  auto posePlaceApproach2 = std::make_shared<WzlPlanner::Pose>(0.48967, 0.15907, 0.45, M_PI, 0, 0);
  auto posePlaceExceute2 = std::make_shared<WzlPlanner::Pose>(0.48967, 0.15907, 0.253, M_PI, 0, 0);
  auto posePlaceEnd2 = std::make_shared<WzlPlanner::Pose>(0.48967, 0.15907, 0.45, M_PI, 0, 0);

  // BEMI 2
  // misc
  auto taskWait = std::make_shared<WzlPlanner::TaskWait>();
  taskWait->time_ = 1000ms;

  taskPickAndPlace->SetId("TestTask");

  taskPick->GetTaskMoveToPoseApproach()->SetTargetPose(posePickApproach)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPick->GetTaskMoveToPosePick()->SetTargetPose(posePickExceute)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPick->GetTaskMoveToEnd()->SetTargetPose(posePickEnd)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);

  taskPlace->GetTaskMoveToPoseApproach()->SetTargetPose(posePlaceApproach)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPlace->GetTaskMoveToPosePlace()->SetTargetPose(posePlaceExceute)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPlace->GetTaskMoveToEnd()->SetTargetPose(posePlaceEnd)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);

  taskPickAndPlace2->SetId("TestTask2");

  taskPick2->GetTaskMoveToPoseApproach()->SetTargetPose(posePickApproach2)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPick2->GetTaskMoveToPosePick()->SetTargetPose(posePickExceute2)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPick2->GetTaskMoveToEnd()->SetTargetPose(posePickEnd2)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);

  taskPlace2->GetTaskMoveToPoseApproach()->SetTargetPose(posePlaceApproach2)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPlace2->GetTaskMoveToPosePlace()->SetTargetPose(posePlaceExceute2)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPlace2->GetTaskMoveToEnd()->SetTargetPose(posePlaceEnd2)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);



  RCLCPP_INFO(node->get_logger(), "Execute Task Pick & Place");
  taskSetRobotSpeed->Execute();

  // setup custom task
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  
  taskList->AddTask(taskPick->GetTaskMoveToPoseApproach());
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPick->GetTaskMoveToPosePick());
  taskList->AddTask(taskIoGripperOpen);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPick->GetTaskMoveToEnd());

  taskList->AddTask(taskPlace->GetTaskMoveToPoseApproach());
  taskList->AddTask(taskIoBemi1Open);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPlace->GetTaskMoveToPosePlace());
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskIoBemi1Close);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskIoBemi1Open);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskIoBemi1Close);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPlace->GetTaskMoveToEnd());

  taskList->AddTask(taskPick2->GetTaskMoveToPoseApproach());
  taskList->AddTask(taskIoBemi1Open);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPick2->GetTaskMoveToPosePick());
  taskList->AddTask(taskIoGripperOpen);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPick2->GetTaskMoveToEnd());

  taskList->AddTask(taskPlace2->GetTaskMoveToPoseApproach());
  taskList->AddTask(taskPlace2->GetTaskMoveToPosePlace());
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPlace2->GetTaskMoveToEnd());

  while (true)
  {
    taskList->Execute();
    rclcpp::spin_some(node);
  }
  

  RCLCPP_INFO(node->get_logger(), "Excecution successful");

}


void TaskRotationTest()
{
  auto node = WzlPlanner::ObjectContainer::Get()->GetNode();
  auto useOpcua = false;
  
  RCLCPP_INFO(node->get_logger(), "Initialize Rotation test.");
  
  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceDummy>();
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);
  
  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("RoboGripper", 0, 1);

  robot->SetGripper(gripper);

  RCLCPP_INFO(node->get_logger(), "Initialize Rotation task");

  auto taskIoBemi1Open = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi1WriteAuf());

  auto taskIoBemi1Close = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi1WriteZu());

  auto taskIoBemi2Open = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi2WriteAuf());

  auto taskIoBemi2Close = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi2WriteZu());

  auto taskIoGripperOpen = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_GreiferWriteAuf());

  auto taskIoGripperClose = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_GreiferWritZu());

  auto task1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto task2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto task3 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto task4 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  
  auto taskSetRobotSpeed = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>();
  taskSetRobotSpeed->SetValue(1.0);

  double rotX = M_PI;
  double rotY = 0;
  double rotZ = 0; 

  double posStartZ = 416.63;
  double posEndZ = 0.44686;

  double stationYApproach = -0.40759;
  double stationYExecute = -0.55759;
  double stationX1 = -0.19138;
  double stationX2 = 0.13816;
  double stationX3 = 0.29433;
  double stationX4 = -0.016;


  // Station 1
  auto pose1 = std::make_shared<WzlPlanner::Pose>(stationX1, stationYApproach, posStartZ, rotX, rotY, 0);
  auto pose2 = std::make_shared<WzlPlanner::Pose>(stationX1, stationYApproach, posStartZ, rotX, rotY, M_PI * 0.5);
  auto pose3 = std::make_shared<WzlPlanner::Pose>(stationX1, stationYApproach, posStartZ, rotX, rotY, M_PI * 1.0);
  auto pose4 = std::make_shared<WzlPlanner::Pose>(stationX1, stationYApproach, posStartZ, rotX, rotY, M_PI * 1.5);


  // misc
  auto taskWait = std::make_shared<WzlPlanner::TaskWait>();
  taskWait->time_ = 500ms;

  task1->SetTargetPose(pose1)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  task2->SetTargetPose(pose2)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  task3->SetTargetPose(pose3)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  task4->SetTargetPose(pose4)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
 


  RCLCPP_INFO(node->get_logger(), "Execute Task Pick & Place");
  taskSetRobotSpeed->Execute();

  // setup custom task
  auto taskList = std::make_shared<WzlPlanner::TaskList>();
  taskList->AddTask(task1);
  taskList->AddTask(task2);
  taskList->AddTask(task3);
  taskList->AddTask(task4);

  while (true)
  {
    taskList->Execute();
    rclcpp::spin_some(node);
  }
  

  RCLCPP_INFO(node->get_logger(), "Excecution successful");

}



void TaskChangingStationTest()
{
  auto node = WzlPlanner::ObjectContainer::Get()->GetNode();
  auto useOpcua = false;
  
  RCLCPP_INFO(node->get_logger(), "Initialize Pick & Place test.");
  
  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceDummy>();
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);
  
  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("RoboGripper", 0, 1);

  robot->SetGripper(gripper);

  RCLCPP_INFO(node->get_logger(), "Initialize Task Pick & Place");

  auto taskIoBemi1Open = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi1WriteAuf());

  auto taskIoBemi1Close = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi1WriteZu());

  auto taskIoBemi2Open = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi2WriteAuf());

  auto taskIoBemi2Close = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi2WriteZu());

  auto taskIoGripperOpen = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_GreiferWriteAuf());

  auto taskIoGripperClose = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_GreiferWritZu());

  auto taskPickAndPlace = std::make_shared<WzlPlanner::TaskPickAndPlace>();
  auto taskPick = taskPickAndPlace->GetTaskPick();
  auto taskPlace = taskPickAndPlace->GetTaskPlace();

  auto taskPickAndPlace2 = std::make_shared<WzlPlanner::TaskPickAndPlace>();
  auto taskPick2 = taskPickAndPlace2->GetTaskPick();
  auto taskPlace2 = taskPickAndPlace2->GetTaskPlace();

  auto taskPickAndPlace3 = std::make_shared<WzlPlanner::TaskPickAndPlace>();
  auto taskPick3 = taskPickAndPlace3->GetTaskPick();
  auto taskPlace3 = taskPickAndPlace3->GetTaskPlace();

  auto taskPickAndPlace4 = std::make_shared<WzlPlanner::TaskPickAndPlace>();
  auto taskPick4 = taskPickAndPlace4->GetTaskPick();
  auto taskPlace4 = taskPickAndPlace4->GetTaskPlace();
  
  auto taskSetRobotSpeed = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>();
  taskSetRobotSpeed->SetValue(0.1);
  
/*
  // Station 1
  auto posePickApproach = std::make_shared<WzlPlanner::Pose>(-0.19138, -0.40759, 0.41686, 2.214, 2.238, 0.011);
  auto posePickExceute = std::make_shared<WzlPlanner::Pose>(-0.19138, -0.55759, 0.41686, 2.214, 2.238, 0.011);
  auto posePickEnd = std::make_shared<WzlPlanner::Pose>(-0.19138, -0.55759, 0.44686, 2.214, 2.238, 0.011);

  auto posePlaceApproach = std::make_shared<WzlPlanner::Pose>(-0.19138, -0.55759, 0.44686, 2.214, 2.238, 0.011);
  auto posePlaceExceute = std::make_shared<WzlPlanner::Pose>(-0.19138, -0.55759, 0.41686, 2.214, 2.238, 0.011);
  auto posePlaceEnd = std::make_shared<WzlPlanner::Pose>(-0.19138, -0.40759, 0.41686, 2.214, 2.238, 0.011);

  // Station 2
  auto posePickApproach2 = std::make_shared<WzlPlanner::Pose>(0.13816, -0.40454, 0.41118, 2.253, 2.192, 0);
  auto posePickExceute2 = std::make_shared<WzlPlanner::Pose>(0.13816, -0.55454, 0.41118, 2.253, 2.192, 0);
  auto posePickEnd2 = std::make_shared<WzlPlanner::Pose>(0.13816, -0.55454, 0.44118, 2.253, 2.192, 0);

  auto posePlaceApproach2 = std::make_shared<WzlPlanner::Pose>(0.13816, -0.55454, 0.44118, 2.253, 2.192, 0);
  auto posePlaceExceute2 = std::make_shared<WzlPlanner::Pose>(0.13816, -0.55454, 0.41118, 2.253, 2.192, 0);
  auto posePlaceEnd2 = std::make_shared<WzlPlanner::Pose>(0.13816, -0.40454, 0.41118, 2.253, 2.192, 0);

  // Station 3
  auto posePickApproach3 = std::make_shared<WzlPlanner::Pose>(0.29433, -0.40067, 0.41014, 2.251, 2.191, 0);
  auto posePickExceute3 = std::make_shared<WzlPlanner::Pose>(0.29433, -0.55067, 0.41014, 2.251, 2.191, 0);
  auto posePickEnd3 = std::make_shared<WzlPlanner::Pose>(0.29433, -0.55067, 0.44014, 2.251, 2.191, 0);

  auto posePlaceApproach3 = std::make_shared<WzlPlanner::Pose>(0.29433, -0.55067, 0.44014, 2.251, 2.191, 0);
  auto posePlaceExceute3 = std::make_shared<WzlPlanner::Pose>(0.29433, -0.55067, 0.41014, 2.251, 2.191, 0);
  auto posePlaceEnd3 = std::make_shared<WzlPlanner::Pose>(0.29433, -0.40067, 0.41014, 2.251, 2.191, 0);

  // Station 4
  auto posePickApproach4 = std::make_shared<WzlPlanner::Pose>(-0.016, -0.40351, 0.41438, 2.346, 2.091, 0.001);
  auto posePickExceute4 = std::make_shared<WzlPlanner::Pose>(-0.016, -0.55351, 0.41438, 2.346, 2.091, 0.001);
  auto posePickEnd4 = std::make_shared<WzlPlanner::Pose>(-0.016, -0.55351, 0.44438, 2.346, 2.091, 0.001);

  auto posePlaceApproach4 = std::make_shared<WzlPlanner::Pose>(-0.016, -0.55351, 0.44438, 2.346, 2.091, 0.001);
  auto posePlaceExceute4 = std::make_shared<WzlPlanner::Pose>(-0.016, -0.55351, 0.41438, 2.346, 2.091, 0.001);
  auto posePlaceEnd4 = std::make_shared<WzlPlanner::Pose>(-0.016, -0.40351, 0.41438, 2.346, 2.091, 0.001);
*/

  double rotX = M_PI;
  double rotY = 0;
  double rotZ = M_PI * -0.5; 

  double posStartZ = 0.41663;
  double posEndZ = 0.44686;

  double stationYApproach = -0.40759;
  //double stationYExecute = -0.55759;
  double stationYExecute = -0.54759;
  double stationX1 = -0.19138;
  double stationX2 = 0.13816;
  double stationX3 = 0.29433;
  double stationX4 = -0.016;


  // Station 1
  auto posePickApproach = std::make_shared<WzlPlanner::Pose>(stationX1, stationYApproach, posStartZ, rotX, rotY, rotZ);
  auto posePickExceute = std::make_shared<WzlPlanner::Pose>(stationX1, stationYExecute, posStartZ, rotX, rotY, rotZ);
  auto posePickEnd = std::make_shared<WzlPlanner::Pose>(stationX1, stationYExecute, posEndZ, rotX, rotY, rotZ);

  auto posePlaceApproach = std::make_shared<WzlPlanner::Pose>(stationX1, stationYExecute, posEndZ, rotX, rotY, rotZ);
  auto posePlaceExceute = std::make_shared<WzlPlanner::Pose>(stationX1, stationYExecute, posStartZ, rotX, rotY, rotZ);
  auto posePlaceEnd = std::make_shared<WzlPlanner::Pose>(stationX1, stationYApproach, posStartZ, rotX, rotY, rotZ);

  // Station 2
  auto posePickApproach2 = std::make_shared<WzlPlanner::Pose>(stationX2, stationYApproach, posStartZ, rotX, rotY, rotZ);
  auto posePickExceute2 = std::make_shared<WzlPlanner::Pose>(stationX2, stationYExecute, posStartZ, rotX, rotY, rotZ);
  auto posePickEnd2 = std::make_shared<WzlPlanner::Pose>(stationX2, stationYExecute, posEndZ, rotX, rotY, rotZ);

  auto posePlaceApproach2 = std::make_shared<WzlPlanner::Pose>(stationX2, stationYExecute, posEndZ, rotX, rotY, rotZ);
  auto posePlaceExceute2 = std::make_shared<WzlPlanner::Pose>(stationX2, stationYExecute, posStartZ, rotX, rotY, rotZ);
  auto posePlaceEnd2 = std::make_shared<WzlPlanner::Pose>(stationX2, stationYApproach, posStartZ, rotX, rotY, rotZ);

  // Station 3
  auto posePickApproach3 = std::make_shared<WzlPlanner::Pose>(stationX3, stationYApproach, posStartZ, rotX, rotY, rotZ);
  auto posePickExceute3 = std::make_shared<WzlPlanner::Pose>(stationX3, stationYExecute, posStartZ, rotX, rotY, rotZ);
  auto posePickEnd3 = std::make_shared<WzlPlanner::Pose>(stationX3, stationYExecute, posEndZ, rotX, rotY, rotZ);

  auto posePlaceApproach3 = std::make_shared<WzlPlanner::Pose>(stationX3, stationYExecute, posEndZ, rotX, rotY, rotZ);
  auto posePlaceExceute3 = std::make_shared<WzlPlanner::Pose>(stationX3, stationYExecute, posStartZ, rotX, rotY, rotZ);
  auto posePlaceEnd3 = std::make_shared<WzlPlanner::Pose>(stationX3, stationYApproach, posStartZ, rotX, rotY, rotZ);

  // Station 4
  auto posePickApproach4 = std::make_shared<WzlPlanner::Pose>(stationX4, stationYApproach, posStartZ, rotX, rotY, rotZ);
  auto posePickExceute4 = std::make_shared<WzlPlanner::Pose>(stationX4, -stationYExecute, posStartZ, rotX, rotY, rotZ);
  auto posePickEnd4 = std::make_shared<WzlPlanner::Pose>(stationX4, stationYExecute, posEndZ, rotX, rotY, rotZ);

  auto posePlaceApproach4 = std::make_shared<WzlPlanner::Pose>(stationX4, stationYExecute, posEndZ, rotX, rotY, rotZ);
  auto posePlaceExceute4 = std::make_shared<WzlPlanner::Pose>(stationX4, stationYExecute, posStartZ, rotX, rotY, rotZ);
  auto posePlaceEnd4 = std::make_shared<WzlPlanner::Pose>(stationX4, stationYApproach, posStartZ, rotX, rotY, rotZ);

  // misc
  auto taskWait = std::make_shared<WzlPlanner::TaskWait>();
  taskWait->time_ = 500ms;
 

  taskPickAndPlace->SetId("TestTask");

  taskPick->GetTaskMoveToPoseApproach()->SetTargetPose(posePickApproach)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPick->GetTaskMoveToPosePick()->SetTargetPose(posePickExceute)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPick->GetTaskMoveToEnd()->SetTargetPose(posePickEnd)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);

  taskPlace->GetTaskMoveToPoseApproach()->SetTargetPose(posePlaceApproach)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPlace->GetTaskMoveToPosePlace()->SetTargetPose(posePlaceExceute)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPlace->GetTaskMoveToEnd()->SetTargetPose(posePlaceEnd)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);

  taskPickAndPlace2->SetId("TestTask2");

  taskPick2->GetTaskMoveToPoseApproach()->SetTargetPose(posePickApproach2)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPick2->GetTaskMoveToPosePick()->SetTargetPose(posePickExceute2)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPick2->GetTaskMoveToEnd()->SetTargetPose(posePickEnd2)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);

  taskPlace2->GetTaskMoveToPoseApproach()->SetTargetPose(posePlaceApproach2)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPlace2->GetTaskMoveToPosePlace()->SetTargetPose(posePlaceExceute2)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPlace2->GetTaskMoveToEnd()->SetTargetPose(posePlaceEnd2)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);


  taskPickAndPlace3->SetId("TestTask3");

  taskPick3->GetTaskMoveToPoseApproach()->SetTargetPose(posePickApproach3)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPick3->GetTaskMoveToPosePick()->SetTargetPose(posePickExceute3)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPick3->GetTaskMoveToEnd()->SetTargetPose(posePickEnd3)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);

  taskPlace3->GetTaskMoveToPoseApproach()->SetTargetPose(posePlaceApproach3)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPlace3->GetTaskMoveToPosePlace()->SetTargetPose(posePlaceExceute3)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPlace3->GetTaskMoveToEnd()->SetTargetPose(posePlaceEnd3)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);

  taskPickAndPlace4->SetId("TestTask4");

  taskPick4->GetTaskMoveToPoseApproach()->SetTargetPose(posePickApproach4)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPick4->GetTaskMoveToPosePick()->SetTargetPose(posePickExceute4)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPick4->GetTaskMoveToEnd()->SetTargetPose(posePickEnd4)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);

  taskPlace4->GetTaskMoveToPoseApproach()->SetTargetPose(posePlaceApproach4)->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskPlace4->GetTaskMoveToPosePlace()->SetTargetPose(posePlaceExceute4)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskPlace4->GetTaskMoveToEnd()->SetTargetPose(posePlaceEnd4)->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);



  RCLCPP_INFO(node->get_logger(), "Execute Task Pick & Place");
  taskSetRobotSpeed->Execute();

  // setup custom task
  auto taskList = std::make_shared<WzlPlanner::TaskList>();
  taskList->AddTask(taskPickAndPlace);
  taskList->AddTask(taskPickAndPlace2);
  taskList->AddTask(taskPickAndPlace3);
  taskList->AddTask(taskPickAndPlace4);

  while (true)
  {
    taskList->Execute();
    rclcpp::spin_some(node);
    //taskPickAndPlace->Execute();
    //taskPickAndPlace2->Execute();
    //taskPickAndPlace3->Execute();
    //taskPickAndPlace4->Execute();
  }
  

  RCLCPP_INFO(node->get_logger(), "Excecution successful");

}

void OpcuaTaskTest(const std::shared_ptr<rclcpp::Node> node)
{
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


  
  RCLCPP_INFO(node->get_logger(), "Initialize Pick & Place test.");
  

  RCLCPP_INFO(node->get_logger(), "Iitialize Opcua Task test");

  auto taskIoBemi1Open = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi1WriteAuf());
  taskIoBemi1Open->SetId("taskIoBemi1Open");

  auto taskIoBemi1Close = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi1WriteZu());
  taskIoBemi1Close->SetId("taskIoBemi1Close");

  auto taskIoBemi2Open = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi2WriteAuf());
    taskIoBemi2Open->SetId("taskIoBemi2Open");

  auto taskIoBemi2Close = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_Bemi2WriteZu());
    taskIoBemi2Close->SetId("taskIoBemi2Close");

  auto taskIoGripperOpen = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_GreiferWriteAuf());
    taskIoGripperOpen->SetId("taskIoGripperOpen");

  auto taskIoGripperClose = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_GreiferWritZu());
    taskIoGripperClose->SetId("taskIoGripperClose");

  // misc
  auto taskWait = std::make_shared<WzlPlanner::TaskWait>();
  taskWait->SetId("taskWait");
  taskWait->time_ = 1000ms;

  // setup custom task
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  // opcua test
  taskList->SetId("OpcuaTaskList");
  taskList->AddTask(taskIoBemi1Open);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskIoGripperOpen);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskIoBemi1Close);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);

  RCLCPP_INFO(node->get_logger(), "Excecution of tasklist");

  while (true)
  {
    taskList->Execute();
    rclcpp::spin_some(node);
  }
  

  RCLCPP_INFO(node->get_logger(), "Excecution successful");

}


int main(int argc, char* argv[])
{
  // Initialize ROS and create the Node
  std::cout << "Initialize robo planner node" << std::endl;
  rclcpp::init(argc, argv);
  
  //auto trWorld = std::make_shared<WzlPlanner::Transform>("world");
  
  rclcpp::sleep_for(500ms);
  
  auto const node = std::make_shared<rclcpp::Node>(
      "robot_planer", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));
  
  RCLCPP_DEBUG(node->get_logger(), "My log message %d", 4);

  CreateCell(node);
  //PickAndPlaceTest();
  //TaskRotationTest();

  rclcpp::sleep_for(2000ms);
  TaskChangingStationTest();
  //OpcuaTaskTest(node);

  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();
  //spinner.join();
  return 0;
}