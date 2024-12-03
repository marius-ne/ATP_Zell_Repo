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
    RCLCPP_WARN(node->get_logger(), "Parameter %s not found Reverting to default value", name.c_str());
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

class MiscTasks
{
public:
  // Task objects are publicly accessible for reuse in other functions
  std::shared_ptr<WzlPlanner::TaskWait> taskWait;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoBemi1Open;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoBemi1Close;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoBemi2Open;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoBemi2Close;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoBemi3Open;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoBemi3Close;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoGripperOpen;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoGripperClose;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoGripperNeutral;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoDeburringSpindleDeactivate;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoDeburringSpindleActivate;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoDeburringSpindleAnpressdruckActivate;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoDeburringSpindleAnpressdruckDeactivate;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoLampRed;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoLampGreen;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoLampOrange;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoLampOff;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoTuerAuf;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoTuerZu;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoTuerStop;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoAlarmOn;
  std::shared_ptr<WzlPlanner::TaskOpcuaRequest> taskIoAlarmOff;
  std::shared_ptr<WzlPlanner::TaskSetRobotValueVelocity> taskSetSpeedPtp;
  std::shared_ptr<WzlPlanner::TaskSetRobotValueVelocity> taskSetSpeedCartesianFast;
  std::shared_ptr<WzlPlanner::TaskSetRobotValueVelocity> taskSetSpeedCartesianSlow;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachSpindel;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachGripper;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachSmallGripper;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachSpindel;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachGripper;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachSmallGripper;

  // Constructor initializes all tasks
  MiscTasks(const rclcpp::Node::SharedPtr &node)
  {
    taskWait = std::make_shared<WzlPlanner::TaskWait>();
    taskWait->time_ = std::chrono::milliseconds(get_parameter<int>(node, "timings.default_wait", 300));
    taskWait->SetId("taskWait");

    taskIoBemi1Open = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_Bemi1WriteAuf());
    taskIoBemi1Open->SetId("taskIoBemi1Open");

