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

/**
 * @brief Retrieves a parameter value from a ROS node
 *
 * @param node The ROS node to retrieve the parameter from
 * @param name The name of the parameter
 * @param default_value The default value to return if the parameter does not exist
 * @return The value of the parameter
 */

template <typename T>
T get_parameter(const rclcpp::Node::SharedPtr &node, const std::string &name, const T &default_value)
{
  if (!node->has_parameter(name))
  {
    node->declare_parameter(name, default_value);
    RCLCPP_WARN(node->get_logger(), "Parameter %s not found Reverting to default value",name.c_str());
  }
  return node->get_parameter(name).get_value<T>();
}

void CreateCell(const std::shared_ptr<rclcpp::Node> node)
{
  // auto robot = std::make_shared<WzlPlanner::RobotDummy>(node);
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
  // scene->AddSceneObject(gripperChangeStation, std::make_shared<WzlPlanner::Pose>(0, 10, 0));

  // clamping device jaws
  RCLCPP_INFO(node->get_logger(), "Initialize Clamping device jaw");
  auto clampingDeviceJaws = std::make_shared<WzlPlanner::SceneObjectClampingDeviceJaws>("ClampingDeviceJaw", 0, 1);
  // scene->AddSceneObject(clampingDeviceJaws, std::make_shared<WzlPlanner::Pose>(5, 0, 0));

  // clamping device elevation
  RCLCPP_INFO(node->get_logger(), "Initialize clamping device elevation");
  auto clampingDeviceElevation = std::make_shared<WzlPlanner::SceneObjectClampingDeviceJaws>("ClampingDeviceElavation", 2, 3);
  // scene->AddSceneObject(clampingDeviceElevation, std::make_shared<WzlPlanner::Pose>(5, 0, 0));

  // scanning tower
  RCLCPP_INFO(node->get_logger(), "Initialize visual scan tower");
  auto scanningTower = std::make_shared<WzlPlanner::SceneObjectVisualScanTower>("VisualScanTower");
  // scene->AddSceneObject(scanningTower, std::make_shared<WzlPlanner::Pose>(5, 5, 0));

  // carrier
  RCLCPP_INFO(node->get_logger(), "Initialize carrier");
  auto carrier = std::make_shared<WzlPlanner::SceneObjectCarrier>("Carrier");
  // scene->AddSceneObject(carrier, std::make_shared<WzlPlanner::Pose>(-5, 0, 0));

  RCLCPP_INFO(node->get_logger(), "Robot scheduler cell environment initialization end.");
}

/**
 * Changing Station Place Task:
 * ---------------------------
 * This task involves the following steps:
 * 1. Approach the changing station (PTP)
 * 2. Drive in execution pose (Cartesian Movement)
 * 3. Lift up (Cartesian Movement)
 * 4. Drive back (Cartesian Movement)
 * 5. Drop down into start position (Cartesian Movement)
 *
 * @brief Retrieves a task list for the changing station place task
 *
 * @param node The ROS node to retrieve parameters from
 * @param stationIndex The index of the changing station (1-4)
 * @return A shared pointer to the task list
 */
