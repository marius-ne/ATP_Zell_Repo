#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <csignal>

#include <rclcpp/rclcpp.hpp>
#include "tf2_eigen/tf2_eigen.hpp"

#include "../include/SceneObjects/SceneObject.h"
#include "../include/ObjectContainer.h"
#include "../include/Tasks/TaskInclude.h"
#include "../include/Tasks/Atomic/TaskOpcuaRequest.h"

#include <math.h>
#include <memory>
#include <chrono>

//#include "../include/Tasks/misc_tasks.h"

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
  auto robot = std::make_shared<WzlPlanner::RobotIiwa>(node);
  auto scene = std::make_shared<WzlPlanner::Scene>(robot, node);
  auto ioInterfaceOpcUa = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  auto ioInterfaceModBus = std::make_shared<WzlPlanner::IoInterfaceModBus>(node);

  robot->SetGripper(std::make_shared<WzlPlanner::GripperMockup>("TestGripper"));

  RCLCPP_INFO(node->get_logger(), "Robot scheduler cell environment initialization start.");
  RCLCPP_INFO(node->get_logger(), "Initialize ObjectContainer");

  WzlPlanner::ObjectContainer::Get()->Initialize(
      //ioInterfaceModBus,
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
  std::shared_ptr<WzlPlanner::TaskSetRobotValueVelocity> taskSetSpeedCartesianDeburring;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachSpindel;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachGripper;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachSmallGripper;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachSpindel;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachGripper;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachSmallGripper;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachWorkpiece;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachWorkpiece;

  void UpdateWorkpieceTask(int partType, int orientation = 0) {
      // Aktualisiere das bestehende taskAttachWorkpiece-Objekt
      taskAttachWorkpiece = std::make_shared<WzlPlanner::TaskPartAttach>("workpiece", partType, orientation);
      taskAttachWorkpiece->SetId("taskAttachWorkpiece_Type" + std::to_string(partType) + 
                              (orientation != 0 ? "_Rot" + std::to_string(orientation) : ""));
  }

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
    double cartesian_deburring = get_parameter<double>(node, "speeds.cartesian_deburring", 1.0);

    taskSetSpeedPtp = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(ptp_speed, 1.0, 0);
    taskSetSpeedCartesianFast = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(cartesian_fast, 0.1, 1);
    taskSetSpeedCartesianSlow = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(cartesian_slow, 0.05, 1);
    taskSetSpeedCartesianDeburring = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(cartesian_deburring, 0.5, 1);

    taskSetSpeedPtp->SetId("taskSetSpeedPtp");
    taskSetSpeedCartesianFast->SetId("taskSetSpeedCartesianFast");
    taskSetSpeedCartesianSlow->SetId("taskSetSpeedCartesianSlow");
    taskSetSpeedCartesianDeburring->SetId("taskSetSpeedCartesianDeburring");

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

    taskAttachWorkpiece = std::make_shared<WzlPlanner::TaskPartAttach>("workpiece");
    taskAttachWorkpiece->SetId("taskAttachWorkpiece");

    taskDetachWorkpiece = std::make_shared<WzlPlanner::TaskPartDetach>("workpiece");
    taskDetachWorkpiece->SetId("taskDetachWorkpiece");



    RCLCPP_INFO(node->get_logger(), "Miscellaneous tasks initialized.");
  }
};