    taskIoBemi1Close = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_Bemi1WriteZu());
    taskIoBemi1Close->SetId("taskIoBemi1Close");

    taskIoBemi2Open = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_Bemi2WriteAuf());
    taskIoBemi2Open->SetId("taskIoBemi2Open");

    taskIoBemi2Close = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_Bemi2WriteZu());
    taskIoBemi2Close->SetId("taskIoBemi2Close");

    taskIoBemi3Open = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_Bemi3WriteAuf());
    taskIoBemi3Open->SetId("taskIoBemi3Open");

    taskIoBemi3Close = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_Bemi3WriteZu());
    taskIoBemi3Close->SetId("taskIoBemi3Close");

    taskIoGripperOpen = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_GreiferWriteAuf());
    taskIoGripperOpen->SetId("taskIoGripperOpen");

    taskIoGripperClose = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_GreiferWritZu());
    taskIoGripperClose->SetId("taskIoGripperClose");

    taskIoGripperNeutral = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_GreiferWritNeutral());
    taskIoGripperNeutral->SetId("taskIoGripperNeutral");

    taskIoDeburringSpindleDeactivate = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_SpindelWriteAus());
    taskIoDeburringSpindleDeactivate->SetId("taskIoDeburringSpindleOff");

    taskIoDeburringSpindleActivate = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_SpindelWriteAn());
    taskIoDeburringSpindleActivate->SetId("taskIoDeburringSpindleOn");

    taskIoDeburringSpindleAnpressdruckActivate = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_AnpressdruckSpindelWriteAn());
    taskIoDeburringSpindleAnpressdruckActivate->SetId("taskIoDeburringSpindleAnpressdruckOn");

    taskIoDeburringSpindleAnpressdruckDeactivate = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_AnpressdruckSpindelWriteAus());
    taskIoDeburringSpindleAnpressdruckDeactivate->SetId("taskIoDeburringSpindleAnpressdruckOff");

    taskIoLampRed = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_LampeFarbeWriteRot());
    taskIoLampRed->SetId("taskIoLampRed");

    taskIoLampGreen = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_LampeFarbeWriteGrün());
    taskIoLampGreen->SetId("taskIoLampGreen");

    taskIoLampOrange = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_LampeFarbeWriteOrange());
    taskIoLampOrange->SetId("taskIoLampOrange");

    taskIoLampOff = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_LampeFarbeWriteAus());
    taskIoLampOff->SetId("taskIoLampOff");

    taskIoTuerAuf = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_TuerWriteAuf());
    taskIoTuerAuf->SetId("taskIoTuerAuf");

    taskIoTuerZu = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_TuerWriteZu());
    taskIoTuerZu->SetId("taskIoTuerZu");

    taskIoTuerStop = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_TuerWriteStop());
    taskIoTuerStop->SetId("taskIoTuerStop");

    taskIoAlarmOn = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_AlarmWriteAn());
    taskIoAlarmOn->SetId("taskIoAlarmOn");

    taskIoAlarmOff = std::make_shared<WzlPlanner::TaskOpcuaRequest>(
        WzlPlanner::OpcUaData::GetOpcUaData_AlarmWriteAus());
    taskIoAlarmOff->SetId("taskIoAlarmOff");

    // Set movement speeds from config parameters
    double ptp_speed = get_parameter<double>(node, "speeds.ptp", 0.3);
    double cartesian_fast = get_parameter<double>(node, "speeds.cartesian_fast", 0.1);
    double cartesian_slow = get_parameter<double>(node, "speeds.cartesian_slow", 0.03);

    taskSetSpeedPtp = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(ptp_speed, 1.0, 0);
    taskSetSpeedCartesianFast = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(cartesian_fast, 0.1, 1);
    taskSetSpeedCartesianSlow = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(cartesian_slow, 0.05, 1);

    taskSetSpeedPtp->SetId("taskSetSpeedPtp");
    taskSetSpeedCartesianFast->SetId("taskSetSpeedCartesianFast");
    taskSetSpeedCartesianSlow->SetId("taskSetSpeedCartesianSlow");

    // Part Attach-Detach

    taskAttachSpindel = std::make_shared<WzlPlanner::TaskPartAttach>("spindel");
    taskAttachSpindel->SetId("taskAttachSpindel");

    taskAttachGripper = std::make_shared<WzlPlanner::TaskPartAttach>("gripper");
    taskAttachGripper->SetId("taskAttachGripper");

    taskAttachSmallGripper = std::make_shared<WzlPlanner::TaskPartAttach>("small_gripper");
    taskAttachSmallGripper->SetId("taskAttachSmallGripper");

    taskDetachSpindel = std::make_shared<WzlPlanner::TaskPartDetach>("spindel");
    taskDetachSpindel->SetId("taskDetachSpindel");

    taskDetachGripper = std::make_shared<WzlPlanner::TaskPartDetach>("gripper");
    taskDetachGripper->SetId("taskDetachGripper");

    taskDetachSmallGripper = std::make_shared<WzlPlanner::TaskPartDetach>("small_gripper");
    taskDetachSmallGripper->SetId("taskDetachSmallGripper");

    RCLCPP_INFO(node->get_logger(), "Miscellaneous tasks initialized.");
  }
};

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

  std::vector<double> stationXValues = get_parameter<std::vector<double>>(node, "positions.station.x_positions", {-0.189, -0.0167, 0.1375, 0.27893});
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
std::shared_ptr<WzlPlanner::TaskList> GetChangingStationTaskPick(const rclcpp::Node::SharedPtr &node, int stationIndex)
{
  if (stationIndex < 1 || stationIndex > 4)
  {
    std::cout << "The changing station index: " << std::to_string(stationIndex) << " in method 'GetChangingStationTaskPlace' is not defined." << std::endl;
    return nullptr;
  }

  double rotX = M_PI - M_PI / 256; // Offset weil tool change station nicht gerade ist
  double rotY = 0;
  double rotZ = M_PI * -0.5;

  std::vector<double> stationXValues = get_parameter<std::vector<double>>(node, "positions.station.x_positions", {-0.189, -0.0167, 0.1375, 0.27893});
  std::vector<double> stationZValues = get_parameter<std::vector<double>>(node, "positions.station.z_values", {0.416, 0.41356, 0.41005, 0.408});

  double posEndZOffset = get_parameter<double>(node, "safety.pos_end_z_offset", 0.03);
  double posPlaceOffsetZ = get_parameter<double>(node, "safety.placement_offset_z", -0.005);

  double stationYApproach = get_parameter<double>(node, "positions.station.y_approach", -0.35);
  double stationYExecute = get_parameter<double>(node, "positions.station.y_execute", -0.5549700856208801);

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
 * Pick task Part carrier:
 * ---------------------------
 * This task involves the following steps:
 * 1. Sets correct speed
 * 2. Moves above Pick position
 * 3. Closes Gripper
 * 4. Moves to Pick position
 * 5. Opens Gripper
 * 6. Moves up
 *
 * @brief Retrieves a task list for the changing station place task
 *
 * @param node The ROS node to retrieve parameters from
 * @param PCIndex The index of the Positions within the Part Carrier (1-8 for PC1)
 * @param PCNr The Part Carrier Number 1-2
 * @return A shared pointer to the task list
 */
std::shared_ptr<WzlPlanner::TaskList> CreateTaskPickPC(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks, int PCIndex, int PCNr)
{
  if (PCNr < 1 || PCNr > 2)
  {
    std::cout << "The Part Carrier number: " << std::to_string(PCNr) << " in method 'CreateTaskPickPC' is not defined." << std::endl;
    return nullptr;
  }

  // Constants
  double placementOffsetZ = 0.2;

  double rotX = M_PI;
  double rotY = 0;
  double rotZ;

  std::vector<double> PC1X;
  std::vector<double> PC1Y;
  std::vector<double> PC1Z;

  if (PCNr == 1)
  {
    PC1X = get_parameter<std::vector<double>>(node, "positions.PC.x_1", {-0.351, -0.456, -0.561, -0.666, -0.771, -0.416, -0.589, -0.762});
    PC1Y = get_parameter<std::vector<double>>(node, "positions.PC.y_1", {0.341, 0.341, 0.341, 0.341, 0.341, 0.144, 0.144, 0.144});
    PC1Z = get_parameter<std::vector<double>>(node, "positions.PC.z_1", {0.260, 0.260, 0.260, 0.260, 0.260, 0.230, 0.230, 0.230});
    rotZ = -M_PI - M_PI / 4;
  }
  else if (PCNr == 2)
  {
    PC1X = get_parameter<std::vector<double>>(node, "positions.PC.x_2", {-0.50674, 0.0});
    PC1Y = get_parameter<std::vector<double>>(node, "positions.PC.y_2", {-0.18692, 0.0});
    PC1Z = get_parameter<std::vector<double>>(node, "positions.PC.z_2", {0.5453, 0.0});
    //rotZ = -M_PI;
    rotZ = -M_PI + (5.0 / 12.0) * M_PI;

  }

  int PC_index = PCIndex - 1;

  double placementPC1Z = PC1Z[PC_index] + placementOffsetZ;

  auto posePC1Approach1 = std::make_shared<WzlPlanner::Pose>(PC1X[PC_index], PC1Y[PC_index], placementPC1Z, rotX, rotY, rotZ);
  auto posePC1Execute1 = std::make_shared<WzlPlanner::Pose>(PC1X[PC_index], PC1Y[PC_index], PC1Z[PC_index], rotX, rotY, rotZ);
  auto posePC1End1 = std::make_shared<WzlPlanner::Pose>(PC1X[PC_index], PC1Y[PC_index], placementPC1Z, rotX, rotY, rotZ);

  // Part Carrier 1, part 1: TASK DEF
  auto taskPC1Approach1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPC1Execute1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPC1End1 = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskPC1Approach1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(posePC1Approach1);
  taskPC1Execute1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePC1Execute1);
  taskPC1End1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePC1End1);

  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(tasks->taskSetSpeedCartesianFast);
  taskList->AddTask(taskPC1Approach1);
  taskList->AddTask(tasks->taskIoGripperClose);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPC1Execute1);
  taskList->AddTask(tasks->taskIoGripperOpen);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPC1End1);

  return taskList;
}