std::shared_ptr<WzlPlanner::TaskList> GetChangingStationTaskPlace(const rclcpp::Node::SharedPtr &node, int stationIndex)
{
  if (stationIndex < 1 || stationIndex > 4)
  {
    std::cout << "The chanigng station index: " << std::to_string(stationIndex) << " in method 'GetChangingStationTaskPlace' is not defined." << std::endl;
    return nullptr;
  }

  double rotX = M_PI;
  double rotY = 0;
  double rotZ = M_PI * -0.5;

  std::vector<double> stationXValues = get_parameter<std::vector<double>>(node, "positions.station.x_positions", {-0.189, -0.0167, 0.1375, 0.29433});
  std::vector<double> stationZValues = get_parameter<std::vector<double>>(node, "positions.station.z_values", {0.416, 0.41356, 0.41005, 0.408});

  double posEndZOffset = get_parameter<double>(node, "safety.pos_end_z_offset", 0.03);
  // double posPlaceOffsetZ = get_parameter<double>(node, "safety.pos_place_offset_z", -0.005);

  double stationYApproach = get_parameter<double>(node, "positions.station.y_approach", -0.35);
  double stationYExecute = get_parameter<double>(node, "positions.station.y_execute", -0.5549700856208801);

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

/**
 * @brief Creates a task list for picking up a station
 *
 * The changing station pick taskm contains these steps:
 * 1. Approach the changing station (PTP movement)
 * 2. Lift up (cartesian movement)
 * 3. Drive into execution pose (Cartesian movement)
 * 4. Drop down and dock the new equipment
 * 5. Drive back (cartesian movement)
 *
 * @param stationIndex The index of the station to pick up (1-4)
 * @return A shared pointer to the task list
 */
std::shared_ptr<WzlPlanner::TaskList> GetChangingStationTaskPick(int stationIndex)
{
  if (stationIndex < 1 || stationIndex > 4)
  {
    std::cout << "The chanigng station index: " << std::to_string(stationIndex) << " in method 'GetChangingStationTaskPlace' is not defined." << std::endl;
    return nullptr;
  }

  //double rotX = M_PI;
  double rotX = M_PI - M_PI/256; // Offset weil tool change station nicht gerade ist
  double rotY = 0;
  double rotZ = M_PI * -0.5;

  double stationXValues[4] = {-0.189, -0.0167, 0.1375, 0.29433};
  double stationZValues[4] = {0.416, 0.41356, 0.41005, 0.408};
  //double stationZValues[4] = {0.416, 0.41356, 0.405, 0.408};

  double posEndZOffset = 0.03;
  double posPlaceOffsetZ = -0.005;

  double stationYApproach = -0.35;
  double stationYExecute = -0.5549700856208801;

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
/**
 * @brief Creates a task list for a circular movement around a given point
 *
 * @param radius The radius of the circle to move around
 * @param posePointCenter The point around which to move in a circle
 * @return A shared pointer to the TaskFollowTrajectory
 */
std::shared_ptr<WzlPlanner::TaskFollowTrajectory> CreateTaskMoveInCircle(double radius, std::shared_ptr<WzlPlanner::Pose> posePointCenter)
{
  double posMidX = posePointCenter->GetPositionX();
  double posMidY = posePointCenter->GetPositionY();
  double posMidZ = posePointCenter->GetPositionZ();

  double rotX = posePointCenter->GetRotationX();
  double rotY = posePointCenter->GetRotationY();
  double rotZ = posePointCenter->GetRotationZ();

  auto taskMoveTrjajectory = std::make_shared<WzlPlanner::TaskFollowTrajectory>();

  for (double i = 0; i < 2 * M_PI; i += 0.01)
  {
    double posX = posMidX + sin(i) * radius;
    double posY = posMidY + cos(i) * radius;

    auto pose = std::make_shared<WzlPlanner::Pose>(posX, posY, posMidZ, rotX, rotY, rotZ);
    taskMoveTrjajectory->AddPose(pose);
  }

  return taskMoveTrjajectory;
}

/**
 * @brief Main function for the UseCase1
 *
 * Contains all tasks for UseCase1
 * It will execute all tasks in the correct order.
 *
 * @param node ROS2 node object
 */
void UseCase1(const rclcpp::Node::SharedPtr &node)
{
  // auto node = WzlPlanner::ObjectContainer::Get()->GetNode();
  [[maybe_unused]] auto useOpcua = false;

  RCLCPP_INFO(node->get_logger(), "Initialize Pick & Place test.");

  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);

  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("RoboGripper", 0, 1);

  robot->SetGripper(gripper);

  RCLCPP_INFO(node->get_logger(), "Initialize Task Pick & Place");

  // DEFINING MISC. TASKS
  auto taskWait = std::make_shared<WzlPlanner::TaskWait>();
  taskWait->time_ = std::chrono::milliseconds(get_parameter<int>(node, "timings.default_wait", 1000));

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

  auto taskIoDeburringSpindleDeactivate = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
      WzlPlanner::OpcUaData::GetOpcUaData_SpindelWriteAn());
  taskIoGripperClose->SetId("taskIoDeburringSindleOn");

  auto taskIoDeburringSpindleActivate = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
      WzlPlanner::OpcUaData::GetOpcUaData_SpindelWriteAus());
  taskIoGripperClose->SetId("taskIoDeburringSindleOff");

  // Set movement speeds: velocity, acelleration, type(normal:0, cartesian:1)
  auto taskSetSpeedPtp = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(0.5, 1.0, 0);
  auto taskSetSpeedCartesianFast = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(0.1, 0.1, 1);
  auto taskSetSpeedCartesianSlow = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(0.06, 0.03, 1);

  // Constants
  double placementOffsetZ = 0.2;

  double rotX = M_PI;
  double rotY = 0;
  double rotZ = -M_PI - M_PI/4;

  // INIT pose and task def
  auto poseInit = std::make_shared<WzlPlanner::Pose>(0.3122745752334595, 0.09810880571603775, 0.4534417390823364, rotX, rotY, rotZ);
  
  auto taskInitPose = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskInitPose->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseInit);
  
  // Part Carrier 1: POSE DEF
  std::vector<double> PC1X = get_parameter<std::vector<double>>(node, "positions.PC_1.x", {-0.351, -0.361});
  std::vector<double> PC1Y = get_parameter<std::vector<double>>(node, "positions.PC_1.y", {0.341, 0.341});
  double executionPC1Z = get_parameter<double>(node, "positions.PC_1.z", 0.26);
  double placementPC1Z = executionPC1Z + placementOffsetZ;

  auto posePC1Approach1 = std::make_shared<WzlPlanner::Pose>(PC1X[2], PC1Y[2], placementPC1Z, rotX, rotY, rotZ);
  auto posePC1Execute1 = std::make_shared<WzlPlanner::Pose>(PC1X[2], PC1Y[2], executionPC1Z, rotX, rotY, rotZ);
  auto posePC1End1 = std::make_shared<WzlPlanner::Pose>(PC1X[2], PC1Y[2], placementPC1Z, rotX, rotY, rotZ);

  // Part Carrier 1, part 1: TASK DEF
  auto taskPC1Approach1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPC1Execute1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPC1End1 = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskPC1Approach1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(posePC1Approach1);
  taskPC1Execute1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePC1Execute1);
  taskPC1End1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePC1End1);

  // BEMI 1: POSE DEF
  double executionBemi1Z = get_parameter<double>(node, "positions.bemi1.z", 0.3107452988624573);
  double placementBemi1Z = executionBemi1Z + placementOffsetZ;
  double bemi1X = get_parameter<double>(node, "positions.bemi1.x", -0.3);
  double bemi1Y = get_parameter<double>(node, "positions.bemi1.y", 0.67974);
  
  double bemi1RZOffset = get_parameter<double>(node, "positions.bemi1.RZ_offset", 0);
  double bemi1rotZ = rotZ + bemi1RZOffset;

  auto poseApproachBemi1 = std::make_shared<WzlPlanner::Pose>(bemi1X, bemi1Y, placementBemi1Z, rotX, rotY, bemi1rotZ );
  auto poseExceuteBemi1 = std::make_shared<WzlPlanner::Pose>(bemi1X, bemi1Y, executionBemi1Z, rotX, rotY, bemi1rotZ );
  auto poseEndBemi1 = std::make_shared<WzlPlanner::Pose>(bemi1X, bemi1Y, placementBemi1Z, rotX, rotY, bemi1rotZ);

  // BEMI 1: TASK DEF
  auto taskApproachBemi1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskExecuteBemi1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskEndBemi1 = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskApproachBemi1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi1);
  taskExecuteBemi1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseExceuteBemi1);
  taskEndBemi1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBemi1);

  // BEMI 2: POSE DEF
  double executionBemi2Z = get_parameter<double>(node, "positions.bemi2.z", 0);
  double placementBemi2Z = executionBemi1Z + placementOffsetZ;
  double bemi2X = get_parameter<double>(node, "positions.bemi2.x", 0);
  double bemi2Y = get_parameter<double>(node, "positions.bemi2.y", 0);

  double bemi2RZOffset = get_parameter<double>(node, "positions.bemi2.RZ_offset", 0);
  double bemi2rotZ = rotZ + bemi2RZOffset;

  auto poseApproachBemi2 = std::make_shared<WzlPlanner::Pose>(bemi2X, bemi2Y, placementBemi2Z, rotX, rotY, bemi2rotZ);
  auto poseExceuteBemi2 = std::make_shared<WzlPlanner::Pose>(bemi2X, bemi2Y, executionBemi2Z, rotX, rotY, bemi2rotZ);
  auto poseEndBemi2 = std::make_shared<WzlPlanner::Pose>(bemi2X, bemi2Y, placementBemi2Z, rotX, rotY, bemi2rotZ);
  
  // BEMI 2: TASK DEF
  auto taskApproachBemi2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskExecuteBemi2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskEndBemi2 = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskApproachBemi2->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi2);
  taskExecuteBemi2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseExceuteBemi2);
  taskEndBemi2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBemi2);

  // Change tool: Gripper -> deburring spindle
  auto taskGripperUnequip = GetChangingStationTaskPlace(node, 3);
  auto taskDeburringSpindleEquip = GetChangingStationTaskPick(2);

  // Deburring Pose and Task DEF
  double rotDeburX = M_PI;
  double rotDeburY = 0;
  double rotDeburZ = -M_PI;

  auto taskDeburApproach1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskDeburExecute = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskDeburEnd1 = std::make_shared<WzlPlanner::TaskMoveToPose>();

  auto deburApporachOffsetZ = 0.1;
  auto poseApporachBemi1Debur = std::make_shared<WzlPlanner::Pose>(0.36059075593948364, 0.6857767701148987, 0.4643709659576416 + deburApporachOffsetZ, rotDeburX, rotDeburY, rotDeburZ);
  auto poseExecuteDebur = std::make_shared<WzlPlanner::Pose>(0.36059075593948364, 0.6857767701148987, 0.4643709659576416 + 0.03, rotDeburX, rotDeburY, rotDeburZ);

  auto taskDeburCircle = CreateTaskMoveInCircle(0.023, poseExecuteDebur);
  taskDeburApproach1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApporachBemi1Debur);
  taskDeburExecute->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseExecuteDebur);
  taskDeburEnd1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseApporachBemi1Debur);

  // change tool: deburring spindle -> Gripper
  auto taskDeburringSpindleUnequip = GetChangingStationTaskPlace(node, 2);
  auto taskGripperEquip = GetChangingStationTaskPick(3);

  // pick part and hold it in front of the sensor
  auto taskPickApproach2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPickExecute2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPickEnd2 = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskPickApproach2->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi2);
  taskPickExecute2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseExceuteBemi2);
  taskPickEnd2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBemi2);

  // do quality inspection
  auto taskQualityInspection = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto poseQualityInspection = std::make_shared<WzlPlanner::Pose>(bemi2X, bemi2Y, placementBemi2Z, 0, 0, 0);

  // TASK SCHEDULING //
  RCLCPP_INFO(node->get_logger(), "Execute Task Use Case 1");

  // setup custom task
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  // set pneumatic to neutral
  taskList->AddTask(taskIoGripperNeutral);
  taskList->AddTask(taskIoDeburringSpindleDeactivate);

  // set robot speed
  taskList->AddTask(taskSetSpeedPtp);

  // move to innitial pose
  taskList->AddTask(taskInitPose);

  // take gripper from changing station
  taskList->AddTask(taskGripperEquip);

  // pick up part 1 from part carrier 1 (PC 1)
  taskList->AddTask(taskSetSpeedCartesianFast);
  taskList->AddTask(taskPC1Approach1);
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPC1Execute1);
  taskList->AddTask(taskIoGripperOpen);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskPC1End1);

  // place part into clamping device BEMI 1
  taskList->AddTask(taskSetSpeedCartesianSlow);
  taskList->AddTask(taskApproachBemi1);
  taskList->AddTask(taskIoBemi1Open);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskExecuteBemi1);
  taskList->AddTask(taskSetSpeedCartesianFast);
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskIoBemi1Close);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskEndBemi1);
  taskList->AddTask(taskIoGripperOpen);
  taskList->AddTask(taskIoGripperNeutral);

  // change equip: gripper -> deburring spindle
  taskList->AddTask(taskSetSpeedCartesianSlow);
  taskList->AddTask(taskGripperUnequip);
  taskList->AddTask(taskDeburringSpindleEquip);
  taskList->AddTask(taskIoDeburringSpindleDeactivate);

  // do the deburring process
  taskList->AddTask(taskDeburApproach1);
  taskList->AddTask(taskDeburExecute);
  taskList->AddTask(taskIoDeburringSpindleActivate);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskDeburCircle);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskIoDeburringSpindleDeactivate);
  taskList->AddTask(taskDeburEnd1);

  // change equip: deburring spindle -> gripper
  taskList->AddTask(taskSetSpeedCartesianSlow);
  taskList->AddTask(taskDeburringSpindleUnequip);
  taskList->AddTask(taskGripperEquip);

  // pick up part again from clamping device BEMI 1
  taskList->AddTask(taskSetSpeedCartesianFast);
  taskList->AddTask(taskApproachBemi1);
  taskList->AddTask(taskIoBemi1Open);
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskExecuteBemi1);
  taskList->AddTask(taskIoGripperOpen);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskEndBemi1);

  // do quality inspection
  // taskList->AddTask(taskQualityInspection);

  // take back part to carrier box
  taskList->AddTask(taskSetSpeedCartesianSlow);
  taskList->AddTask(taskPC1Approach1);
  taskList->AddTask(taskPC1Execute1);
  taskList->AddTask(taskIoGripperClose);
  taskList->AddTask(taskWait);
  taskList->AddTask(taskSetSpeedCartesianFast);
  taskList->AddTask(taskPC1End1);

  // unequip gripper
  taskList->AddTask(taskIoGripperNeutral);
  taskList->AddTask(taskSetSpeedCartesianSlow);
  taskList->AddTask(taskGripperUnequip);

  // move back to idle pose
  taskList->AddTask(taskInitPose);

  while (true)
  {
    if (!taskList->Execute())
    {
      RCLCPP_INFO(node->get_logger(), "Excecution failed");
      return;
    }

    rclcpp::spin_some(node);
  }

  RCLCPP_INFO(node->get_logger(), "Excecution successful");
}