std::vector<std::vector<double>> LoadNCFile(const std::string& filename) {
    std::vector<std::vector<double>> points;
    
    // Get the package share directory
    std::string package_share_dir = ament_index_cpp::get_package_share_directory("robo_planner");
    std::string filepath = package_share_dir + "/config/" + filename;
    
    std::ifstream file(filepath);
    if (!file.is_open()) {
        RCLCPP_ERROR(rclcpp::get_logger("robo_planner"), "Error opening NC file: %s", filepath.c_str());
        return points;
    }

    std::vector<double> last_point(3, std::numeric_limits<double>::infinity()); // Initialize with infinity to ensure first point is added

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '(' || line[0] == '%') {
            continue;
        }

        // Look for lines containing X, Y, Z coordinates
        if (line.find('X') != std::string::npos || 
            line.find('Y') != std::string::npos || 
            line.find('Z') != std::string::npos) {
            
            std::vector<double> point(3, 0.0); // Initialize with [0,0,0]
            
            // Parse X coordinate
            size_t xPos = line.find('X');
            if (xPos != std::string::npos) {
                size_t nextChar = line.find_first_of(" XYZF", xPos + 1);
                std::string xVal = line.substr(xPos + 1, nextChar - xPos - 1);
                //point[0] = std::stod(xVal) / 1000.0;
                point[0] = (std::stod(xVal) / 4000.0) + 0.3;
            }
            
            // Parse Y coordinate
            size_t yPos = line.find('Y');
            if (yPos != std::string::npos) {
                size_t nextChar = line.find_first_of(" XYZF", yPos + 1);
                std::string yVal = line.substr(yPos + 1, nextChar - yPos - 1);
                //point[1] = std::stod(yVal) / -1000.0;
                point[1] = (std::stod(yVal) / -4000.0) + 0.3;
            }
            
            // Parse Z coordinate
            size_t zPos = line.find('Z');
            if (zPos != std::string::npos) {
                size_t nextChar = line.find_first_of(" XYZF", zPos + 1);
                std::string zVal = line.substr(zPos + 1, nextChar - zPos - 1);
                //point[2] = std::stod(zVal) / 1000.0;
                point[2] = 0.5;
            }
            
            // Only add point if it's different from the last point
            if (point[0] != last_point[0] || 
                point[1] != last_point[1] || 
                point[2] != last_point[2]) {
                points.push_back(point);
                last_point = point;
            }
        }
    }

    file.close();
    RCLCPP_INFO(rclcpp::get_logger("robo_planner"), "Successfully loaded NC file with %ld points (after removing duplicates)", points.size());
    return points;
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
  taskMove1->SetId("ChangingStationPlace_Move1");

  auto taskMove2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove2->SetTargetPose(targetPose2);
  taskMove2->SetId("ChangingStationPlace_Move2");

  auto taskMove3 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove3->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove3->SetTargetPose(targetPose3);
  taskMove3->SetId("ChangingStationPlace_Move3");

  auto taskMove4 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove4->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove4->SetTargetPose(targetPose4);
  taskMove4->SetId("ChangingStationPlace_Move4");

  auto taskMove5 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove5->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove5->SetTargetPose(targetPose5);
  taskMove5->SetId("ChangingStationPlace_Move5");

  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(taskMove1);
  taskList->AddTask(taskMove2);
  taskList->AddTask(taskMove3);
  taskList->AddTask(taskMove4);
  taskList->AddTask(taskMove5);

  taskList->SetId("ChangingStationPlace");

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
  taskMove1->SetId("ChangingStationPick_Move1");

  auto taskMove2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove2->SetTargetPose(targetPose2);
  taskMove2->SetId("ChangingStationPick_Move2");

  auto taskMove3 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove3->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove3->SetTargetPose(targetPose3);
  taskMove3->SetId("ChangingStationPick_Move3");

  auto taskMove4 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove4->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove4->SetTargetPose(targetPose4);
  taskMove4->SetId("ChangingStationPick_Move4");

  auto taskMove5 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskMove5->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian);
  taskMove5->SetTargetPose(targetPose5);
  taskMove5->SetId("ChangingStationPick_Move5");

  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(taskMove1);
  taskList->AddTask(taskMove2);
  taskList->AddTask(taskMove3);
  taskList->AddTask(taskMove4);
  taskList->AddTask(taskMove5);

  taskList->SetId("ChangingStationPick");

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
  //Workpiece orientation an partType defined through the PCNr and PCIndex 
  int partType=1;
  int workpieceOrientation=0;

  if (PCNr == 1) {
    if (PCIndex >= 1 && PCIndex <= 5) {
        partType = 1;//lower Part
        workpieceOrientation = 0;
    } 
    // evt andere Orientierungen
    else if (PCIndex >= 6 && PCIndex <= 8) {
        partType = 1; 
        workpieceOrientation = 90;
    }
  } 
// PCNr 2: oberes Teil
  else if (PCNr == 2) {
      partType = 2; // upper Part
  }
  if (PCNr < 1 || PCNr > 2)
  {
    std::cout << "The Part Carrier number: " << std::to_string(PCNr) << " in method 'CreateTaskPickPC' is not defined." << std::endl;
    return nullptr;
  }

  // Constants
  double placementOffsetZ = 0.2;

  double rotX = M_PI;
  double rotY = 0;
  double rotZ =0.5;

  std::vector<double> PCX;
  std::vector<double> PCY;
  std::vector<double> PCZ;