/**
 * Place task Part carrier:
 * ---------------------------
 * This task involves the following steps:
 * 1. Sets correct speed
 * 2. Moves above Place position
 * 3. Moves to Pick/Place position
 * 4. Closes Gripper
 * 5. Sets correct speed
 * 6. Moves up
 *
 * @brief Retrieves a task list for the changing station place task
 *
 * @param node The ROS node to retrieve parameters from
 * @param PCIndex The index of the Positions within the Part Carrier (1-8 for PC1)
 * @param PCNr The Part Carrier Number 1-2
 * @return A shared pointer to the task list
 */
std::shared_ptr<WzlPlanner::TaskList> CreateTaskPlacePC(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks, int PCIndex, int PCNr)
{
  if (PCNr < 1 || PCNr > 2)
  {
    std::cout << "The Part Carrier number: " << std::to_string(PCNr) << " in method 'CreateTaskPickPC' is not defined." << std::endl;
    return nullptr;
  }

  // Constants
  double placementOffsetZ = 0.2;

  double rotX = M_PI;
  double rotY = 0;
  double rotZ;

  std::vector<double> PC1X;
  std::vector<double> PC1Y;
  std::vector<double> PC1Z;

  if (PCNr == 1)
  {
    PC1X = get_parameter<std::vector<double>>(node, "positions.PC.x_1", {-0.351, -0.456, -0.561, -0.666, -0.771, -0.416, -0.589, -0.762});
    PC1Y = get_parameter<std::vector<double>>(node, "positions.PC.y_1", {0.341, 0.341, 0.341, 0.341, 0.341, 0.144, 0.144, 0.144});
    PC1Z = get_parameter<std::vector<double>>(node, "positions.PC.z_1", {0.260, 0.260, 0.260, 0.260, 0.260, 0.230, 0.230, 0.230});
    rotZ = -M_PI - M_PI / 4;
  }
  else if (PCNr == 2)
  {
    PC1X = get_parameter<std::vector<double>>(node, "positions.PC.x_2", {-0.50674, 0.0});
    PC1Y = get_parameter<std::vector<double>>(node, "positions.PC.y_2", {-0.18692, 0.0});
    PC1Z = get_parameter<std::vector<double>>(node, "positions.PC.z_2", {0.5453, 0.0});
    //rotZ = -M_PI;
    rotZ = -M_PI + (5.0 / 12.0) * M_PI;
  }

  int PC_index = PCIndex - 1;

  double placementPC1Z = PC1Z[PC_index] + placementOffsetZ;

  auto posePC1Approach1 = std::make_shared<WzlPlanner::Pose>(PC1X[PC_index], PC1Y[PC_index], placementPC1Z, rotX, rotY, rotZ);
  auto posePC1Execute1 = std::make_shared<WzlPlanner::Pose>(PC1X[PC_index], PC1Y[PC_index], PC1Z[PC_index], rotX, rotY, rotZ);
  auto posePC1End1 = std::make_shared<WzlPlanner::Pose>(PC1X[PC_index], PC1Y[PC_index], placementPC1Z, rotX, rotY, rotZ);

  // Part Carrier 1, part 1: TASK DEF
  auto taskPC1Approach1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPC1Execute1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPC1End1 = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskPC1Approach1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(posePC1Approach1);
  taskPC1Execute1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePC1Execute1);
  taskPC1End1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePC1End1);

  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
  taskList->AddTask(taskPC1Approach1);
  taskList->AddTask(taskPC1Execute1);
  taskList->AddTask(tasks->taskIoGripperClose);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskSetSpeedCartesianFast);
  taskList->AddTask(taskPC1End1);

  return taskList;
}

