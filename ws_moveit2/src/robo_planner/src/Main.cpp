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


// The Changing station place task contains these steps:
// - 1.) Approach the changing station (PTP)
// - 2.) Drive in execution pose (Cartesian Movemment)
// - 3.) Lift up (Cartesian movement)
// - 4.) Drive back (Cartesian movement)
// - 5.) Drop down into start position (Cartesian movement)
std::shared_ptr<WzlPlanner::TaskList> GetChangingStationTaskPlace(int stationIndex)
{
  if (stationIndex < 1 || stationIndex > 4)
  {
    std::cout << "The chanigng station index: " << std::to_string(stationIndex) << " in method 'GetChangingStationTaskPlace' is not defined." << std::endl;
      return nullptr;
  }

  double rotX = M_PI;
  double rotY = 0;
  double rotZ = M_PI * -0.5; 
  
  double stationXValues[4] = { -0.189, -0.0167, 0.1375, 0.29433 };
  double stationZValues[4] = { 0.416, 0.41356, 0.41005, 0.408 };

  double posEndZOffset = 0.03;
  double posPlaceOffsetZ = -0.005;

  double stationYApproach = -0.40759;
  double stationYExecute = -0.55;

  double posX = stationXValues[stationIndex - 1];
  double posStartZ = stationZValues[stationIndex - 1];

  auto targetPose1 = std::make_shared<WzlPlanner::Pose>(posX, stationYApproach, posStartZ, rotX, rotY, rotZ);
  auto targetPose2 = std::make_shared<WzlPlanner::Pose>(posX, stationYExecute, posStartZ, rotX, rotY, rotZ);
  auto targetPose3 = std::make_shared<WzlPlanner::Pose>(posX, stationYExecute, posStartZ + posEndZOffset, rotX, rotY, rotZ);
  auto targetPose4 = std::make_shared<WzlPlanner::Pose>(posX, stationYApproach, posStartZ + posEndZOffset, rotX, rotY, rotZ);
  auto targetPose5 = std::make_shared<WzlPlanner::Pose>(posX, stationYApproach, posStartZ, rotX, rotY, rotZ);

  auto taskMove1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskMove1->SetTargetPose(targetPose1);
  
  auto taskMove2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove2->SetTargetPose(targetPose2);

  auto taskMove3 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove3->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove3->SetTargetPose(targetPose3);

  auto taskMove4 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove4->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove4->SetTargetPose(targetPose4);

  auto taskMove5 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove5->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove5->SetTargetPose(targetPose5);

  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(taskMove1);
  taskList->AddTask(taskMove2);
  taskList->AddTask(taskMove3);
  taskList->AddTask(taskMove4);
  taskList->AddTask(taskMove5);  

  return taskList;
}

// The changing station pick taskm contains these steps:
// - Approach the changing station (PTP movement)
// - Lift up (cartesian movement)
// - Drive into execution pose (Cartesian movement)
// - Drop down and dock the new equipment 
// - Drive back (cartesian movement)
std::shared_ptr<WzlPlanner::TaskList> GetChangingStationTaskPick(int stationIndex)
{
  if (stationIndex < 1 || stationIndex > 4)
  {
    std::cout << "The chanigng station index: " << std::to_string(stationIndex) << " in method 'GetChangingStationTaskPlace' is not defined." << std::endl;
      return nullptr;
  }

  double rotX = M_PI;
  double rotY = 0;
  double rotZ = M_PI * -0.5; 

  double stationXValues[4] = { -0.189, -0.0167, 0.1375, 0.29433 };
  double stationZValues[4] = { 0.416, 0.41356, 0.41005, 0.408 };

  double posEndZOffset = 0.03;
  double posPlaceOffsetZ = -0.005;

  double stationYApproach = -0.40759;
  double stationYExecute = -0.55;

  double posX = stationXValues[stationIndex - 1];
  double posStartZ = stationZValues[stationIndex - 1];

  auto targetPose1 = std::make_shared<WzlPlanner::Pose>(posX, stationYApproach, posStartZ, rotX, rotY, rotZ);
  auto targetPose2 = std::make_shared<WzlPlanner::Pose>(posX, stationYApproach, posStartZ + posEndZOffset, rotX, rotY, rotZ);
  auto targetPose3 = std::make_shared<WzlPlanner::Pose>(posX, stationYExecute, posStartZ + posEndZOffset, rotX, rotY, rotZ);
  auto targetPose4 = std::make_shared<WzlPlanner::Pose>(posX, stationYExecute, posStartZ + posPlaceOffsetZ, rotX, rotY, rotZ);
  auto targetPose5 = std::make_shared<WzlPlanner::Pose>(posX, stationYApproach, posStartZ, rotX, rotY, rotZ);


  auto taskMove1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskMove1->SetTargetPose(targetPose1);
  
  auto taskMove2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove2->SetTargetPose(targetPose2);

  auto taskMove3 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove3->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove3->SetTargetPose(targetPose3);

  auto taskMove4 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove4->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove4->SetTargetPose(targetPose4);

  auto taskMove5 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove5->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove5->SetTargetPose(targetPose5);

  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(taskMove1);
  taskList->AddTask(taskMove2);
  taskList->AddTask(taskMove3);
  taskList->AddTask(taskMove4);
  taskList->AddTask(taskMove5);  

  return taskList;
}