std::cout << PCNr<< std::endl;
  if (PCNr == 1)// Koordinaten
  {
    PCX = get_parameter<std::vector<double>>(node, "positions.PC.x_1", {0.29255, -0.456, -0.561, -0.666, -0.771, -0.416, -0.589, -0.762});//nur Standartwerte falss parameter nicht gefunden werden -> richtige Parameter in cell_config.yaml
    PCY = get_parameter<std::vector<double>>(node, "positions.PC.y_1", {-0.41572, 0.341, 0.341, 0.341, 0.341, 0.144, 0.144, 0.144});
    PCZ = get_parameter<std::vector<double>>(node, "positions.PC.z_1", {0.1883, 0.260, 0.260, 0.260, 0.260, 0.230, 0.230, 0.230});//z=0,34252
  }
  else if (PCNr == 2)
  {
    PCX = get_parameter<std::vector<double>>(node, "positions.PC.x_2", {0.29021, 0.0});
    PCY = get_parameter<std::vector<double>>(node, "positions.PC.y_2", {0.42433, 0.0});
    PCZ = get_parameter<std::vector<double>>(node, "positions.PC.z_2", {0.16713, 0.0});


  }

  int PC_index = PCIndex - 1;

  double placementPCZ = PCZ[PC_index] + placementOffsetZ;
  std::cout << PCNr<< std::endl;
  auto posePCApproach = std::make_shared<WzlPlanner::Pose>(PCX[PC_index], PCY[PC_index], placementPCZ, rotX, rotY, rotZ);
  auto posePCExecute = std::make_shared<WzlPlanner::Pose>(PCX[PC_index], PCY[PC_index], PCZ[PC_index], rotX, rotY, rotZ);
  auto posePCEnd = std::make_shared<WzlPlanner::Pose>(PCX[PC_index], PCY[PC_index], placementPCZ, rotX, rotY, rotZ);

  // Part Carrier, part: TASK DEF
  auto taskPCApproach = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPCExecute = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPCEnd = std::make_shared<WzlPlanner::TaskMoveToPose>();

  tasks->UpdateWorkpieceTask(partType, workpieceOrientation);

  taskPCApproach->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(posePCApproach);
  taskPCApproach->SetId("taskPCApproach");
  taskPCExecute->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePCExecute);
  taskPCExecute->SetId("taskPCExecute");
  taskPCEnd->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePCEnd);
  taskPCEnd->SetId("taskPCEnd");

  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(tasks->taskSetSpeedCartesianFast);
  taskList->AddTask(taskPCApproach);
  taskList->AddTask(tasks->taskIoBemi2Close); //Greifer gerade über Bemi2 angesteuert!!! 
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPCExecute);
  taskList->AddTask(tasks->taskIoBemi2Open);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskAttachWorkpiece);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPCEnd);
  taskList->SetId("PCPick");

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
  double rotZ = 0.5;

  std::vector<double> PCX;
  std::vector<double> PCY;
  std::vector<double> PCZ;

  if (PCNr == 1)// Koordinaten
  {
    PCX = get_parameter<std::vector<double>>(node, "positions.PC.x_1", {0.29255, -0.456, -0.561, -0.666, -0.771, -0.416, -0.589, -0.762});//nur Standartwerte falss parameter nicht gefunden werden -> richtige Parameter in cell_config.yaml
    PCY = get_parameter<std::vector<double>>(node, "positions.PC.y_1", {-0.41572, 0.341, 0.341, 0.341, 0.341, 0.144, 0.144, 0.144});
    PCZ = get_parameter<std::vector<double>>(node, "positions.PC.z_1", {0.1883, 0.260, 0.260, 0.260, 0.260, 0.230, 0.230, 0.230});//z=0,34252
  }
  else if (PCNr == 2)
  {
    PCX = get_parameter<std::vector<double>>(node, "positions.PC.x_2", {0.29021, 0.0});
    PCY = get_parameter<std::vector<double>>(node, "positions.PC.y_2", {0.42433, 0.0});
    PCZ = get_parameter<std::vector<double>>(node, "positions.PC.z_2", {0.16713, 0.0});


  }

  int PC_index = PCIndex - 1;

  double placementPCZ = PCZ[PC_index] + placementOffsetZ;

  auto posePCApproach = std::make_shared<WzlPlanner::Pose>(PCX[PC_index], PCY[PC_index], placementPCZ, rotX, rotY, rotZ);
  auto posePCExecute = std::make_shared<WzlPlanner::Pose>(PCX[PC_index], PCY[PC_index], PCZ[PC_index], rotX, rotY, rotZ);
  auto posePCEnd = std::make_shared<WzlPlanner::Pose>(PCX[PC_index], PCY[PC_index], placementPCZ, rotX, rotY, rotZ);

  // Part Carrier 1, part 1: TASK DEF
  auto taskPCApproach = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPCExecute = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskPCEnd = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskPCApproach->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(posePCApproach);
  taskPCApproach->SetId("taskPCApproach");
  taskPCExecute->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePCExecute);
  taskPCExecute->SetId("taskPCExecute");
  taskPCEnd->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePCEnd);
  taskPCEnd->SetId("taskPCEnd");

  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
  taskList->AddTask(taskPCApproach);
  taskList->AddTask(tasks->taskIoBemi2Open); 
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPCExecute);
  taskList->AddTask(tasks->taskIoBemi2Close); //Greifer gerade über Bemi2 angesteuert!!!
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskDetachWorkpiece);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPCEnd);
  
  taskList->SetId("PCPlace");

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
 * @param PartType The Part Type 1-2, Big 1, Small 2
 * @return A shared pointer to the task list
 */
std::shared_ptr<WzlPlanner::TaskList> CreateTaskPickBEMI(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks, int BEMIIndex, int partType, int workpieceOrientation)
{

  if (BEMIIndex < 1 || BEMIIndex > 2)
  {
    std::cout << "The BEMI index: " << std::to_string(BEMIIndex) << " in method 'CreateTaskPickBEMI' is not defined." << std::endl;
    return nullptr;
  }

  if (partType < 1 || partType > 2)
  {
    std::cout << "The Part Type: " << std::to_string(partType) << " in method 'CreateTaskPlaceBEMI' is not defined." << std::endl;
    return nullptr;
  }

  // Constants
  double placementOffsetZ = 0.2;

  double rotX = M_PI;
  double rotY = 0;
  double rotZ = -0;

  // BEMI POSE DEF

  //Positionen nur fallback: richtige Definition in cell_config.yaml
std::vector<double> ExecutionBEMIZ = get_parameter<std::vector<double>>(node, "positions.bemi.z", {0.17558, 0.2885, 0.0});//unterschiedliche Koordinaten für Bemi 1 und 2, da Part1 in Bemi1 unten, Part 2 in Bemi2 Oben

std::vector<double> BEMIX = get_parameter<std::vector<double>>(node, "positions.bemi.x", {0.54009, 0.1184, 0.0});
std::vector<double> BEMIY = get_parameter<std::vector<double>>(node, "positions.bemi.y", {0.05915, 0.6178, 0.0});
std::vector<double> BEMIRZOffset = get_parameter<std::vector<double>>(node, "positions.bemi.RZ_offset", {0.0475, -1.405985086238, 0.0});

double placementBemiZ = ExecutionBEMIZ[BEMIIndex - 1] + placementOffsetZ;
double BEMIrotZ = rotZ + BEMIRZOffset[BEMIIndex - 1];

auto poseApproachBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], placementBemiZ, rotX, rotY, BEMIrotZ);
auto poseExecuteBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], ExecutionBEMIZ[BEMIIndex - 1], rotX, rotY, BEMIrotZ);
auto poseEndBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], placementBemiZ, rotX, rotY, BEMIrotZ);