#ifdef RUN_TESTS

int TransformTest()
{

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

  auto taskPlace1 = GetChangingStationTaskPlace(node, 1);
  auto taskPick1 = GetChangingStationTaskPick(1);

  auto taskPlace2 = GetChangingStationTaskPlace(node, 2);
  auto taskPick2 = GetChangingStationTaskPick(2);

  auto taskPlace3 = GetChangingStationTaskPlace(node, 3);
  auto taskPick3 = GetChangingStationTaskPick(3);

  auto taskPlace4 = GetChangingStationTaskPlace(node, 4);
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
#endif

int main(int argc, char *argv[])
{
  // Initialize ROS and create the Node
  std::cout << "Initialize robo planner node" << std::endl;
  rclcpp::init(argc, argv);

  // auto trWorld = std::make_shared<WzlPlanner::Transform>("world");

  rclcpp::sleep_for(500ms);

  auto const node = std::make_shared<rclcpp::Node>(
      "robo_planner", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));

  CreateCell(node);
  // PickAndPlaceTest();
  // TaskRotationTest();

  rclcpp::sleep_for(3000ms);
  // TaskMoveInCircleTest();
  // TaskChangingStationTest();
  UseCase1(node);
  // OpcuaTaskTest(node);

  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();
  // spinner.join();
  return 0;
}