/**
 * Pick task BEMI:
 * ---------------------------
 * This task involves the following steps:
 * 1. Sets correct speed
 * 2. Moves above Pick position
 * 3. Opens BEMI
 * 4. Closes Gripper
 * 5. Moves to Pick position
 * 6. Opens Gripper
 * 7. Moves up
 *
 * @brief Retrieves a task list for the changing station place task
 *
 * @param node The ROS node to retrieve parameters from
 * @param BEMIIndex The index of the BEMI 1-3
 * @return A shared pointer to the task list
 */
std::shared_ptr<WzlPlanner::TaskList> CreateTaskPickBEMI(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks, int BEMIIndex)
{
  if (BEMIIndex < 1 || BEMIIndex > 3)
  {
    std::cout << "The BEMI index: " << std::to_string(BEMIIndex) << " in method 'CreateTaskPickBEMI' is not defined." << std::endl;
    return nullptr;
  }

  // Constants
  double placementOffsetZ = 0.2;

  double rotX = M_PI;
  double rotY = 0;
  double rotZ = -M_PI - M_PI / 4;

  // BEMI POSE DEF

  std::vector<double> ExecutionBEMIZ = get_parameter<std::vector<double>>(node, "positions.bemi.z", {0.320, 0.2885, 0.0});

  double placementBemiZ = ExecutionBEMIZ[BEMIIndex - 1] + placementOffsetZ;

  std::vector<double> BEMIX = get_parameter<std::vector<double>>(node, "positions.bemi.x", {0.3634, 0.1184, 0.0});
  std::vector<double> BEMIY = get_parameter<std::vector<double>>(node, "positions.bemi.y", {0.6815, 0.6178, 0.0});

  std::vector<double> BEMIRZOffset = get_parameter<std::vector<double>>(node, "positions.bemi.RZ_offset", {0.0475, -1.405985086238, 0.0});
  double BEMIrotZ = rotZ + BEMIRZOffset[BEMIIndex - 1];

  auto poseApproachBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], placementBemiZ, rotX, rotY, BEMIrotZ);
  auto poseExecuteBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], ExecutionBEMIZ[BEMIIndex - 1], rotX, rotY, BEMIrotZ);
  auto poseEndBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], placementBemiZ, rotX, rotY, BEMIrotZ);

  // BEMI TASK DEF
  auto taskApproachBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskExecuteBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskEndBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskApproachBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi);
  taskExecuteBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseExecuteBemi);
  taskEndBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBemi);

  // DEFINE TASK LIST
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(tasks->taskSetSpeedCartesianFast);
  taskList->AddTask(taskApproachBemi);

  if (BEMIIndex == 1)
  {
    taskList->AddTask(tasks->taskIoBemi1Open);
  }
  else if (BEMIIndex == 2)
  {
    taskList->AddTask(tasks->taskIoBemi2Open);
  } // else if (BEMIIndex == 3)
  //{
  // taskList->AddTask(tasks->taskIoBemi3Open);
  //}

  taskList->AddTask(tasks->taskIoGripperClose);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskExecuteBemi);
  taskList->AddTask(tasks->taskIoGripperOpen);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskEndBemi);

  return taskList;
}