// BEMI TASK DEF
auto taskApproachBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();
auto taskExecuteBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();
auto taskEndBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();

tasks->UpdateWorkpieceTask(partType, workpieceOrientation);

taskApproachBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi);
taskApproachBemi->SetId("taskApproachBemi");
taskExecuteBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseExecuteBemi);
taskExecuteBemi->SetId("taskExecuteBemi");
taskEndBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBemi);
taskEndBemi->SetId("taskEndBemi");

// DEFINE TASK LIST
auto taskList = std::make_shared<WzlPlanner::TaskList>();

taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
taskList->AddTask(taskApproachBemi);
taskList->AddTask(tasks->taskIoBemi2Close);
taskList->AddTask(tasks->taskWait);
taskList->AddTask(taskExecuteBemi);
taskList->AddTask(tasks->taskSetSpeedCartesianFast);
taskList->AddTask(tasks->taskIoBemi2Open); //Greifer gerade über Bemi2 angesteuert!!! öffnet greifer
taskList->AddTask(tasks->taskIoBemi2Open);
taskList->AddTask(tasks->taskWait);
taskList->AddTask(tasks->taskAttachWorkpiece);
taskList->AddTask(tasks->taskWait);
taskList->AddTask(taskEndBemi);

taskList->SetId("BemiPick");

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
 * @param PartType The Part Type, Big 1, Small 2
 * @return A shared pointer to the task list
 */
std::shared_ptr<WzlPlanner::TaskList> CreateTaskPlaceBEMI(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks, int BEMIIndex, int PartType)
{
  if (BEMIIndex < 1 || BEMIIndex > 2)
  {
    std::cout << "The BEMI index: " << std::to_string(BEMIIndex) << " in method 'CreateTaskPlaceBEMI' is not defined." << std::endl;
    return nullptr;
  }

  if (PartType < 1 || PartType > 2)
  {
    std::cout << "The Part Type: " << std::to_string(PartType) << " in method 'CreateTaskPlaceBEMI' is not defined." << std::endl;
    return nullptr;
  }

  // Constants
  double placementOffsetZ = 0.2;

  double rotX = M_PI;
  double rotY = 0;
  double rotZ = 0;
  

//Positionen nur fallback: richtige Definition in cell_config.yaml
std::vector<double> ExecutionBEMIZ = get_parameter<std::vector<double>>(node, "positions.bemi.z", {0.17558, 0.2885, 0.0});//unterschiedliche Koordinaten für Bemi 1 und 2, da Part1 in Bemi1 unten, Part 2 in Bemi2 Oben

  std::vector<double> BEMIX = get_parameter<std::vector<double>>(node, "positions.bemi.x", {0.54009, 0.1184, 0.0});
  std::vector<double> BEMIY = get_parameter<std::vector<double>>(node, "positions.bemi.y", {0.05915, 0.6178, 0.0});
  std::vector<double> BEMIRZOffset = get_parameter<std::vector<double>>(node, "positions.bemi.RZ_offset", {0.0475, -1.405985086238, 0.0});
  
  double placementBemiZ = ExecutionBEMIZ[BEMIIndex - 1] + placementOffsetZ;
  double BEMIrotZ = rotZ + BEMIRZOffset[BEMIIndex - 1];

  auto poseApproachBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], placementBemiZ, rotX, rotY, BEMIrotZ);
  auto poseExecuteBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], ExecutionBEMIZ[BEMIIndex - 1], rotX, rotY, BEMIrotZ);
  auto poseEndBemi = std::make_shared<WzlPlanner::Pose>(BEMIX[BEMIIndex - 1], BEMIY[BEMIIndex - 1], placementBemiZ, rotX, rotY, BEMIrotZ);

  // BEMI TASK DEF
  auto taskApproachBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskExecuteBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();
  auto taskEndBemi = std::make_shared<WzlPlanner::TaskMoveToPose>();

  taskApproachBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseApproachBemi);
  taskApproachBemi->SetId("taskApproachBemi");
  taskExecuteBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseExecuteBemi);
  taskExecuteBemi->SetId("taskExecuteBemi");
  taskEndBemi->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBemi);
  taskEndBemi->SetId("taskEndBemi");

  // DEFINE TASK LIST
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
  taskList->AddTask(taskApproachBemi);


  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskExecuteBemi);
  taskList->AddTask(tasks->taskSetSpeedCartesianFast);
  taskList->AddTask(tasks->taskIoBemi2Close); //Greifer gerade über Bemi2 angesteuert!!! öffnet greifer
  taskList->AddTask(tasks->taskIoBemi2Close);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskDetachWorkpiece);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskEndBemi);
  
  taskList->SetId("BemiPlace");

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
  double placementOffsetZ = 0.25; // Offset height befor bearing placement

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
  taskApproachBearing->SetId("taskApproachBearing");
  taskPlaceBearing->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePlaceBearing);
  taskPlaceBearing->SetId("taskPlaceBearing");
  taskEndBearing->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBearing);
  taskEndBearing->SetId("taskEndBearing");

  // Define task list
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  /**Redundant check if BEMI is closed | wml: not needed TODO: remove
  if (BEMIIndex == 1)
  {
    taskList->AddTask(tasks->taskIoBemi1Close);
  }
  else if (BEMIIndex == 2)
  {
    taskList->AddTask(tasks->taskIoBemi2Close);
  }
  **/

  // TODO add BEMI 3 close and remove BEMI 1 & 2 Close since bearing is never inserted in BEMI 1 & 2

  // Add tasks to task list
  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
  taskList->AddTask(taskApproachBearing);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPlaceBearing);
  taskList->AddTask(tasks->taskIoGripperClose);
  taskList->AddTask(tasks->taskIoGripperClose);
  taskList->AddTask(tasks->taskIoGripperClose);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
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
  taskApproachBearing->SetId("taskApproachBearing");
  taskPickBearing->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(posePickBearing);
  taskPickBearing->SetId("taskPickBearing");
  taskEndBearing->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseEndBearing);
  taskEndBearing->SetId("taskEndBearing");

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
  taskList->AddTask(tasks->taskIoGripperOpen);
  taskList->AddTask(tasks->taskIoGripperOpen);
  taskList->AddTask(tasks->taskWait);
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
  taskMoveTrjajectory->SetId("MoveInCircle");

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
 * @brief Creates a task list for executing deburring operation
 *
 * @param node ROS node to access parameters and logging
 * @param tasks Shared pointer to miscellaneous tasks for spindle control
 * @param points Vector of 3D points defining the deburring trajectory
 * @param BEMIIndex Index of the BEMI workstation (1-3)
 * @return A shared pointer to TaskList containing trajectory and spindle control
 */