void UseCase1()
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

  auto taskWait = std::make_shared<WzlPlanner::TaskWait>();
  taskWait->time_ = 1000ms;

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

  auto taskIoGripperNeutral = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_GreiferWritNeutral());
    taskIoGripperClose->SetId("taskIoGripperNeutral");

  auto taskIoDeburringSpindleDeactivate  = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_SpindelWriteAn());
    taskIoGripperClose->SetId("taskIoDeburringSindleOn");

  auto taskIoDeburringSpindleActivate= std::make_shared<WzlPlanner::TaskOpcuaRequest>(
    WzlPlanner::OpcUaData::GetOpcUaData_SpindelWriteAus());
    taskIoGripperClose->SetId("taskIoDeburringSindleOff");

  auto taskSetSpeedPtp = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(0.3, 1, 0);
  auto taskSetSpeedCartesianFast = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(0.1, 0.1, 1);
  auto taskSetSpeedCartesianSlow = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(0.03, 0.03, 1);

  // use just absolute poses
  double placementOffsetZ = 0.2;


  // Pick part from carrier and place it into clamping device
  double rotX = M_PI;
  double rotY = 0;
  double rotZ = -M_PI; 

  double executionBemi1Z = 0.25;
  double placementBemi1Z = executionBemi1Z + placementOffsetZ;
  double bemi1X = -0.4475369453430176;
  double bemi1Y = 0.3396724462509155;

  auto poseApproachBemi1 = std::make_shared<WzlPlanner::Pose>(bemi1X, bemi1Y, placementBemi1Z, rotX, rotY, rotZ);
  auto poseExceuteBemi1 = std::make_shared<WzlPlanner::Pose>(bemi1X, bemi1Y, executionBemi1Z, rotX, rotY, rotZ);
  auto poseEndBemi1 = std::make_shared<WzlPlanner::Pose>(bemi1X, bemi1Y, placementBemi1Z, rotX, rotY, rotZ);

  double executionBemi2Z = 0.3107452988624573;
  double placementBemi2Z = executionBemi1Z + placementOffsetZ;
  double bemi2X = 0.36473026871681213;
  double bemi2Y = 0.6826684474945068;

  rotX = 3.141;
  rotY = 0.005;
  rotZ = -M_PI + 0.065; 

  auto poseApproachBemi2 = std::make_shared<WzlPlanner::Pose>(bemi2X, bemi2Y, placementBemi2Z, rotX, rotY, rotZ);
  auto poseExceuteBemi2 = std::make_shared<WzlPlanner::Pose>(bemi2X, bemi2Y, executionBemi2Z, rotX, rotY, rotZ);
  auto poseEndBemi2 = std::make_shared<WzlPlanner::Pose>(bemi2X, bemi2Y, placementBemi2Z, rotX, rotY, rotZ);

  rotX = M_PI;
  rotY = 0;
  rotZ = -M_PI; 

  auto taskPickApproach1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPickExecute1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPickEnd1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  
  taskPickApproach1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi1);
  taskPickExecute1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseExceuteBemi1);
  taskPickEnd1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBemi1);

  auto taskPlaceApproach1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPlaceExecute1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPlaceEnd1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  
  taskPlaceApproach1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi2);
  taskPlaceExecute1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseExceuteBemi2);
  taskPlaceEnd1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBemi2);

  // Change tool: Gripper -> deburring spindle 
  auto taskGripperUnequip = GetChangingStationTaskPlace(1);
  auto taskDeburringSpindleEquip = GetChangingStationTaskPick(2);

  // do deburring
  double rotDeburX = M_PI;
  double rotDeburY = 0;
  double rotDeburZ = M_PI * -0.5; 

  auto taskDeburApproach1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskDeburApproach2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskDeburEnd1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskDeburEnd2 = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskDeburApproach1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi1);
  taskDeburApproach2->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi1);
  taskDeburEnd1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi1);
  taskDeburEnd2->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi1);


  // change tool: deburring spindle -> Gripper
  auto taskDeburringSpindleUnequip = GetChangingStationTaskPlace(2);
  auto taskGripperEquip = GetChangingStationTaskPick(1);

  // pick part and hold it in front of the sensor
  auto taskPickApproach2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPickExecute2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPickEnd2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  
  taskPickApproach2->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi2);
  taskPickExecute2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseExceuteBemi2);
  taskPickEnd2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBemi2);


  RCLCPP_INFO(node->get_logger(), "Execute Task Use Case 1");

  // setup custom task
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(taskSetSpeedPtp);

  // pick up part from carrier
  taskList->AddTask(taskSetSpeedCartesianFast);
  taskList->AddTask(taskPickApproach1);
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPickExecute1);
  taskList->AddTask(taskIoGripperOpen);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPickEnd1);

  // place part into clamping device
  taskList->AddTask(taskSetSpeedCartesianSlow);
  taskList->AddTask(taskPlaceApproach1);
  taskList->AddTask(taskIoBemi1Open);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPlaceExecute1);
  taskList->AddTask(taskSetSpeedCartesianFast);
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskIoBemi1Close);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPlaceEnd1);
  taskList->AddTask(taskIoGripperOpen);
  taskList->AddTask(taskIoGripperNeutral);

  // change equip: gripper -> deburring spindle
  taskList->AddTask(taskSetSpeedCartesianSlow);
  taskList->AddTask(taskGripperUnequip);
  taskList->AddTask(taskDeburringSpindleEquip);
  taskList->AddTask(taskIoDeburringSpindleDeactivate);

  // do the deburring process
  taskList->AddTask(taskIoDeburringSpindleActivate);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskIoDeburringSpindleDeactivate);

  // change equip: deburring spindle -> gripper
  taskList->AddTask(taskSetSpeedCartesianSlow);
  taskList->AddTask(taskDeburringSpindleUnequip);
  taskList->AddTask(taskGripperEquip);

  // pick up part again from clamping device
  taskList->AddTask(taskSetSpeedCartesianFast);
  taskList->AddTask(taskPlaceApproach1);
  taskList->AddTask(taskIoBemi1Open);
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPlaceExecute1);
  taskList->AddTask(taskIoGripperOpen);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPlaceEnd1);

  // take back part to carrier box
  taskList->AddTask(taskSetSpeedCartesianSlow);
  taskList->AddTask(taskPickApproach1);
  taskList->AddTask(taskPickExecute1);
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskSetSpeedCartesianFast);
  taskList->AddTask(taskPickEnd1);
  

  while (true)
  {
    taskList->Execute();
    rclcpp::spin_some(node);
  }
  

  RCLCPP_INFO(node->get_logger(), "Excecution successful");

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
  
  auto taskSetRobotSpeed = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(0.3, 0.3);

  // use just absolute poses
  double placementOffsetZ = 0.2;


  // BEMI 1
  double executionBemi1Z = 0.11785902827978134;

  auto posePickApproach = std::make_shared<WzlPlanner::Pose>(0.48967, 0.15907, executionBemi1Z + placementOffsetZ, 0.45, M_PI, 0, 0);
  auto posePickExceute = std::make_shared<WzlPlanner::Pose>(-0.4292486310005188, 0.15907, executionBemi1Z, M_PI, 0, 0);
  auto posePickEnd = std::make_shared<WzlPlanner::Pose>(0.48967, 0.15907, executionBemi1Z + placementOffsetZ, M_PI, 0, 0);

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
  
  auto taskSetRobotSpeed = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(1.0, 1.0);

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