/**
 * Place task BEMI:
 * ---------------------------
 * This task involves the following steps:
 * 1. Sets correct speed
 * 2. Moves above Place position
 * 3. Opens BEMI
 * 4. Moves to Place position
 * 5. Sets correct speed
 * 4. Closes Gripper
 * 7. Moves up
 * 8. Closes BEMI
 * 9. Opens Gripper
 * 10. Sets Gripper to neutral
 *
 * @brief Retrieves a task list for the changing station place task
 *
 * @param node The ROS node to retrieve parameters from
 * @param BEMIIndex The index of the BEMI 1-3
 * @return A shared pointer to the task list
 */
std::shared_ptr<WzlPlanner::TaskList> CreateTaskPlaceBEMI(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks, int BEMIIndex)
{
  if (BEMIIndex < 1 || BEMIIndex > 3)
  {
    std::cout << "The BEMI index: " << std::to_string(BEMIIndex) << " in method 'CreateTaskPlaceBEMI' is not defined." << std::endl;
    return nullptr;
  }

  // Constants
  double placementOffsetZ = 0.2;

  double rotX = M_PI;
  double rotY = 0;
  double rotZ = -M_PI - M_PI / 4;

  // BEMI POSE DEF

  std::vector<double> ExecutionBEMIZ = get_parameter<std::vector<double>>(node, "positions.bemi.z", {0.320, 0.2885, 0.0});

  double placementBemiZ = ExecutionBEMIZ[BEMIIndex - 1] + placementOffsetZ;

  std::vector<double> BEMIX = get_parameter<std::vector<double>>(node, "positions.bemi.x", {0.3634, 0.1184, 0.0});
  std::vector<double> BEMIY = get_parameter<std::vector<double>>(node, "positions.bemi.y", {0.6815, 0.6178, 0.0});

  std::vector<double> BEMIRZOffset = get_parameter<std::vector<double>>(node, "positions.bemi.RZ_offset", {0.0475, -1.405985086238, 0.0});
  double BEMIrotZ = rotZ + BEMIRZOffset[BEMIIndex - 1];

  auto poseApproachBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], placementBemiZ, rotX, rotY, BEMIrotZ);
  auto poseExecuteBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], ExecutionBEMIZ[BEMIIndex - 1], rotX, rotY, BEMIrotZ);
  auto poseEndBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], placementBemiZ, rotX, rotY, BEMIrotZ);

  // BEMI TASK DEF
  auto taskApproachBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskExecuteBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskEndBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskApproachBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi);
  taskExecuteBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseExecuteBemi);
  taskEndBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBemi);

  // DEFINE TASK LIST
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
  taskList->AddTask(taskApproachBemi);

  if (BEMIIndex == 1)
  {
    taskList->AddTask(tasks->taskIoBemi1Open);
  }
  else if (BEMIIndex == 2)
  {
    taskList->AddTask(tasks->taskIoBemi2Open);
  }

  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskExecuteBemi);
  taskList->AddTask(tasks->taskSetSpeedCartesianFast);
  taskList->AddTask(tasks->taskIoGripperClose);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskEndBemi);
  taskList->AddTask(tasks->taskWait);

  if (BEMIIndex == 1)
  {
    taskList->AddTask(tasks->taskIoBemi1Close);
  }
  else if (BEMIIndex == 2)
  {
    taskList->AddTask(tasks->taskIoBemi2Close);
  }

  taskList->AddTask(tasks->taskIoGripperOpen);
  taskList->AddTask(tasks->taskIoGripperNeutral);

  return taskList;
}