std::shared_ptr<WzlPlanner::TaskList> CreateTaskPerformDeburr(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks, const std::vector<std::vector<double>> &points, int BEMIIndex)
{
    auto deburrtasklist = std::make_shared<WzlPlanner::TaskList>();
    
    // Constants for initial orientation
    double rotX = M_PI;
    double rotY = 0;
    double rotZ = -M_PI - M_PI / 4;

    // Create trajectory task
    auto trajectory = std::make_shared<WzlPlanner::TaskFollowTrajectory>();
    trajectory->SetId("DeburTrajectory");

    // Add each point to trajectory
    for(const auto& point : points) {
        if(point.size() >= 3) {
            auto pose = std::make_shared<WzlPlanner::Pose>(
                point[0],  // X
                point[1],  // Y
                point[2],  // Z
                rotX, rotY, rotZ
            );
            trajectory->AddPose(pose);
        }
    }

    // Setup deburring sequence
    deburrtasklist->AddTask(tasks->taskSetSpeedCartesianSlow);
    //deburrtasklist->AddTask(tasks->taskIoDeburringSpindleActivate);
    //deburrtasklist->AddTask(tasks->taskIoDeburringSpindleAnpressdruckActivate);
    deburrtasklist->AddTask(tasks->taskWait);
    deburrtasklist->AddTask(trajectory);
    //deburrtasklist->AddTask(tasks->taskIoDeburringSpindleDeactivate);
    //deburrtasklist->AddTask(tasks->taskIoDeburringSpindleAnpressdruckDeactivate);
    
    return deburrtasklist;
}