void TaskMoveInCircleTest()
{
  auto node = WzlPlanner::ObjectContainer::Get()->GetNode();
  auto useOpcua = false;
  
  RCLCPP_INFO(node->get_logger(), "Initialize Trajectory circle test.");
  
  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceDummy>();
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);
  
  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("RoboGripper", 0, 1);

  robot->SetGripper(gripper);

  auto taskSetRobotSpeed = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(0.1, 0.1);

  double radius = 0.1;
  double posMidX = 0.3;
  double posMidY = 0.3;
  double posMidZ = 0.4;

  double rotX = M_PI;
  double rotY = 0;
  double rotZ = M_PI * -0.5; 

  auto taskStartPose = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskStartPose->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP);
  taskStartPose->SetTargetPose(std::make_shared<WzlPlanner::Pose>(posMidX, posMidY, posMidZ, rotX, rotY, rotZ));

  auto taskMoveTrjajectory = std::make_shared<WzlPlanner::TaskFollowTrajectory>();
  
  for (double i = 0; i < 2 * M_PI; i += 0.01)
  {
    double posX = posMidX + sin(i) * radius;
    double posY = posMidY + cos(i) * radius;

    auto pose = std::make_shared<WzlPlanner::Pose>(posX, posY, posMidZ, rotX, rotY, rotZ);
    taskMoveTrjajectory->AddPose(pose);
  }

  taskSetRobotSpeed->Execute();

  // setup custom task
  auto taskList = std::make_shared<WzlPlanner::TaskList>();
  taskList->AddTask(taskStartPose);
  taskList->AddTask(taskMoveTrjajectory);

  while (true)
  {
    taskList->Execute();
    rclcpp::spin_some(node);
  }

}