std::shared_ptr<WzlPlanner::TaskList> CreateTaskPlaceBearingInBEMI(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks, int BEMIIndex)
{
  if (BEMIIndex < 1 || BEMIIndex > 3)
  {
    std::cout << "The BEMI index: " << std::to_string(BEMIIndex)
              << " in method 'CreateTaskPlaceBearingInBEMI' is not defined." << std::endl;
    return nullptr;
  }

  // Constants
  double placementOffsetZ = 0.25; // Offset for bearing placement height

  double rotX = M_PI;
  double rotY = 0;
   double rotZ = -M_PI - M_PI / 4;
  //double rotZ = 0;

  // Bearing placement poses
  std::vector<double> BearingX = get_parameter<std::vector<double>>(node, "positions.bearing.x", {0, 0.08982});
  std::vector<double> BearingY = get_parameter<std::vector<double>>(node, "positions.bearing.y", {0, 0.57029});
  std::vector<double> BearingZ = get_parameter<std::vector<double>>(node, "positions.bearing.z", {0, 0.33903});

  double placementBearingZ = BearingZ[BEMIIndex - 1] + placementOffsetZ;

  double bearingRotZ = rotZ;
  // Bearing rotation offset
  /*   std::vector<double> BearingRZOffset = get_parameter<std::vector<double>>(
        node, "positions.bearing.RZ_offset", {0.05, -1.4, 0.1});
    double bearingRotZ = rotZ + BearingRZOffset[BEMIIndex - 1]; */

  // Define poses
  auto poseApproachBearing = std::make_shared<WzlPlanner::Pose>(
      BearingX[BEMIIndex - 1], BearingY[BEMIIndex - 1], placementBearingZ, rotX, rotY, bearingRotZ);
  auto posePlaceBearing = std::make_shared<WzlPlanner::Pose>(
      BearingX[BEMIIndex - 1], BearingY[BEMIIndex - 1], BearingZ[BEMIIndex - 1], rotX, rotY, bearingRotZ);
  auto poseEndBearing = std::make_shared<WzlPlanner::Pose>(
      BearingX[BEMIIndex - 1], BearingY[BEMIIndex - 1], placementBearingZ, rotX, rotY, bearingRotZ);

  // Define tasks
  auto taskApproachBearing = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPlaceBearing = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskEndBearing = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskApproachBearing->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBearing);
  taskPlaceBearing->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePlaceBearing);
  taskEndBearing->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBearing);

  // Define task list
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  // Redundant check if BEMI is closed
  if (BEMIIndex == 1)
  {
    taskList->AddTask(tasks->taskIoBemi1Close);
  }
  else if (BEMIIndex == 2)
  {
    taskList->AddTask(tasks->taskIoBemi2Close);
  }

  // Add tasks to task list
  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
  taskList->AddTask(taskApproachBearing);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPlaceBearing);
  taskList->AddTask(tasks->taskIoGripperClose); // Check if we should close or open gripper here
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskEndBearing);
  taskList->AddTask(tasks->taskSetSpeedCartesianFast);
  taskList->AddTask(tasks->taskIoGripperNeutral);

  return taskList;
}