/**
 * 
 *
 * @brief Retrieves a task list for the photo positions task
 *
 * @param node The ROS node to retrieve parameters from
 * @return A shared pointer to the task list
 */
 std::shared_ptr<WzlPlanner::TaskList> CreateTaskPhotoPositions(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks)
 {

   double rotX = M_PI;
   double rotY = 0;
   double rotZ = M_PI ;
 
   auto pose1 = std::make_shared<WzlPlanner::Pose>( 0.4,  0.4, 0.55, rotX, rotY, 0);
   auto pose2 = std::make_shared<WzlPlanner::Pose>( 0.5,  0  , 0.55, rotX, rotY, 0);
   auto pose3 = std::make_shared<WzlPlanner::Pose>( 0.4, -0.4, 0.55, rotX, rotY, 0);
   auto pose4 = std::make_shared<WzlPlanner::Pose>( 0  , -0.5, 0.55, rotX, rotY, rotZ);
   auto pose5 = std::make_shared<WzlPlanner::Pose>(-0.4, -0.4, 0.55, rotX, rotY, rotZ);
   auto pose6 = std::make_shared<WzlPlanner::Pose>(-0.5,  0  , 0.55, rotX, rotY, rotZ);
   auto pose7 = std::make_shared<WzlPlanner::Pose>(-0.4,  0.4, 0.55, rotX, rotY, rotZ);
   auto pose8 = std::make_shared<WzlPlanner::Pose>( 0  ,  0.5, 0.55, rotX, rotY, rotZ);
 
   auto taskPose1= std::make_shared<WzlPlanner::TaskMoveToPose>();
   auto taskPose2= std::make_shared<WzlPlanner::TaskMoveToPose>();
   auto taskPose3= std::make_shared<WzlPlanner::TaskMoveToPose>();
   auto taskPose4= std::make_shared<WzlPlanner::TaskMoveToPose>();
   auto taskPose5= std::make_shared<WzlPlanner::TaskMoveToPose>();
   auto taskPose6= std::make_shared<WzlPlanner::TaskMoveToPose>();
   auto taskPose7= std::make_shared<WzlPlanner::TaskMoveToPose>();
   auto taskPose8= std::make_shared<WzlPlanner::TaskMoveToPose>();

   taskPose1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose1); taskPose1->SetId("taskPose1");
   taskPose2->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose2); taskPose2->SetId("taskPose2");
   taskPose3->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose3); taskPose3->SetId("taskPose3");
   taskPose4->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose4); taskPose4->SetId("taskPose4");
   taskPose5->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose5); taskPose5->SetId("taskPose5");
   taskPose6->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose6); taskPose6->SetId("taskPose6");
   taskPose7->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose7); taskPose7->SetId("taskPose7");
   taskPose8->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose8); taskPose8->SetId("taskPose8");

   auto taskList = std::make_shared<WzlPlanner::TaskList>();
   taskList->SetId("PhotoPositions");
   taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
   taskList->AddTask(taskPose1);
   taskList->AddTask(tasks->taskWait);
   taskList->AddTask(taskPose2);
   taskList->AddTask(tasks->taskWait);
   taskList->AddTask(taskPose3);
   taskList->AddTask(tasks->taskWait);
   taskList->AddTask(taskPose4);
   taskList->AddTask(tasks->taskWait);
   taskList->AddTask(taskPose5);
   taskList->AddTask(tasks->taskWait);
   taskList->AddTask(taskPose6);
   taskList->AddTask(tasks->taskWait);
   taskList->AddTask(taskPose7);
   taskList->AddTask(tasks->taskWait);
   taskList->AddTask(taskPose8);

   return taskList;
 }


void UseCase2(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks)
{
  tasks->taskIoLampOrange->Execute();

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
  auto poseInit = std::make_shared<WzlPlanner::Pose>(0.4, 0.1, 0.5, rotX, rotY, rotZ); //0.3122745752334595, 0.09810880571603775, 0.4534417390823364,
  
  // Part 1 Posen
  auto pose1 = std::make_shared<WzlPlanner::Pose>(0.29255, -0.41572, 0.45, rotX, rotY, 0.5);  
  auto pose2 = std::make_shared<WzlPlanner::Pose>(0.29255, -0.41572, 0.1883, rotX, rotY, 0.5); // Pose Aufnahme Part 1 in PC1 1,0472
  auto pose3 = std::make_shared<WzlPlanner::Pose>(0.54009, 0.05915, 0.45, rotX, rotY, 1.63075);
  auto pose4 = std::make_shared<WzlPlanner::Pose>(0.54009, 0.05915, 0.17558, rotX, rotY, 1.63075); // Pose Ablage Part 1 in Tool1 

  // Part 2 Posen 
  auto pose5 = std::make_shared<WzlPlanner::Pose>(0.29021, 0.42433, 0.45, rotX, rotY, 0.5);  
  auto pose6 = std::make_shared<WzlPlanner::Pose>(0.29021, 0.42433, 0.16713, rotX, rotY, 0.5); // Pose Aufnahme Part 2 in PC2 
  auto pose7 = std::make_shared<WzlPlanner::Pose>(0.53988, 0.030554, 0.45, rotX, rotY, -1.4932);
  auto pose8 = std::make_shared<WzlPlanner::Pose>(0.53988, 0.030554, 0.185, rotX, rotY, -1.4932); // Pose Ablage Part 2 in Tool1 
  

  // =========== Init & Standard Posen =========== //
  auto taskInitPose = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskInitPose->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseInit);
  taskInitPose->SetId("InitPose");
  //======== Posen für Handling Part 1 aus PC1 ======//
  auto taskPose1 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // P2P Bewegung zu Einfahrtposition PC1
  taskPose1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose1);
  taskPose1->SetId("Pose1");

  auto taskPose2 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Gerade Einfahrbewegung in PC1
  taskPose2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose2);
  taskPose2->SetId("Pose2");

  auto taskPose3 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Gerade Ausfahrbewegung aus PC1
  taskPose3->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose1);
  taskPose3->SetId("Pose3");

  auto taskPose4 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // P2P Bewegung zu Einfahrtposition Tool 1
  taskPose4->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose3);
  taskPose4->SetId("Pose4");

  auto taskPose5 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Gerade Einfahrbewegung in Tool 1
  taskPose5->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose4);
  taskPose5->SetId("Pose5");

  auto taskPose6 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Gerade Aufahren aus Tool 1
  taskPose6->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose3);
  taskPose6->SetId("Pose6");

  //======== Posen für Handling Part 2 aus PC2 ======//

  auto taskPose7 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // P2P Bewegung zu Einfahrtposition PC1
  taskPose7->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose5);
  taskPose7->SetId("Pose7");

  auto taskPose8 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Gerade Einfahrbewegung in PC1
  taskPose8->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose6);
  taskPose8->SetId("Pose8");

  auto taskPose9 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Gerade Ausfahrbewegung aus PC1
  taskPose9->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose5);
  taskPose9->SetId("Pose9");

  auto taskPose10 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // P2P Bewegung zu Einfahrtposition Tool 1
  taskPose10->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose7);
  taskPose10->SetId("Pose10");

  auto taskPose11 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Gerade Einfahrbewegung in Tool 1
  taskPose11->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose8);
  taskPose11->SetId("Pose11");

  auto taskPose12 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Gerade Aufahren aus Tool 1
  taskPose12->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose7);
  taskPose12->SetId("Pose12");

  
  ////// TASK SCHEDULING //////
  RCLCPP_INFO(node->get_logger(), "Execute Task Use Case 2");

  // setup custom task list
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  // Set Pneumatics to neutral
  // evt alle nicht nötig
  //taskList->AddTask(tasks->taskIoGripperNeutral);
  //taskList->AddTask(tasks->taskIoDeburringSpindleDeactivate);
  //taskList->AddTask(tasks->taskIoDeburringSpindleAnpressdruckDeactivate);
  //taskList->AddTask(tasks->taskIoLampGreen);
  taskList->AddTask(tasks->taskWait); 
  //taskList->AddTask(tasks->taskAttachGripper); 
  //------------------- Turn cell to neutral position -------------------//
  taskList->AddTask(taskInitPose);
  taskList->AddTask(taskPose1);
  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
  taskList->AddTask(tasks->taskIoBemi2Close); //Greifer gerade über Bemi2 angesteuert!!! 
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPose2);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi2Open);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPose3);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPose4);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPose5);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi2Close); //Greifer gerade über Bemi2 angesteuert!!! 
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPose6);

  //Pick up part 2
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPose7);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPose8);
  taskList->AddTask(tasks->taskIoBemi2Open);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPose9);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPose10);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPose11);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi2Close); //Greifer gerade über Bemi2 angesteuert!!! 
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(taskPose12);
  taskList->AddTask(tasks->taskWait);

  //------------------- Pick Part 1&2 from PC & Place parts in BEMI 1&2 -------------------//
  
  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);


  taskList->AddTask(taskInitPose);


  while (true)
  {
    if (!taskList->Execute())
    {
      RCLCPP_INFO(node->get_logger(), "Execution failed");

      return;
    }

    rclcpp::spin_some(node);
  }

  RCLCPP_INFO(node->get_logger(), "Execution successful");
}