void TaskChangingStationTest()
{
  auto node = WzlPlanner::ObjectContainer::Get()->GetNode();
  auto useOpcua = false;
  
  RCLCPP_INFO(node->get_logger(), "Initialize Task Changing station - 2.");
  
  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceDummy>();
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);
  
  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("RoboGripper", 0, 1);

  robot->SetGripper(gripper);
  
  auto taskSetRobotSpeed = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(0.1, 0.1);
  
  auto taskPlace1 = GetChangingStationTaskPlace(1);
  auto taskPick1 = GetChangingStationTaskPick(1);

  auto taskPlace2 = GetChangingStationTaskPlace(2);
  auto taskPick2 = GetChangingStationTaskPick(2);

  auto taskPlace3 = GetChangingStationTaskPlace(3);
  auto taskPick3 = GetChangingStationTaskPick(3);

  auto taskPlace4 = GetChangingStationTaskPlace(4);
  auto taskPick4 = GetChangingStationTaskPick(4);



  RCLCPP_INFO(node->get_logger(), "Execute Task Changing station - 2");
  taskSetRobotSpeed->Execute();

  // setup custom task
  auto taskList = std::make_shared<WzlPlanner::TaskList>();
  taskList->AddTask(taskPlace1);
  taskList->AddTask(taskPick1);
  taskList->AddTask(taskPlace2);
  taskList->AddTask(taskPick2);
  taskList->AddTask(taskPlace3);
  taskList->AddTask(taskPick3);
  taskList->AddTask(taskPlace4);
  taskList->AddTask(taskPick4);

  while (true)
  {
    taskList->Execute();
    rclcpp::spin_some(node);
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


  CreateCell(node);
  //PickAndPlaceTest();
  //TaskRotationTest();

  rclcpp::sleep_for(3000ms);
  //TaskMoveInCircleTest();
  //TaskChangingStationTest();
  UseCase1();
  //OpcuaTaskTest(node);

  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();
  //spinner.join();
  return 0;
}