std::shared_ptr<WzlPlanner::TaskList> CreateTaskPickBearingFromBEMI(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks, int BEMIIndex)
{
  if (BEMIIndex < 1 || BEMIIndex > 3)
  {
    std::cout << "The BEMI index: " << std::to_string(BEMIIndex)
              << " in method 'CreateTaskPickBearingFromBEMI' is not defined." << std::endl;
    return nullptr;
  }

  // Constants
  double placementOffsetZ = 0.35; // Offset for bearing placement height

  double rotX = M_PI;
  double rotY = 0;
   double rotZ = -M_PI - M_PI / 4;
  //double rotZ = 0;

  // Bearing placement poses
  std::vector<double> BearingX = get_parameter<std::vector<double>>(node, "positions.bearing.x", {0.38283, 0.08982});
  std::vector<double> BearingY = get_parameter<std::vector<double>>(node, "positions.bearing.y", {0.64933, 0.57029});
  std::vector<double> BearingZ = get_parameter<std::vector<double>>(node, "positions.bearing.z", {0.3389, 0.33903});

  double placementBearingZ = BearingZ[BEMIIndex - 1] + placementOffsetZ;

  double bearingRotZ = rotZ;
  // Bearing rotation offset
  /*   std::vector<double> BearingRZOffset = get_parameter<std::vector<double>>(
        node, "positions.bearing.RZ_offset", {0.05, -1.4, 0.1});
    double bearingRotZ = rotZ + BearingRZOffset[BEMIIndex - 1]; */

  // Define poses
  auto poseApproachBearing = std::make_shared<WzlPlanner::Pose>(
      BearingX[BEMIIndex - 1], BearingY[BEMIIndex - 1], placementBearingZ, rotX, rotY, bearingRotZ);
  auto posePickBearing = std::make_shared<WzlPlanner::Pose>(
      BearingX[BEMIIndex - 1], BearingY[BEMIIndex - 1], BearingZ[BEMIIndex - 1], rotX, rotY, bearingRotZ);
  auto poseEndBearing = std::make_shared<WzlPlanner::Pose>(
      BearingX[BEMIIndex - 1], BearingY[BEMIIndex - 1], placementBearingZ, rotX, rotY, bearingRotZ);

  // Define tasks
  auto taskApproachBearing = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPickBearing = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskEndBearing = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskApproachBearing->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBearing);
  taskPickBearing->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePickBearing);
  taskEndBearing->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBearing);

  // Define task list
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  // Redundant check if BEMI is closed
  if (BEMIIndex == 1)
  {
    taskList->AddTask(tasks->taskIoBemi1Close);
  }
  else if (BEMIIndex == 2)
  {
    taskList->AddTask(tasks->taskIoBemi2Close);
  }

  // Add tasks to task list
  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
  taskList->AddTask(taskApproachBearing);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPickBearing);
  taskList->AddTask(tasks->taskIoGripperOpen); // Check if we should close or open gripper here
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskEndBearing);
  taskList->AddTask(tasks->taskSetSpeedCartesianFast);
  taskList->AddTask(tasks->taskIoGripperNeutral);

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
void UseCase1(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks)
{
  tasks->taskIoLampOrange->Execute();
  //tasks->taskIoAlarmOff->Execute();

  // auto node = WzlPlanner::ObjectContainer::Get()->GetNode();
  [[maybe_unused]] auto useOpcua = false;

  RCLCPP_INFO(node->get_logger(), "Initialize Pick & Place test.");

  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);

  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("RoboGripper", 0, 1);

  robot->SetGripper(gripper);

  RCLCPP_INFO(node->get_logger(), "Initialize Task Pick & Place");

  // Constants
  double rotX = M_PI;
  double rotY = 0;
  double rotZ = -M_PI - M_PI / 4;

  // INIT pose and task def
  auto poseInit = std::make_shared<WzlPlanner::Pose>(0.3122745752334595, 0.09810880571603775, 0.4534417390823364, rotX, rotY, rotZ);

  auto taskInitPose = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskInitPose->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseInit);

  // Change tool: Gripper -> deburring spindle
  auto taskGripperUnequip = GetChangingStationTaskPlace(node, 3);
  auto taskDeburringSpindleEquip = GetChangingStationTaskPick(node, 2);

  // Small Gripper Equip/Unequip
  auto taskSmallGripperEquip = GetChangingStationTaskPick(node, 4);
  auto taskSmallGripperUnequip = GetChangingStationTaskPlace(node, 4);

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
  auto taskGripperEquip = GetChangingStationTaskPick(node, 3);

  auto taskfollowtrajectory = std::make_shared<WzlPlanner::TaskFollowTrajectory>();

  auto pose1= std::make_shared<WzlPlanner::Pose>(0.35, 0.15, 0.55, rotX, rotY, rotZ);
  auto pose2= std::make_shared<WzlPlanner::Pose>(0.4, 0.4, 0.6, rotX, rotY, rotZ);
  auto pose3= std::make_shared<WzlPlanner::Pose>(0.1, 0.4, 0.6, rotX, rotY, rotZ);

  taskfollowtrajectory->AddPose(pose1);
  taskfollowtrajectory->AddPose(pose2);
  taskfollowtrajectory->AddPose(pose3);
  taskfollowtrajectory->SetId("TaskFollowTrajectory");

  ////// TASK SCHEDULING //////
  RCLCPP_INFO(node->get_logger(), "Execute Task Use Case 1");

  // setup custom task list
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  //HABE IRGENDWIE MIT DER PNEUMATIC PROBLEME, MUSS MAL SCHAUEN WAS GEÄNDERT WURDE UND WARUM ES NICHT MEHR FUNKTIONIERT

  // Set Pneumatics to neutral
  //taskList->AddTask(tasks->taskWait);
  //taskList->AddTask(tasks->taskIoGripperNeutral);
  //taskList->AddTask(tasks->taskIoDeburringSpindleDeactivate);
  //taskList->AddTask(tasks->taskIoDeburringSpindleAnpressdruckDeactivate);
  taskList->AddTask(tasks->taskIoLampGreen);
  taskList->AddTask(taskInitPose);

  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskfollowtrajectory);

  taskList->AddTask(tasks->taskWait);

  while (true)
  {
    if (!taskList->Execute())
    {
      RCLCPP_INFO(node->get_logger(), "Execution failed");
      //tasks->taskIoGripperNeutral->Execute();
      //tasks->taskIoDeburringSpindleDeactivate->Execute();
      //tasks->taskIoDeburringSpindleAnpressdruckDeactivate->Execute();
      tasks->taskIoLampRed->Execute(); // Failure -> Lamp red
      //tasks->taskIoAlarmOn->Execute();  // Failure -> Alarm on
      return;
    }

    rclcpp::spin_some(node);
  }

  RCLCPP_INFO(node->get_logger(), "Excecution successful");
}

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
  rclcpp::sleep_for(3000ms);
  auto misc_tasks = std::make_shared<MiscTasks>(node);
  rclcpp::sleep_for(3000ms);

  UseCase1(node, misc_tasks);

  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();

  return 0;
}