void UseCase1(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks)
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

  // Constants
  double rotX = M_PI;
  double rotY = 0;
  double rotZ = -M_PI - M_PI / 4;

  // INIT pose and task def
  auto poseInit = std::make_shared<WzlPlanner::Pose>(0.4, 0.1, 0.5, rotX, rotY, rotZ);

  auto taskInitPose = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskInitPose->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseInit);
  taskInitPose->SetId("InitPose");

 

  // TASK SCHEDULING 
  RCLCPP_INFO(node->get_logger(), "Execute Task Use Case 3");
  // setup custom task list
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  // Set Pneumatics to neutral
  //taskList->AddTask(tasks->taskIoGripperNeutral);

  taskList->AddTask(tasks->taskWait); 
  taskList->AddTask(tasks->taskAttachGripper);

  //------------------- Turn cell to neutral position -------------------//
  taskList->AddTask(taskInitPose);
 
  taskList->AddTask(tasks->taskSetSpeedPtp);

  //------------------- Pick Part 1&2 from PC & Place parts in BEMI 1&2 -------------------//
  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);

  taskList->AddTask(CreateTaskPhotoPositions(node, tasks));
  taskList->AddTask(taskInitPose);

  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
  //Pick Part 1 & Place parts in BEMI 1(unten)
  taskList->AddTask(CreateTaskPickPC(node, tasks, 1, 1));
  taskList->AddTask(CreateTaskPlaceBEMI(node, tasks, 1, 1)); 
  taskList->AddTask(taskInitPose);
  
  //Pick Part 2 & Place parts in BEMI 2(selber Bemi, oben)
  taskList->AddTask(CreateTaskPickPC(node, tasks, 1, 2));
  taskList->AddTask(CreateTaskPlaceBEMI(node, tasks, 2, 2));
  
  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);

  taskList->AddTask(taskInitPose);

  //return Part 2
  taskList->AddTask(CreateTaskPickBEMI(node, tasks, 2, 2,0));
  taskList->AddTask(CreateTaskPlacePC(node, tasks, 1, 2));
  taskList->AddTask(taskInitPose);
  //return Part 1  
  taskList->AddTask(CreateTaskPickBEMI(node, tasks, 1, 1,0));
  taskList->AddTask(CreateTaskPlacePC(node, tasks, 1, 1));
  taskList->AddTask(taskInitPose);
  
  //taskList->AddTask(CreateTaskPerformDeburr(node, tasks, LoadNCFile("Toolpath_Body_v0.5_Leftt Side (copy).nc"), 1));

  while (true)
  {
    if (!taskList->Execute())
    {
      RCLCPP_INFO(node->get_logger(), "Execution failed");
      auto failuretasks = std::make_shared<WzlPlanner::TaskList>();
      failuretasks->SetId("FailureTasks");

      failuretasks->AddTask(tasks->taskIoLampRed);
      failuretasks->AddTask(tasks->taskIoGripperNeutral);
      failuretasks->AddTask(tasks->taskIoDeburringSpindleDeactivate);
      failuretasks->AddTask(tasks->taskIoDeburringSpindleAnpressdruckDeactivate);

      failuretasks->Execute();
      return;
    }

    rclcpp::spin_some(node);
  }

  RCLCPP_INFO(node->get_logger(), "Execution successful");
}

void UseCaseTestModBus(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks)
{

  RCLCPP_INFO(node->get_logger(), "Initialize ModBus Test.");

  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("RoboGripper", 0, 1);

  robot->SetGripper(gripper);

  // Constants
  double rotX = M_PI;
  double rotY = 0;
  //double rotZ = -M_PI - M_PI / 4;
  double rotZ = 0;

  // INIT pose and task def
  auto poseInit = std::make_shared<WzlPlanner::Pose>(0.3, 0.3, 0.3, rotX, rotY, rotZ);
  auto pose1 = std::make_shared<WzlPlanner::Pose>(-0.3, 0.3, 0.3, rotX, rotY, rotZ);
  auto pose2 = std::make_shared<WzlPlanner::Pose>(-0.3, 0.3, 0.1, rotX, rotY, rotZ);

  auto taskInitPose = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskInitPose->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseInit);
  taskInitPose->SetId("InitPose");

  auto taskPose1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskPose1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose1);
  taskPose1->SetId("Pose1");

  auto taskPose2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskPose2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose2);
  taskPose2->SetId("Pose2");

  auto taskPose3 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskPose3->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose1);
  taskPose3->SetId("Pose3");

  ////// TASK SCHEDULING //////
  RCLCPP_INFO(node->get_logger(), "Execute Task Test ModBus");

  // setup custom task list
  auto taskList = std::make_shared<WzlPlanner::TaskList>();
  taskList->SetId("TaskList_TestModBus");


  //BEMI2 OPEN/CLOSE -> Gripper open Close
  taskList->AddTask(tasks->taskSetSpeedCartesianFast);
  taskList->AddTask(tasks->taskSetSpeedPtp);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi2Open);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi2Close);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi2Open);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi2Close);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi2Open);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi2Close);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi3Open);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi3Close);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskIoBemi2Open);
  taskList->AddTask(tasks->taskWait);
  // taskList->AddTask(taskInitPose);
  // taskList->AddTask(tasks->taskWait);
  // taskList->AddTask(taskPose1);  
  // taskList->AddTask(tasks->taskWait);
  // taskList->AddTask(taskPose2); 
  // taskList->AddTask(tasks->taskWait);
  // taskList->AddTask(taskPose3);


  while (true)
  {
    if (!taskList->Execute())
    {
      RCLCPP_INFO(node->get_logger(), "Execution failed");

      return;
    }

    rclcpp::spin_some(node);
  }

  RCLCPP_INFO(node->get_logger(), "Execution successful");
}

// global version of misctasks
std::shared_ptr<MiscTasks> g_misc_tasks;

// Modify signal handler to use global variable
void signalHandler(int signum) {
    std::cout << "Interrupt signal received.\n";

    rclcpp::shutdown();
    exit(signum);
}

int main(int argc, char *argv[])
{
  // Initialize ROS and create the Node
  std::cout << "Initialize robo planner node" << std::endl;
  rclcpp::init(argc, argv);

  signal(SIGINT, signalHandler);

  // auto trWorld = std::make_shared<WzlPlanner::Transform>("world");

  rclcpp::sleep_for(500ms);

  auto const node = std::make_shared<rclcpp::Node>(
      "robo_planner", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));

  WzlPlanner::TaskOpcuaRequest::InitializeGripperStatePublisher(node);
  // Anfangszustand annehmen: geschlossen (false) oder offen (true). 
  // nicht wirklich bekannt, erst nach erstem öffnen schließen
  //WzlPlanner::TaskOpcuaRequest::PublishInitial(true);

  // Initialize the task status publisher
  WzlPlanner::Task::InitializePublisher(node);

  CreateCell(node);
  


  rclcpp::sleep_for(2000ms);
  auto misc_tasks = std::make_shared<MiscTasks>(node);

  g_misc_tasks = misc_tasks;  // Store in global variable

  rclcpp::sleep_for(2000ms);

  //UseCase starten
  int use_case = 1;  // Standardwert

  if (node->has_parameter("use_case")) {
      use_case = node->get_parameter("use_case").as_int();
  } else {
      node->declare_parameter<int>("use_case", 1);
      use_case = node->get_parameter("use_case").as_int();
  }

  RCLCPP_INFO(node->get_logger(), "Starting UseCase %d", use_case);
    
    // UseCase basierend auf Parameter auswählen
    switch (use_case) {
        case 1:
            UseCase1(node, misc_tasks);
            break;
        case 2:
            UseCase2(node, misc_tasks);
            break;
        default:
            RCLCPP_ERROR(node->get_logger(), "Invalid use case %d, using default (3)", use_case);
            UseCase1(node, misc_tasks);
    }
  rclcpp::spin(node);

  return 0;
}