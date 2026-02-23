#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <csignal>

#include <rclcpp/rclcpp.hpp>
#include "tf2_eigen/tf2_eigen.hpp"
#include <geometry_msgs/msg/pose_array.hpp>

#include "../include/SceneObjects/SceneObject.h"
#include "../include/ObjectContainer.h"
#include "../include/Tasks/TaskInclude.h"
#include "../include/Tasks/Atomic/TaskOpcuaRequest.h"

#include <math.h>
#include <memory>
#include <chrono>

#include "ScrewList.cpp"  // Screw and ScrewList definitions

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
      ioInterfaceModBus,
      ioInterfaceOpcUa,
      robot,
      scene,
      node);

 
  RCLCPP_INFO(node->get_logger(), "Robot scheduler cell environment initialization end.");
}

class MiscTasks
{
public:
  // Task objects are publicly accessible for reuse in other functions
  std::shared_ptr<WzlPlanner::TaskWait> taskWait; // wait for one second
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
  std::shared_ptr<WzlPlanner::TaskSetRobotValueVelocity> taskSetSpeedCartesianMedium;
  std::shared_ptr<WzlPlanner::TaskSetRobotValueVelocity> taskSetSpeedCartesianDeburring;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachSpindel;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachGripper;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachSmallGripper;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachSpindel;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachGripper;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachSmallGripper;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachWorkpiece;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachWorkpiece;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachScrewdriver;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachScrewdriver;
  std::shared_ptr<WzlPlanner::TaskPartAttach> taskAttachCameraMount;
  std::shared_ptr<WzlPlanner::TaskPartDetach> taskDetachCameraMount;

  std::shared_ptr<WzlPlanner::TaskModBusWrite> taskModBusWriteZForce;
  std::shared_ptr<WzlPlanner::TaskModBusWrite> taskModBusWriteScrewLength;
  std::shared_ptr<WzlPlanner::TaskModBusWrite> taskModBusWriteTargetTorque;
  std::shared_ptr<WzlPlanner::TaskModBusWrite> taskModBusWriteTightenScrew;
  std::shared_ptr<WzlPlanner::TaskModBusWrite> taskModBusWriteLoosenScrew;
  std::shared_ptr<WzlPlanner::TaskModBusWrite> taskModBusWriteShankPos20;
  std::shared_ptr<WzlPlanner::TaskModBusWrite> taskModBusWriteShankPos45;
  std::shared_ptr<WzlPlanner::TaskModBusWrite> taskModBusWriteShankPos0;
  std::shared_ptr<WzlPlanner::TaskModBusWrite> taskModBusWriteStop;

  std::shared_ptr<WzlPlanner::TaskModBusRead> taskModBusReadToolType;
  std::shared_ptr<WzlPlanner::TaskModBusRead> taskModBusReadStatusErrors;
  std::shared_ptr<WzlPlanner::TaskModBusRead> taskModBusReadTorqueAngleGradient;
  std::shared_ptr<WzlPlanner::TaskModBusRead> taskModBusReadAchievedTorque;
  std::shared_ptr<WzlPlanner::TaskModBusRead> taskModBusReadCurrentTorque;
  std::shared_ptr<WzlPlanner::TaskModBusRead> taskModBusReadZForce;
  std::shared_ptr<WzlPlanner::TaskModBusRead> taskModBusReadShankPos;

  std::shared_ptr<WzlPlanner::TaskModBusInterpretReadResult> taskModBusInterpretReadResultToolType;

  void UpdateWorkpieceTask(int partType, int orientation = 0) {
      // Update the existing taskAttachWorkpiece object
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

    // MODBUS WRITE 

    taskModBusWriteTightenScrew = std::make_shared<WzlPlanner::TaskModBusWrite>(
        WzlPlanner::ModBusData::GetModBusData_TightenScrew_Write());
    taskModBusWriteTightenScrew->SetId("taskModBusWriteTightenScrew");

    taskModBusWriteLoosenScrew = std::make_shared<WzlPlanner::TaskModBusWrite>(
        WzlPlanner::ModBusData::GetModBusData_LoosenScrew_Write());
    taskModBusWriteLoosenScrew->SetId("taskModBusWriteLoosenScrew");

    taskModBusWriteZForce = std::make_shared<WzlPlanner::TaskModBusWrite>(
        WzlPlanner::ModBusData::GetModBusData_ZAxesForce_Write());
    taskModBusWriteZForce->SetId("taskModBusWriteZForce");
    taskModBusWriteZForce->SetValue(30); // default Z force

    taskModBusWriteScrewLength = std::make_shared<WzlPlanner::TaskModBusWrite>(
        WzlPlanner::ModBusData::GetModBusData_ScrewLength_Write());
    taskModBusWriteScrewLength->SetId("taskModBusWriteScrewLength");
    taskModBusWriteScrewLength->SetValue(16000); //   default screw length

    taskModBusWriteTargetTorque = std::make_shared<WzlPlanner::TaskModBusWrite>(
        WzlPlanner::ModBusData::GetModBusData_TargetTorque_Write());
    taskModBusWriteTargetTorque->SetId("taskModBusWriteTargetTorque");
    taskModBusWriteTargetTorque->SetValue(5000);

    taskModBusWriteStop = std::make_shared<WzlPlanner::TaskModBusWrite>(
        WzlPlanner::ModBusData::GetModBusData_Stop_Write());
    taskModBusWriteStop->SetId("taskModBusWriteStop");

    // ===== ModBus tasks for screw loosening (to be used in task list later) =====
    taskModBusWriteShankPos45 = std::make_shared<WzlPlanner::TaskModBusWrite>(
        WzlPlanner::ModBusData::GetModBusData_ShankPosition_Write());
    taskModBusWriteShankPos45->SetId("taskModBusWriteShankPos45");
    taskModBusWriteShankPos45->SetValue(45);

    taskModBusWriteShankPos20 = std::make_shared<WzlPlanner::TaskModBusWrite>(
        WzlPlanner::ModBusData::GetModBusData_ShankPosition_Write());
    taskModBusWriteShankPos20->SetId("taskModBusWriteShankPos20");
    taskModBusWriteShankPos20->SetValue(20);

    taskModBusWriteShankPos0 = std::make_shared<WzlPlanner::TaskModBusWrite>(
        WzlPlanner::ModBusData::GetModBusData_ShankPosition_Write());
    taskModBusWriteShankPos0->SetId("taskModBusWriteShankPos0");
    taskModBusWriteShankPos0->SetValue(0);

    // MODBUS READ
    taskModBusReadToolType = std::make_shared<WzlPlanner::TaskModBusRead>(
      WzlPlanner::ModBusData::GetModBusData_ToolType_Read());
    taskModBusReadToolType->SetId("taskModBusReadToolType");

    taskModBusInterpretReadResultToolType = std::make_shared<WzlPlanner::TaskModBusInterpretReadResult>(taskModBusReadToolType);
    taskModBusInterpretReadResultToolType->SetId("taskModBusInterpretReadResultToolType");
    taskModBusInterpretReadResultToolType->SetComparisonValue("Screwdriver");

    
    
    taskModBusReadStatusErrors = std::make_shared<WzlPlanner::TaskModBusRead>(
        WzlPlanner::ModBusData::GetModBusData_StatusErrors_Read());
    taskModBusReadStatusErrors->SetId("taskModBusReadStatusErrors");

    taskModBusReadTorqueAngleGradient = std::make_shared<WzlPlanner::TaskModBusRead>(
        WzlPlanner::ModBusData::GetModBusData_TorqueAngleGradient_Read());
    taskModBusReadTorqueAngleGradient->SetId("taskModBusReadTorqueAngleGradient");

    taskModBusReadAchievedTorque = std::make_shared<WzlPlanner::TaskModBusRead>(
        WzlPlanner::ModBusData::GetModBusData_AchievedTorque_Read());
    taskModBusReadAchievedTorque->SetId("taskModBusReadAchievedTorque");

    taskModBusReadCurrentTorque = std::make_shared<WzlPlanner::TaskModBusRead>(
        WzlPlanner::ModBusData::GetModBusData_CurrentTorque_Read());
    taskModBusReadCurrentTorque->SetId("taskModBusReadCurrentTorque");

    taskModBusReadShankPos = std::make_shared<WzlPlanner::TaskModBusRead>(
        WzlPlanner::ModBusData::GetModBusData_ShankZAxesPosition_Read());
    taskModBusReadShankPos->SetId("taskModBusReadShankPos");

    taskModBusReadZForce = std::make_shared<WzlPlanner::TaskModBusRead>(
        WzlPlanner::ModBusData::GetModBusData_ZForce_Read());
    taskModBusReadZForce->SetId("taskModBusReadZForce");

    // Set movement speeds from config parameters
    double ptp_speed = get_parameter<double>(node, "speeds.ptp", 0.3);
    double cartesian_fast = get_parameter<double>(node, "speeds.cartesian_fast", 0.1);
    double cartesian_slow = get_parameter<double>(node, "speeds.cartesian_slow", 0.03);
    double cartesian_deburring = get_parameter<double>(node, "speeds.cartesian_deburring", 1.0);

    taskSetSpeedPtp = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(ptp_speed, 1.0, 0);
    taskSetSpeedCartesianFast = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(cartesian_fast, 0.1, 1);
    taskSetSpeedCartesianSlow = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(cartesian_slow, 0.05, 1);
    taskSetSpeedCartesianMedium = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(cartesian_slow, 0.075, 1);
    taskSetSpeedCartesianDeburring = std::make_shared<WzlPlanner::TaskSetRobotValueVelocity>(cartesian_deburring, 0.5, 1);

    taskSetSpeedPtp->SetId("taskSetSpeedPtp");
    taskSetSpeedCartesianFast->SetId("taskSetSpeedCartesianFast");
    taskSetSpeedCartesianSlow->SetId("taskSetSpeedCartesianSlow");
    taskSetSpeedCartesianMedium->SetId("taskSetSpeedCartesianMedium");
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

    taskAttachScrewdriver = std::make_shared<WzlPlanner::TaskPartAttach>("screwdriver");
    taskAttachScrewdriver->SetId("taskAttachScrewdriver");

    taskDetachScrewdriver = std::make_shared<WzlPlanner::TaskPartDetach>("screwdriver");
    taskDetachScrewdriver->SetId("taskDetachScrewdriver");

    taskAttachCameraMount = std::make_shared<WzlPlanner::TaskPartAttach>("CameraMount");
    taskAttachCameraMount->SetId("taskAttachCameraMount");

    taskDetachCameraMount = std::make_shared<WzlPlanner::TaskPartDetach>("CameraMount");
    taskDetachCameraMount->SetId("taskDetachCameraMount");

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
  //Workpiece orientation and partType defined through the PCNr and PCIndex 
  int partType=1;
  int workpieceOrientation=0;

  // Constants
  double placementOffsetZ = 0.2;

  double rotX = M_PI;
  double rotY = 0;
  double rotZ =0.5;

  std::vector<double> PCX;
  std::vector<double> PCY;
  std::vector<double> PCZ;

  if (PCNr == 1) {
    if (PCIndex == 1 || PCIndex == 5) {
        partType = 1;//lower Part
        workpieceOrientation = 0;
        rotZ =0.5;
    } 
    // possible other orientations
    else if (PCIndex == 2 || PCIndex == 6) {
        partType = 1; 
        workpieceOrientation = 180;
        rotZ =0.5 + M_PI;
    }
    else if (PCIndex == 3 || PCIndex == 4) {
      partType = 1; 
      workpieceOrientation = 90;
      
  }
  } 
// PCNr 2: upper Part
  else if (PCNr == 2) {
      partType = 2; // upper Part
  }
  if (PCNr < 1 || PCNr > 2)
  {
    std::cout << "The Part Carrier number: " << std::to_string(PCNr) << " in method 'CreateTaskPickPC' is not defined." << std::endl;
    return nullptr;
  }




std::cout << PCNr<< std::endl;
  if (PCNr == 1)// Coordinates
  {
    PCX = get_parameter<std::vector<double>>(node, "positions.PC.x_1", {0.29255, -0.456, -0.561, -0.666, -0.771, -0.416, -0.589, -0.762});//only default values if parameters are not found -> correct parameters in cell_config.yaml
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
  taskList->AddTask(tasks->taskIoBemi2Close); //Gripper currently controlled via Bemi2!!! 
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

  if (PCNr == 1)// Coordinates
  {
    PCX = get_parameter<std::vector<double>>(node, "positions.PC.x_1", {0.29255, -0.456, -0.561, -0.666, -0.771, -0.416, -0.589, -0.762});//only default values if parameters are not found -> correct parameters in cell_config.yaml
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
  taskList->AddTask(tasks->taskIoBemi2Close); //Gripper currently controlled via Bemi2!!!
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

  //Position definitions - fallback only: correct definition in cell_config.yaml
std::vector<double> ExecutionBEMIZ = get_parameter<std::vector<double>>(node, "positions.bemi.z", {0.17558, 0.2885, 0.0}); // Different coordinates for BEMI 1 and 2, since Part1 goes to BEMI1 bottom, Part 2 to BEMI2 top

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
taskList->AddTask(tasks->taskIoBemi2Open); //Gripper currently controlled via Bemi2!!! opens gripper
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
  

//Position definitions - fallback only: correct definition in cell_config.yaml
std::vector<double> ExecutionBEMIZ = get_parameter<std::vector<double>>(node, "positions.bemi.z", {0.17558, 0.2885, 0.0}); // Different coordinates for BEMI 1 and 2, since Part1 goes to BEMI1 bottom, Part 2 to BEMI2 top

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
  taskList->AddTask(tasks->taskIoBemi2Close); //Gripper currently controlled via Bemi2!!! opens gripper
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
  double placementOffsetZ = 0.25; // Offset height before bearing placement

  double rotX = M_PI;
  double rotY = 0;
   double rotZ = -M_PI - M_PI / 4;

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
  
  // Part 1 Poses
  auto pose1 = std::make_shared<WzlPlanner::Pose>(0.29255, -0.41572, 0.45, rotX, rotY, 0.5);  
  auto pose2 = std::make_shared<WzlPlanner::Pose>(0.29255, -0.41572, 0.1883, rotX, rotY, 0.5); // Pose pick Part 1 in PC1 1,0472
  auto pose3 = std::make_shared<WzlPlanner::Pose>(0.54009, 0.05915, 0.45, rotX, rotY, 1.63075);
  auto pose4 = std::make_shared<WzlPlanner::Pose>(0.54009, 0.05915, 0.17558, rotX, rotY, 1.63075); // Pose place Part 1 in Tool1 

  // Part 2 Poses 
  auto pose5 = std::make_shared<WzlPlanner::Pose>(0.29021, 0.42433, 0.45, rotX, rotY, 0.5);  
  auto pose6 = std::make_shared<WzlPlanner::Pose>(0.29021, 0.42433, 0.16713, rotX, rotY, 0.5); // Pose pick Part 2 in PC2 
  auto pose7 = std::make_shared<WzlPlanner::Pose>(0.53988, 0.030554, 0.45, rotX, rotY, -1.4932);
  auto pose8 = std::make_shared<WzlPlanner::Pose>(0.53988, 0.030554, 0.185, rotX, rotY, -1.4932); // Pose place Part 2 in Tool1 
  

  // =========== Init & Standard Poses =========== //
  auto taskInitPose = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskInitPose->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseInit);
  taskInitPose->SetId("InitPose");
  //======== Poses for handling Part 1 from PC1 ======//
  auto taskPose1 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // P2P movement to entry position PC1
  taskPose1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose1);
  taskPose1->SetId("Pose1");

  auto taskPose2 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Straight movement into PC1
  taskPose2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose2);
  taskPose2->SetId("Pose2");

  auto taskPose3 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Straight movement out of PC1
  taskPose3->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose1);
  taskPose3->SetId("Pose3");

  auto taskPose4 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // P2P movement to entry position Tool 1
  taskPose4->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose3);
  taskPose4->SetId("Pose4");

  auto taskPose5 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Straight movement into Tool 1
  taskPose5->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose4);
  taskPose5->SetId("Pose5");

  auto taskPose6 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Straight movement out of Tool 1
  taskPose6->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose3);
  taskPose6->SetId("Pose6");

  //======== Poses for handling Part 2 from PC2 ======//

  auto taskPose7 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // P2P movement to entry position PC1
  taskPose7->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose5);
  taskPose7->SetId("Pose7");

  auto taskPose8 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Straight movement into PC1
  taskPose8->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose6);
  taskPose8->SetId("Pose8");

  auto taskPose9 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Straight movement out of PC1
  taskPose9->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose5);
  taskPose9->SetId("Pose9");

  auto taskPose10 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // P2P movement to entry position Tool 1
  taskPose10->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(pose7);
  taskPose10->SetId("Pose10");

  auto taskPose11 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Straight movement into Tool 1
  taskPose11->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose8);
  taskPose11->SetId("Pose11");

  auto taskPose12 = std::make_shared<WzlPlanner::TaskMoveToPose>(); // Straight movement out of Tool 1
  taskPose12->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(pose7);
  taskPose12->SetId("Pose12");

  
  ////// TASK SCHEDULING //////
  RCLCPP_INFO(node->get_logger(), "Execute Task Use Case 2");

  // setup custom task list
  auto taskList = std::make_shared<WzlPlanner::TaskList>();

  // Set Pneumatics to neutral
  // possibly all not needed
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
  taskList->AddTask(tasks->taskIoBemi2Close); //Gripper currently controlled via Bemi2!!! 
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
  taskList->AddTask(tasks->taskIoBemi2Close); //Gripper currently controlled via Bemi2!!! 
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
  taskList->AddTask(tasks->taskIoBemi2Close); //Gripper currently controlled via Bemi2!!! 
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

  //taskList->AddTask(CreateTaskPhotoPositions(node, tasks));
  //taskList->AddTask(taskInitPose);

  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
  //Pick Part 1 & Place parts in BEMI 1(bottom)
  taskList->AddTask(CreateTaskPickPC(node, tasks, 1, 1));
  taskList->AddTask(CreateTaskPlaceBEMI(node, tasks, 1, 1)); 
  taskList->AddTask(taskInitPose);
  
  //Pick Part 2 & Place parts in BEMI 2(same Bemi, top)
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

void UseCase4(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks)
{
  // ===== IO / robot initialization =====
  [[maybe_unused]] auto useOpcua = false;

  RCLCPP_INFO(node->get_logger(), "Initialize screwdriver test.");

  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);

  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  
  RCLCPP_INFO(node->get_logger(), "Initialize screwdriver");

  // Set gripper for proper collision model
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("ScrewdriverGripper", 0, 1);
  robot->SetGripper(gripper);

  // ===== Orientation / constants =====
  // Changed to point right (+Y) instead of downwards (-Z)
  double rotX = M_PI / 2;      // 90 degrees - rotates to point right
  double rotY = 0;             // no pitch
  double rotZ = 0;  // keep yaw angle

  // ===== Basic poses =====
  // INIT pose and task default
  auto poseInit = std::make_shared<WzlPlanner::Pose>(0.498, -0.386, 0.548, rotX, rotY, rotZ);
    
  // =========== Init & Standard Poses =========== //
  auto taskInitPose = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskInitPose->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseInit);
  taskInitPose->SetId("InitPose");

  // Pose zum Fotografieren der Schraubposition
  auto posePhotoScrew1 = std::make_shared<WzlPlanner::Pose>(0.4, 0.1, 0.45, rotX, rotY, rotZ); // Koordinaten anpassen
  auto posePhotoScrew2 = std::make_shared<WzlPlanner::Pose>(0.4, 0.1, 0.45, rotX, rotY, rotZ); // Koordinaten anpassen


  // ===== Tasks for handling pictures =====
  auto taskPhotoScrew1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskPhotoScrew1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(posePhotoScrew1); //aufgabe zum erten Foto positionieren
  taskPhotoScrew1->SetId("posePhotoScrew1");

  auto taskPhotoScrew2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskPhotoScrew2->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(posePhotoScrew2);  //aufgabe zum zweiten Foto positionieren
  taskPhotoScrew2->SetId("posePhotoScrew2");

  // ===== Screw list and generated poses =====
  // List of detected screws (to be filled from vision or config)
  ScrewList screwList;

  // TEMP: test data - fill list with 5 screw positions
  // later this will be filled automatically from vision/config
  screwList.addScrew(0.35, 0.05, 0.55);
  screwList.addScrew(0.36, 0.06, 0.55);
  screwList.addScrew(0.37, 0.07, 0.55);
  screwList.addScrew(0.38, 0.08, 0.55);
  screwList.addScrew(0.39, 0.09, 0.55);


  std::size_t screwCount = screwList.getCount();
  std::vector<std::shared_ptr<WzlPlanner::Pose>> poseScrewApproach(screwCount + 1); // indices 1..screwCount
  std::vector<std::shared_ptr<WzlPlanner::Pose>> poseScrew(screwCount + 1);          // actual screw poses

  int counter = 1;
  double screwApproachOffsetZ = 0.02; // approach a few cm above real screw position

  // create approach and actual poses as long as there are screws in the list
  while (!screwList.isEmpty())
  {
    // take last screw, then remove it from the list
    auto screw = screwList.takeLastScrew();

    // create approach pose above the screw
    auto poseApproach = std::make_shared<WzlPlanner::Pose>(
        screw.x,
        screw.y,
        screw.z + screwApproachOffsetZ,
        rotX,
        rotY,
        rotZ);

    // create actual screw pose at the exact screw position
    auto poseAtScrew = std::make_shared<WzlPlanner::Pose>(
        screw.x,
        screw.y,
        screw.z,
        rotX,
        rotY,
        rotZ);

    // store them in the vectors at the current index
    poseScrewApproach[counter] = poseApproach;
    poseScrew[counter] = poseAtScrew;

    counter += 1;
  }
    
      ////// TASK SCHEDULING //////
      // First task list: move to photo positions
  auto taskListPhotos = std::make_shared<WzlPlanner::TaskList>();
  taskListPhotos->SetId("TaskList_Photos");
  taskListPhotos->AddTask(tasks->taskWait);
  //taskListPhotos->AddTask(tasks->taskAttachScrewdriver);      // Schraubendreher collision an
  taskListPhotos->AddTask(tasks->taskSetSpeedCartesianSlow);  // langsam fahren 
  taskListPhotos->AddTask(tasks->taskWait);
  taskListPhotos->AddTask(taskInitPose);                      // initial position - move to (0.4, 0.1, 0.5)
  taskListPhotos->AddTask(tasks->taskWait);
  taskListPhotos->AddTask(tasks->taskWait);
  //taskListPhotos->AddTask(tasks->taskAttachScrewdriver); 
  taskListPhotos->AddTask(tasks->taskWait);
  taskListPhotos->AddTask(tasks->taskWait);                   // extra wait to ensure stable configuration
  taskListPhotos->AddTask(taskPhotoScrew1);                   // erste Fotoposition anfahren
  taskListPhotos->AddTask(tasks->taskWait);
  taskListPhotos->AddTask(taskPhotoScrew2);                   // zweite Fotoposition anfahren
  taskListPhotos->AddTask(tasks->taskWait);
  taskListPhotos->AddTask(taskInitPose);                      // initial position
  taskListPhotos->AddTask(tasks->taskWait);
  taskListPhotos->AddTask(tasks->taskDetachScrewdriver);    // Schraubendreher collision aus

  // Second task list: move to screws back and forth
  auto taskListScrews = std::make_shared<WzlPlanner::TaskList>();
  taskListScrews->SetId("TaskList_Screws");
  //taskListScrews->AddTask(tasks->taskAttachScrewdriver);       // Schraubendreher collision an
  taskListScrews->AddTask(tasks->taskSetSpeedCartesianSlow);
  taskListScrews->AddTask(tasks->taskWait);
  

  // For each screw: go to approach pose, then to screw pose, then back to init
  
  for (std::size_t i = 1; i <= screwCount; ++i)
  {
    auto taskApproach = std::make_shared<WzlPlanner::TaskMoveToPose>();
    taskApproach->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseScrewApproach[i]);
    taskApproach->SetId("poseScrewApproach" + std::to_string(i));

    auto taskAtScrew = std::make_shared<WzlPlanner::TaskMoveToPose>();
    taskAtScrew->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew[i]);
    taskAtScrew->SetId("poseScrew" + std::to_string(i));

    taskListScrews->AddTask(taskApproach);
    taskListScrews->AddTask(tasks->taskWait);
    taskListScrews->AddTask(taskAtScrew);
    taskListScrews->AddTask(tasks->taskWait);

    // Ausschrauben-Sequenz: entspricht dem ROS-Service
    //   ros2 service call /ausschrauben modbus_interfaces/srv/LoosenScrew
    //   "{screw_length: 16000, z_force: 30}"
    //taskListScrews->AddTask(tasks->taskModBusWriteScrewLength);
    //taskListScrews->AddTask(tasks->taskWait);
    //taskListScrews->AddTask(tasks->taskModBusWriteZForce);
    //taskListScrews->AddTask(tasks->taskWait);
    //taskListScrews->AddTask(tasks->taskModBusWriteLoosenScrew);
    //taskListScrews->AddTask(tasks->taskWait);

    taskListScrews->AddTask(taskInitPose);
  }

  RCLCPP_INFO(node->get_logger(), "Execute Task Use Case 4");

  // Execute photo task list once, then screw task list in a loop
  if (!taskListPhotos->Execute())
  {
    RCLCPP_INFO(node->get_logger(), "Execution of photo task list failed");
    return;
  }

  while (true) // screw task list wird immer wiederholt
  {
    if (!taskListScrews->Execute())
    {
      RCLCPP_INFO(node->get_logger(), "Execution of screw task list failed");

      return;
    }

    rclcpp::spin_some(node);
  }

  RCLCPP_INFO(node->get_logger(), "Execution successful");
}

void UseCase5(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks)
{
  // ===== IO / robot initialization =====
  [[maybe_unused]] auto useOpcua = false;

  RCLCPP_INFO(node->get_logger(), "Initialize UseCase 5 - Move to InitPose only.");

  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);

  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  
  RCLCPP_INFO(node->get_logger(), "Initialize gripper for collision model");

  // Set gripper for proper collision model
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("ScrewdriverGripper", 0, 1);
  robot->SetGripper(gripper);

  // ===== Orientation / constants =====
  double rotX = M_PI / 2;
  double rotY = 0;
  double rotZ = 0;


  // ===== Basic poses =====
  auto poseInit = std::make_shared<WzlPlanner::Pose>(0.498, -0.386, 0.548, rotX, rotY, rotZ);
  
  
  auto taskInitPose = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskInitPose->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseInit);
  taskInitPose->SetId("InitPose");

// === Überflug ===

  // Pose Kamera
  // Position:    x=0.6702, y=0.1867, z=0.3122
  // Quaternion:  x=0.5598, y=0.4659, z=0.4490, w=0.5176
  // Euler (deg): rx=93.50, ry=-1.17, rz=80.64

// ===== Screw list  =====
  //definition 
    
    // Schraube 1: x=0.5159, y=-0.0272, z=0.1118
    // rx=90.03, ry=0.09, rz=-0.01 ???
    // rx=89.84, ry=0.09, rz=-0.04
    double Screw1X = 0.5159;
    double Screw1Y = -0.0272;
    double Screw1Z = 0.1118;

    // Schraube 2: x=0.5814, y=-0.0186, z=0.1124
    // rx=90.03, ry=0.09, rz=-0.01
    double Screw2X = 0.5814;
    double Screw2Y = -0.0186;
    double Screw2Z = 0.1124; 

    // Schraube 3: x=0.5894, y=0.0525, z=0.1034
    // rx=89.98, ry=0.09, rz=25.50
    double Screw3X = 0.5894;
    double Screw3Y = 0.0525;
    double Screw3Z = 0.1034;

    // Schraube 4: x=0.5145, y=0.1290, z=0.1046
    // rx=90.03, ry=0.09, rz=-0.01
    double Screw4X = 0.5145;
    double Screw4Y = 0.1290;
    double Screw4Z = 0.1046; 

    // Schraube 5: x=0.4893, y=0.0438, z=0.1034
    // rx=90.03, ry=0.09, rz=-0.02
    double Screw5X = 0.4893;
    double Screw5Y = 0.0438;
    double Screw5Z = 0.1034; 

  
    // Einschraubung: 
    // 1. x=0.5614, y=-0.5545, z=0.0348
    // 2. x=0.5344, y=-0.5629, z=0.0319
    // 3. x=0.5507, y=-0.5684, z=0.0326
    // 4. x=0.5517, y=-0.5404, z=0.0322
    // 5. x=0.5348, y=-0.5452, z=0.0318
    double Screw1_EinschraubX = 0.5614;
    double Screw1_EinschraubY = -0.5545;
    double Screw1_EinschraubZ = 0.0348;

    double Screw2_EinschraubX = 0.5344;
    double Screw2_EinschraubY = -0.5629;
    double Screw2_EinschraubZ = 0.0319;

    double Screw3_EinschraubX = 0.5507;
    double Screw3_EinschraubY = -0.5684;
    double Screw3_EinschraubZ = 0.0326;

    double Screw4_EinschraubX = 0.5517;
    double Screw4_EinschraubY = -0.5404;
    double Screw4_EinschraubZ = 0.0322;

    double Screw5_EinschraubX = 0.5348;
    double Screw5_EinschraubY = -0.5452;
    double Screw5_EinschraubZ = 0.0318;

    // Foto Pos: x=0.6220, y=0.2084, z=0.2393
    double PhotoX = 0.6220;
    double PhotoY = 0.2084;
    double PhotoZ = 0.2393;

    double insertionZOffset = 0.025;

    // Foto pose
    auto posePhoto = std::make_shared<WzlPlanner::Pose>(PhotoX, PhotoY, PhotoZ, M_PI / 2, 0, M_PI / 2);

    auto taskPhoto = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskPhoto->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(posePhoto);
      taskPhoto->SetId("PhotoPose");

    // Posen der Schrauben mit Offset für Einschraubung
    auto poseScrew1 = std::make_shared<WzlPlanner::Pose>(Screw1X, Screw1Y, Screw1Z - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew2 = std::make_shared<WzlPlanner::Pose>(Screw2X, Screw2Y, Screw2Z - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew3 = std::make_shared<WzlPlanner::Pose>(Screw3X, Screw3Y, Screw3Z - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew4 = std::make_shared<WzlPlanner::Pose>(Screw4X, Screw4Y, Screw4Z - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew5 = std::make_shared<WzlPlanner::Pose>(Screw5X, Screw5Y, Screw5Z - insertionZOffset, M_PI / 2, 0, 0);

    // handlings

    auto taskScrew1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew1);
      taskScrew1->SetId("Screw1");

    auto taskScrew2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew2);
      taskScrew2->SetId("Screw2");

    auto taskScrew3 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew3->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew3);
      taskScrew3->SetId("Screw3");

    auto taskScrew4 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew4->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew4);
      taskScrew4->SetId("Screw4");

    auto taskScrew5 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew5->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew5);
      taskScrew5->SetId("Screw5");  


// === Screwlist safty points ===

double SaftyOffsetZ = 0.2; // safety offset above screws

  // Posen
    auto poseScrewSafe1 = std::make_shared<WzlPlanner::Pose>(Screw1X, Screw1Y, Screw1Z + SaftyOffsetZ,M_PI / 2, 0, 0);
    auto poseScrewSafe2 = std::make_shared<WzlPlanner::Pose>(Screw2X, Screw2Y, Screw2Z + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrewSafe3 = std::make_shared<WzlPlanner::Pose>(Screw3X, Screw3Y, Screw3Z + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrewSafe4 = std::make_shared<WzlPlanner::Pose>(Screw4X, Screw4Y, Screw4Z + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrewSafe5 = std::make_shared<WzlPlanner::Pose>(Screw5X, Screw5Y, Screw5Z + SaftyOffsetZ, M_PI / 2, 0, 0);

  //handlings


    // ACHTUNG: HIER PTP (OMPL)! Nach erster Fotopose
    auto taskScrewSafe1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseScrewSafe1);
      taskScrewSafe1->SetId("ScrewSafe1");

    auto taskScrewSafe2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe2);
      taskScrewSafe2->SetId("ScrewSafe2");

    auto taskScrewSafe3 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe3->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe3);
      taskScrewSafe3->SetId("ScrewSafe3");

    auto taskScrewSafe4 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe4->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe4);
      taskScrewSafe4->SetId("ScrewSafe4");

    auto taskScrewSafe5 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe5->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe5);
      taskScrewSafe5->SetId("ScrewSafe5");


    //handlings

    auto taskScrewSafe1_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe1_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe1);
      taskScrewSafe1_post->SetId("ScrewSafe1_post");

    auto taskScrewSafe2_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe2_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe2);
      taskScrewSafe2_post->SetId("ScrewSafe2_post");

    auto taskScrewSafe3_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe3_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe3);
      taskScrewSafe3_post->SetId("ScrewSafe3_post");

    auto taskScrewSafe4_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe4_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe4);
      taskScrewSafe4_post->SetId("ScrewSafe4_post");

    auto taskScrewSafe5_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe5_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe5);
      taskScrewSafe5_post->SetId("ScrewSafe5_post");



    // Schrauben Einschraubpositionen Safe
    auto poseScrew1_EinschraubSafe = std::make_shared<WzlPlanner::Pose>(Screw1_EinschraubX, Screw1_EinschraubY, Screw1_EinschraubZ + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrew2_EinschraubSafe = std::make_shared<WzlPlanner::Pose>(Screw2_EinschraubX, Screw2_EinschraubY, Screw2_EinschraubZ + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrew3_EinschraubSafe = std::make_shared<WzlPlanner::Pose>(Screw3_EinschraubX, Screw3_EinschraubY, Screw3_EinschraubZ + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrew4_EinschraubSafe = std::make_shared<WzlPlanner::Pose>(Screw4_EinschraubX, Screw4_EinschraubY, Screw4_EinschraubZ + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrew5_EinschraubSafe = std::make_shared<WzlPlanner::Pose>(Screw5_EinschraubX, Screw5_EinschraubY, Screw5_EinschraubZ + SaftyOffsetZ, M_PI / 2, 0, 0);

    auto taskScrew1_EinschraubSafe = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew1_EinschraubSafe->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew1_EinschraubSafe);
      taskScrew1_EinschraubSafe->SetId("Screw1_EinschraubSafe");

    auto taskScrew2_EinschraubSafe = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew2_EinschraubSafe->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew2_EinschraubSafe);
      taskScrew2_EinschraubSafe->SetId("Screw2_EinschraubSafe");

    auto taskScrew3_EinschraubSafe = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew3_EinschraubSafe->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew3_EinschraubSafe);
      taskScrew3_EinschraubSafe->SetId("Screw3_EinschraubSafe");

    auto taskScrew4_EinschraubSafe = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew4_EinschraubSafe->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew4_EinschraubSafe);
      taskScrew4_EinschraubSafe->SetId("Screw4_EinschraubSafe");

    auto taskScrew5_EinschraubSafe = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew5_EinschraubSafe->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew5_EinschraubSafe);
      taskScrew5_EinschraubSafe->SetId("Screw5_EinschraubSafe");



    //Schrauben Einschraubpositionen
    auto poseScrew1_Einschraub = std::make_shared<WzlPlanner::Pose>(Screw1_EinschraubX, Screw1_EinschraubY, Screw1_EinschraubZ - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew2_Einschraub = std::make_shared<WzlPlanner::Pose>(Screw2_EinschraubX, Screw2_EinschraubY, Screw2_EinschraubZ - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew3_Einschraub = std::make_shared<WzlPlanner::Pose>(Screw3_EinschraubX, Screw3_EinschraubY, Screw3_EinschraubZ - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew4_Einschraub = std::make_shared<WzlPlanner::Pose>(Screw4_EinschraubX, Screw4_EinschraubY, Screw4_EinschraubZ - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew5_Einschraub = std::make_shared<WzlPlanner::Pose>(Screw5_EinschraubX, Screw5_EinschraubY, Screw5_EinschraubZ - insertionZOffset, M_PI / 2, 0, 0); 

    auto taskScrew1_Einschraub = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew1_Einschraub->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew1_Einschraub);
      taskScrew1_Einschraub->SetId("Screw1_Einschraub");

    auto taskScrew2_Einschraub = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew2_Einschraub->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew2_Einschraub);
      taskScrew2_Einschraub->SetId("Screw2_Einschraub");

    auto taskScrew3_Einschraub = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew3_Einschraub->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew3_Einschraub);
      taskScrew3_Einschraub->SetId("Screw3_Einschraub");

    auto taskScrew4_Einschraub = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew4_Einschraub->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew4_Einschraub);
      taskScrew4_Einschraub->SetId("Screw4_Einschraub");

    auto taskScrew5_Einschraub = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew5_Einschraub->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew5_Einschraub);
      taskScrew5_Einschraub->SetId("Screw5_Einschraub");

    // schraube Einschraubpositionen Safe post

    auto taskScrew1_EinschraubSafe_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew1_EinschraubSafe_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew1_EinschraubSafe);
      taskScrew1_EinschraubSafe_post->SetId("Screw1_EinschraubSafe_post");

    auto taskScrew2_EinschraubSafe_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew2_EinschraubSafe_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew2_EinschraubSafe);
      taskScrew2_EinschraubSafe_post->SetId("Screw2_EinschraubSafe_post");

    auto taskScrew3_EinschraubSafe_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew3_EinschraubSafe_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew3_EinschraubSafe);
      taskScrew3_EinschraubSafe_post->SetId("Screw3_EinschraubSafe_post");

    auto taskScrew4_EinschraubSafe_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew4_EinschraubSafe_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew4_EinschraubSafe);
      taskScrew4_EinschraubSafe_post->SetId("Screw4_EinschraubSafe_post");

    auto taskScrew5_EinschraubSafe_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew5_EinschraubSafe_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew5_EinschraubSafe);
      taskScrew5_EinschraubSafe_post->SetId("Screw5_EinschraubSafe_post");



  ////// TASK SCHEDULING //////
  RCLCPP_INFO(node->get_logger(), "Execute Task Use Case 5");

  // ===== Set screw parameters =====
  int screwLength = 35000;  // Change this value to adjust screw length in ym (min 0 max 35000)
  int zForce = 30;          // Change this value to adjust Z-axis force in N (min 18 mx 30)
  int targetTorque = 100;    // Change this value to adjust target torque in yNm (min 100 max 5000)
  
  tasks->taskModBusWriteScrewLength->SetValue(screwLength);
  tasks->taskModBusWriteZForce->SetValue(zForce);
  tasks->taskModBusWriteTargetTorque->SetValue(targetTorque);

  auto taskList = std::make_shared<WzlPlanner::TaskList>();
  taskList->SetId("TaskList_PosesAndScrews");
  // taskList->AddTask(tasks->taskDetachScrewdriver);
  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskPhoto); // Fotoposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrewSafe1); // schraube 1 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew1); // schraube 1 anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength); 
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteLoosenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  
  taskList->AddTask(taskScrewSafe1_post); // schraube 1 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  
  taskList->AddTask(taskScrew1_EinschraubSafe); // schraube 1 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew1_Einschraub); // schraube 1 Einschraubposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTargetTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTightenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew1_EinschraubSafe_post); // schraube 1 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);


  taskList->AddTask(taskScrewSafe2); // schraube 2 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew2); // schraube 2 anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteLoosenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  
  taskList->AddTask(taskScrewSafe2_post); // schraube 2 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew2_EinschraubSafe); // schraube 2 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew2_Einschraub); // schraube 2 Einschraubposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTargetTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTightenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew2_EinschraubSafe_post); // schraube 2 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrewSafe3); // schraube 3 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew3); // schraube 3 anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteLoosenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);


  taskList->AddTask(taskScrewSafe3_post); // schraube 3 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew3_EinschraubSafe); // schraube 3 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew3_Einschraub); // schraube 3 Einschraubposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTargetTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTightenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew3_EinschraubSafe_post); // schraube 3 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);


  taskList->AddTask(taskScrewSafe4); // schraube 4 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew4); // schraube 4  anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteLoosenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrewSafe4_post); // schraube 4 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew4_EinschraubSafe); // schraube 4 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew4_Einschraub); // schraube 4 Einschraubposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTargetTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTightenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew4_EinschraubSafe_post); // schraube 4 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  
  taskList->AddTask(taskScrewSafe5); // schraube 5 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  
  taskList->AddTask(taskScrew5); // schraube 5 anfahren
  taskList->AddTask(tasks->taskWait);  
  taskList->AddTask(tasks->taskWait);
  
  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteLoosenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);


  taskList->AddTask(taskScrewSafe5_post); // schraube 5 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew5_EinschraubSafe); // schraube 5 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew5_Einschraub); // schraube 5 Einschraubposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTargetTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTightenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew5_EinschraubSafe_post); // schraube 5 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);


  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  if (!taskList->Execute())
  {
    RCLCPP_INFO(node->get_logger(), "Execution of UseCase 5 failed");
    return;
  }

  RCLCPP_INFO(node->get_logger(), "UseCase 5 execution successful");
}


void UseCase6(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks)
{
  // ===== IO / robot initialization =====
  [[maybe_unused]] auto useOpcua = false;

  RCLCPP_INFO(node->get_logger(), "Initialize UseCase 6 - Move to Photo only.");

  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);

  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  
  RCLCPP_INFO(node->get_logger(), "Initialize gripper for collision model");

  // Set gripper for proper collision model
  // auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("ScrewdriverGripper", 0, 1);
  // robot->SetGripper(gripper);

  // ===== Orientation / constants =====
  double rotX = M_PI / 2;
  double rotY = 0;
  double rotZ = 0;
  

  // ===== Basic poses =====
  auto poseInit = std::make_shared<WzlPlanner::Pose>(0.498, -0.386, 0.548, rotX, rotY, rotZ);
  
    
  auto taskInitPose = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskInitPose->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseInit);
  taskInitPose->SetId("InitPose");

  // === Überflug ===

    // ===== Holzbohrer  =====
    // x=0.5920, y=0.0536, z=0.1485
    double CalibPointX = 0.5920;
    double CalibPointY = 0.0536;
    double CalibPointZ = 0.2485; 
    
    double AngleX = M_PI / 2;
    double AngleY = 0;
    double AngleZ = 0;

    // Einschraubung: 1. x=0.5614, y=-0.5545, z=0.0348
    // 2. x=0.5344, y=-0.5629, z=0.0319
    // 3. x=0.5507, y=-0.5684, z=0.0326
    // 4. x=0.5517, y=-0.5404, z=0.0322
    // 5. x=0.5348, y=-0.5452, z=0.0318

    // Posen
    auto poseCalib = std::make_shared<WzlPlanner::Pose>(CalibPointX, CalibPointY, CalibPointZ, AngleX, AngleY, AngleZ);
    auto poseCalibRot = std::make_shared<WzlPlanner::Pose>(CalibPointX, CalibPointY, CalibPointZ, AngleX, AngleY, AngleZ+M_PI/6);

    // handlings
    auto taskCalib = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskCalib->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseCalib);
      taskCalib->SetId("Calib");

    auto taskCalibRot = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskCalibRot->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseCalibRot);
      taskCalibRot->SetId("CalibRot");


  ////// TASK SCHEDULING //////
  RCLCPP_INFO(node->get_logger(), "Execute Task Use Case 6");

  
  auto taskList = std::make_shared<WzlPlanner::TaskList>();
  taskList->SetId("TaskList_PosesAndScrews");

  taskList->AddTask(tasks->taskSetSpeedCartesianSlow);

  taskList->AddTask(tasks->taskDetachScrewdriver);

  // taskList->AddTask(tasks->taskWait);
  // taskList->AddTask(tasks->taskWait);

  // taskList->AddTask(taskInitPose);

  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskCalib); // schraube 1 Sichereitsposition anfahren
  
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskCalibRot); // schraube 1 Sichereitsposition anfahren

  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  

  if (!taskList->Execute())
  {
    RCLCPP_INFO(node->get_logger(), "Execution of UseCase 6 failed");
    return;
  }

  RCLCPP_INFO(node->get_logger(), "UseCase 6 execution successful");
}


void UseCase7(const rclcpp::Node::SharedPtr &node, const std::shared_ptr<MiscTasks> &tasks)
{
  // ===== IO / robot initialization =====
  [[maybe_unused]] auto useOpcua = false;

  RCLCPP_INFO(node->get_logger(), "Initialize UseCase 7 - Photo + Detection + Screw Operations.");

  auto dummyIoInterface = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  WzlPlanner::ObjectContainer::Get()->SetIoInterface(dummyIoInterface);

  auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();
  
  RCLCPP_INFO(node->get_logger(), "Initialize gripper for collision model");

  // Set gripper for proper collision model
  auto gripper = std::make_shared<WzlPlanner::GripperPneumaticSingle>("ScrewdriverGripper", 0, 1);
  robot->SetGripper(gripper);

  // ===== Orientation / constants =====
  double rotX = M_PI / 2;
  double rotY = 0;
  double rotZ = 0;


  // ===== Basic poses =====
  auto poseInit = std::make_shared<WzlPlanner::Pose>(0.498, -0.386, 0.548, rotX, rotY, rotZ);
  
  
  auto taskInitPose = std::make_shared<WzlPlanner::TaskMoveToPose>();
  taskInitPose->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseInit);
  taskInitPose->SetId("InitPose");

// === Überflug ===

  // Pose Kamera
  // Position:    x=0.6702, y=0.1867, z=0.3122
  // Quaternion:  x=0.5598, y=0.4659, z=0.4490, w=0.5176
  // Euler (deg): rx=93.50, ry=-1.17, rz=80.64

// ===== Photo pose (executed first, before detection) =====
    // Foto Pos: x=0.6220, y=0.2084, z=0.2393
    double PhotoX = 0.6220;
    double PhotoY = 0.2084;
    double PhotoZ = 0.2393;

    auto posePhoto = std::make_shared<WzlPlanner::Pose>(PhotoX, PhotoY, PhotoZ, M_PI / 2, 0, M_PI / 2);

    auto taskPhoto = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskPhoto->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(posePhoto);
      taskPhoto->SetId("PhotoPose");

  // ===== Phase 1: Move to photo pose =====
  RCLCPP_INFO(node->get_logger(), "UseCase 7 - Phase 1: Moving to photo pose ...");

  auto taskListPhoto = std::make_shared<WzlPlanner::TaskList>();
  taskListPhoto->SetId("TaskList_PhotoPose");
  taskListPhoto->AddTask(tasks->taskSetSpeedCartesianFast);
  taskListPhoto->AddTask(tasks->taskWait);
  taskListPhoto->AddTask(tasks->taskWait);
  taskListPhoto->AddTask(taskPhoto);
  taskListPhoto->AddTask(tasks->taskWait);
  taskListPhoto->AddTask(tasks->taskWait);
  taskListPhoto->AddTask(tasks->taskWait);
  taskListPhoto->AddTask(tasks->taskWait);
  taskListPhoto->AddTask(tasks->taskWait);

  if (!taskListPhoto->Execute())
  {
    RCLCPP_ERROR(node->get_logger(), "Failed to move to photo pose. Aborting UseCase 7.");
    return;
  }
  RCLCPP_INFO(node->get_logger(), "Reached photo pose. Starting screw detection ...");

  // ===== Phase 2: Wait for screw detections from localization =====
  geometry_msgs::msg::PoseArray::SharedPtr detected_screws_msg;
  auto screw_sub = node->create_subscription<geometry_msgs::msg::PoseArray>(
      "screws_from_depth", 10,
      [&detected_screws_msg](const geometry_msgs::msg::PoseArray::SharedPtr msg) {
          detected_screws_msg = msg;
      });

  const int max_retries = 10;           // number of 30s windows to try
  const auto retry_timeout = std::chrono::seconds(30);
  bool detection_ok = false;

  for (int attempt = 1; attempt <= max_retries; ++attempt) {
    detected_screws_msg.reset();
    RCLCPP_INFO(node->get_logger(),
                "Waiting for 5 detected screw positions on screws_from_depth (attempt %d/%d) ...",
                attempt, max_retries);

    auto wait_start = std::chrono::steady_clock::now();
    while (rclcpp::ok()) {
      rclcpp::spin_some(node);
      std::this_thread::sleep_for(100ms);

      if (detected_screws_msg && detected_screws_msg->poses.size() >= 5) {
        detection_ok = true;
        break;
      }
      if (detected_screws_msg && detected_screws_msg->poses.size() < 5) {
        RCLCPP_WARN(node->get_logger(),
                    "Received %zu screw positions (need 5). Waiting for a complete detection ...",
                    detected_screws_msg->poses.size());
        detected_screws_msg.reset();
      }
      if (std::chrono::steady_clock::now() - wait_start > retry_timeout) {
        RCLCPP_WARN(node->get_logger(), "Attempt %d/%d timed out.", attempt, max_retries);
        break;
      }
    }
    if (detection_ok) break;
  }

  if (!detection_ok) {
    RCLCPP_ERROR(node->get_logger(),
                 "Failed to receive 5 screw positions after %d retries. Aborting UseCase 7.", max_retries);
    return;
  }

  // ===== Phase 3: Define screw positions from detected values =====
  RCLCPP_INFO(node->get_logger(), "Received %zu detected screw positions:",
              detected_screws_msg->poses.size());

  double Screw1X = detected_screws_msg->poses[0].position.x;
  double Screw1Y = detected_screws_msg->poses[0].position.y;
  double Screw1Z = detected_screws_msg->poses[0].position.z;

  double Screw2X = detected_screws_msg->poses[1].position.x;
  double Screw2Y = detected_screws_msg->poses[1].position.y;
  double Screw2Z = detected_screws_msg->poses[1].position.z;

  double Screw3X = detected_screws_msg->poses[2].position.x;
  double Screw3Y = detected_screws_msg->poses[2].position.y;
  double Screw3Z = detected_screws_msg->poses[2].position.z;

  double Screw4X = detected_screws_msg->poses[3].position.x;
  double Screw4Y = detected_screws_msg->poses[3].position.y;
  double Screw4Z = detected_screws_msg->poses[3].position.z;

  double Screw5X = detected_screws_msg->poses[4].position.x;
  double Screw5Y = detected_screws_msg->poses[4].position.y;
  double Screw5Z = detected_screws_msg->poses[4].position.z;

  for (size_t i = 0; i < 5; ++i) {
    RCLCPP_INFO(node->get_logger(), "  Screw %zu: x=%.4f, y=%.4f, z=%.4f",
                i + 1,
                detected_screws_msg->poses[i].position.x,
                detected_screws_msg->poses[i].position.y,
                detected_screws_msg->poses[i].position.z);
  }

    // Einschraubung (fixed insertion positions): 
    // 1. x=0.5614, y=-0.5545, z=0.0348
    // 2. x=0.5344, y=-0.5629, z=0.0319
    // 3. x=0.5507, y=-0.5684, z=0.0326
    // 4. x=0.5517, y=-0.5404, z=0.0322
    // 5. x=0.5348, y=-0.5452, z=0.0318
    double Screw1_EinschraubX = 0.5614;
    double Screw1_EinschraubY = -0.5545;
    double Screw1_EinschraubZ = 0.0348;

    double Screw2_EinschraubX = 0.5344;
    double Screw2_EinschraubY = -0.5629;
    double Screw2_EinschraubZ = 0.0319;

    double Screw3_EinschraubX = 0.5507;
    double Screw3_EinschraubY = -0.5684;
    double Screw3_EinschraubZ = 0.0326;

    double Screw4_EinschraubX = 0.5517;
    double Screw4_EinschraubY = -0.5404;
    double Screw4_EinschraubZ = 0.0322;

    double Screw5_EinschraubX = 0.5348;
    double Screw5_EinschraubY = -0.5452;
    double Screw5_EinschraubZ = 0.0318;

    double insertionZOffset = 0.035;

    // Posen der Schrauben mit Offset für Einschraubung 
    auto poseScrew1 = std::make_shared<WzlPlanner::Pose>(Screw1X, Screw1Y, Screw1Z - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew2 = std::make_shared<WzlPlanner::Pose>(Screw2X, Screw2Y, Screw2Z - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew3 = std::make_shared<WzlPlanner::Pose>(Screw3X, Screw3Y, Screw3Z - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew4 = std::make_shared<WzlPlanner::Pose>(Screw4X, Screw4Y, Screw4Z - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew5 = std::make_shared<WzlPlanner::Pose>(Screw5X, Screw5Y, Screw5Z - insertionZOffset, M_PI / 2, 0, 0);

    // handlings

    auto taskScrew1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew1->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew1);
      taskScrew1->SetId("Screw1");

    auto taskScrew2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew2->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew2);
      taskScrew2->SetId("Screw2");

    auto taskScrew3 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew3->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew3);
      taskScrew3->SetId("Screw3");

    auto taskScrew4 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew4->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew4);
      taskScrew4->SetId("Screw4");

    auto taskScrew5 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew5->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew5);
      taskScrew5->SetId("Screw5");  


  // === Screwlist safty points ===

  double SaftyOffsetZ = 0.2; // safety offset above screws

  // Posen
    auto poseScrewSafe1 = std::make_shared<WzlPlanner::Pose>(Screw1X, Screw1Y, Screw1Z + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrewSafe2 = std::make_shared<WzlPlanner::Pose>(Screw2X, Screw2Y, Screw2Z + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrewSafe3 = std::make_shared<WzlPlanner::Pose>(Screw3X, Screw3Y, Screw3Z + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrewSafe4 = std::make_shared<WzlPlanner::Pose>(Screw4X, Screw4Y, Screw4Z + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrewSafe5 = std::make_shared<WzlPlanner::Pose>(Screw5X, Screw5Y, Screw5Z + SaftyOffsetZ, M_PI / 2, 0, 0);

  //handlings


    // ACHTUNG: HIER PTP (OMPL)! Nach erster Fotopose
    auto taskScrewSafe1 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe1->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseScrewSafe1);
      taskScrewSafe1->SetId("ScrewSafe1");

    auto taskScrewSafe2 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe2->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseScrewSafe2);
      taskScrewSafe2->SetId("ScrewSafe2");

    auto taskScrewSafe3 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe3->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseScrewSafe3);
      taskScrewSafe3->SetId("ScrewSafe3");

    auto taskScrewSafe4 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe4->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseScrewSafe4);
      taskScrewSafe4->SetId("ScrewSafe4");

    auto taskScrewSafe5 = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe5->SetMoveType(WzlPlanner::RobotMoveType::AbsolutePTP)->SetTargetPose(poseScrewSafe5);
      taskScrewSafe5->SetId("ScrewSafe5");


    //handlings

    auto taskScrewSafe1_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe1_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe1);
      taskScrewSafe1_post->SetId("ScrewSafe1_post");

    auto taskScrewSafe2_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe2_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe2);
      taskScrewSafe2_post->SetId("ScrewSafe2_post");

    auto taskScrewSafe3_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe3_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe3);
      taskScrewSafe3_post->SetId("ScrewSafe3_post");

    auto taskScrewSafe4_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe4_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe4);
      taskScrewSafe4_post->SetId("ScrewSafe4_post");

    auto taskScrewSafe5_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrewSafe5_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrewSafe5);
      taskScrewSafe5_post->SetId("ScrewSafe5_post");



    // Schrauben Einschraubpositionen Safe
    auto poseScrew1_EinschraubSafe = std::make_shared<WzlPlanner::Pose>(Screw1_EinschraubX, Screw1_EinschraubY, Screw1_EinschraubZ + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrew2_EinschraubSafe = std::make_shared<WzlPlanner::Pose>(Screw2_EinschraubX, Screw2_EinschraubY, Screw2_EinschraubZ + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrew3_EinschraubSafe = std::make_shared<WzlPlanner::Pose>(Screw3_EinschraubX, Screw3_EinschraubY, Screw3_EinschraubZ + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrew4_EinschraubSafe = std::make_shared<WzlPlanner::Pose>(Screw4_EinschraubX, Screw4_EinschraubY, Screw4_EinschraubZ + SaftyOffsetZ, M_PI / 2, 0, 0);
    auto poseScrew5_EinschraubSafe = std::make_shared<WzlPlanner::Pose>(Screw5_EinschraubX, Screw5_EinschraubY, Screw5_EinschraubZ + SaftyOffsetZ, M_PI / 2, 0, 0);

    auto taskScrew1_EinschraubSafe = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew1_EinschraubSafe->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew1_EinschraubSafe);
      taskScrew1_EinschraubSafe->SetId("Screw1_EinschraubSafe");

    auto taskScrew2_EinschraubSafe = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew2_EinschraubSafe->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew2_EinschraubSafe);
      taskScrew2_EinschraubSafe->SetId("Screw2_EinschraubSafe");

    auto taskScrew3_EinschraubSafe = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew3_EinschraubSafe->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew3_EinschraubSafe);
      taskScrew3_EinschraubSafe->SetId("Screw3_EinschraubSafe");

    auto taskScrew4_EinschraubSafe = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew4_EinschraubSafe->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew4_EinschraubSafe);
      taskScrew4_EinschraubSafe->SetId("Screw4_EinschraubSafe");

    auto taskScrew5_EinschraubSafe = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew5_EinschraubSafe->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew5_EinschraubSafe);
      taskScrew5_EinschraubSafe->SetId("Screw5_EinschraubSafe");



    //Schrauben Einschraubpositionen
    auto poseScrew1_Einschraub = std::make_shared<WzlPlanner::Pose>(Screw1_EinschraubX, Screw1_EinschraubY, Screw1_EinschraubZ - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew2_Einschraub = std::make_shared<WzlPlanner::Pose>(Screw2_EinschraubX, Screw2_EinschraubY, Screw2_EinschraubZ - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew3_Einschraub = std::make_shared<WzlPlanner::Pose>(Screw3_EinschraubX, Screw3_EinschraubY, Screw3_EinschraubZ - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew4_Einschraub = std::make_shared<WzlPlanner::Pose>(Screw4_EinschraubX, Screw4_EinschraubY, Screw4_EinschraubZ - insertionZOffset, M_PI / 2, 0, 0);
    auto poseScrew5_Einschraub = std::make_shared<WzlPlanner::Pose>(Screw5_EinschraubX, Screw5_EinschraubY, Screw5_EinschraubZ - insertionZOffset, M_PI / 2, 0, 0); 

    auto taskScrew1_Einschraub = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew1_Einschraub->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew1_Einschraub);
      taskScrew1_Einschraub->SetId("Screw1_Einschraub");

    auto taskScrew2_Einschraub = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew2_Einschraub->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew2_Einschraub);
      taskScrew2_Einschraub->SetId("Screw2_Einschraub");

    auto taskScrew3_Einschraub = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew3_Einschraub->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew3_Einschraub);
      taskScrew3_Einschraub->SetId("Screw3_Einschraub");

    auto taskScrew4_Einschraub = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew4_Einschraub->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew4_Einschraub);
      taskScrew4_Einschraub->SetId("Screw4_Einschraub");

    auto taskScrew5_Einschraub = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew5_Einschraub->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew5_Einschraub);
      taskScrew5_Einschraub->SetId("Screw5_Einschraub");

    // schraube Einschraubpositionen Safe post

    auto taskScrew1_EinschraubSafe_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew1_EinschraubSafe_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew1_EinschraubSafe);
      taskScrew1_EinschraubSafe_post->SetId("Screw1_EinschraubSafe_post");

    auto taskScrew2_EinschraubSafe_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew2_EinschraubSafe_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew2_EinschraubSafe);
      taskScrew2_EinschraubSafe_post->SetId("Screw2_EinschraubSafe_post");

    auto taskScrew3_EinschraubSafe_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew3_EinschraubSafe_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew3_EinschraubSafe);
      taskScrew3_EinschraubSafe_post->SetId("Screw3_EinschraubSafe_post");

    auto taskScrew4_EinschraubSafe_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew4_EinschraubSafe_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew4_EinschraubSafe);
      taskScrew4_EinschraubSafe_post->SetId("Screw4_EinschraubSafe_post");

    auto taskScrew5_EinschraubSafe_post = std::make_shared<WzlPlanner::TaskMoveToPose>();
      taskScrew5_EinschraubSafe_post->SetMoveType(WzlPlanner::RobotMoveType::AbsoluteCartesian)->SetTargetPose(poseScrew5_EinschraubSafe);
      taskScrew5_EinschraubSafe_post->SetId("Screw5_EinschraubSafe_post");



  ////// TASK SCHEDULING - Phase 4: Execute screw operations //////
  RCLCPP_INFO(node->get_logger(), "UseCase 7 - Phase 4: Executing screw operations with detected positions ...");

  // ===== Set screw parameters =====
  int screwLength = 35000;  // Change this value to adjust screw length in ym (min 0 max 35000)
  int zForce = 30;          // Change this value to adjust Z-axis force in N (min 18 mx 30)
  int targetTorque = 100;    // Change this value to adjust target torque in yNm (min 100 max 5000)
  
  tasks->taskModBusWriteScrewLength->SetValue(screwLength);
  tasks->taskModBusWriteZForce->SetValue(zForce);
  tasks->taskModBusWriteTargetTorque->SetValue(targetTorque);

  auto taskList = std::make_shared<WzlPlanner::TaskList>();
  taskList->SetId("TaskList_ScrewOperations");

  taskList->AddTask(taskScrewSafe1); // schraube 1 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew1); // schraube 1 anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength); 
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteLoosenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  
  taskList->AddTask(taskScrewSafe1_post); // schraube 1 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  
  taskList->AddTask(taskScrew1_EinschraubSafe); // schraube 1 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew1_Einschraub); // schraube 1 Einschraubposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTargetTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTightenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew1_EinschraubSafe_post); // schraube 1 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);


  taskList->AddTask(taskScrewSafe2); // schraube 2 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew2); // schraube 2 anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteLoosenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  
  taskList->AddTask(taskScrewSafe2_post); // schraube 2 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew2_EinschraubSafe); // schraube 2 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew2_Einschraub); // schraube 2 Einschraubposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTargetTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTightenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew2_EinschraubSafe_post); // schraube 2 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrewSafe3); // schraube 3 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew3); // schraube 3 anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteLoosenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);


  taskList->AddTask(taskScrewSafe3_post); // schraube 3 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew3_EinschraubSafe); // schraube 3 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew3_Einschraub); // schraube 3 Einschraubposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTargetTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTightenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew3_EinschraubSafe_post); // schraube 3 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);


  taskList->AddTask(taskScrewSafe4); // schraube 4 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew4); // schraube 4  anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteLoosenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrewSafe4_post); // schraube 4 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew4_EinschraubSafe); // schraube 4 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew4_Einschraub); // schraube 4 Einschraubposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTargetTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTightenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew4_EinschraubSafe_post); // schraube 4 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  
  taskList->AddTask(taskScrewSafe5); // schraube 5 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  
  taskList->AddTask(taskScrew5); // schraube 5 anfahren
  taskList->AddTask(tasks->taskWait);  
  taskList->AddTask(tasks->taskWait);
  
  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteLoosenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);


  taskList->AddTask(taskScrewSafe5_post); // schraube 5 Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew5_EinschraubSafe); // schraube 5 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew5_Einschraub); // schraube 5 Einschraubposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTargetTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTightenScrew);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(taskScrew5_EinschraubSafe_post); // schraube 5 Einschraub Sichereitsposition anfahren
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);


  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  if (!taskList->Execute())
  {
    RCLCPP_ERROR(node->get_logger(), "Execution of UseCase 7 screw operations failed");
    return;
  }

  RCLCPP_INFO(node->get_logger(), "UseCase 7 execution successful");
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
  taskList->AddTask(tasks->taskSetSpeedPtp);
  taskList->AddTask(tasks->taskModBusWriteScrewLength);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTargetTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteShankPos20);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteLoosenScrew);

  taskList->AddTask(tasks->taskModBusReadTorqueAngleGradient);
  taskList->AddTask(tasks->taskModBusReadCurrentTorque);
  taskList->AddTask(tasks->taskModBusReadShankPos);
  taskList->AddTask(tasks->taskModBusReadZForce);
  taskList->AddTask(tasks->taskModBusReadAchievedTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusReadTorqueAngleGradient);

  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

  taskList->AddTask(tasks->taskModBusWriteZForce);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusWriteTightenScrew);

  taskList->AddTask(tasks->taskModBusReadTorqueAngleGradient);
  taskList->AddTask(tasks->taskModBusReadCurrentTorque);
  taskList->AddTask(tasks->taskModBusReadShankPos);
  taskList->AddTask(tasks->taskModBusReadZForce);
  taskList->AddTask(tasks->taskModBusReadAchievedTorque);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskModBusReadTorqueAngleGradient);

  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);
  taskList->AddTask(tasks->taskWait);

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
  // Initial state assumption: closed (false) or open (true). 
  // not really known, only after first opening/closing
  //WzlPlanner::TaskOpcuaRequest::PublishInitial(true);

  // Initialize the task status publisher
  WzlPlanner::Task::InitializePublisher(node);

  CreateCell(node);

  rclcpp::sleep_for(2000ms);
  auto misc_tasks = std::make_shared<MiscTasks>(node);

  g_misc_tasks = misc_tasks;  // Store in global variable

  rclcpp::sleep_for(2000ms);

  //Start UseCase
  int use_case = 1;  // Default value

  if (node->has_parameter("use_case")) {
      use_case = node->get_parameter("use_case").as_int();
  } else {
      node->declare_parameter<int>("use_case", 1);
      use_case = node->get_parameter("use_case").as_int();
  }

  RCLCPP_INFO(node->get_logger(), "Starting UseCase %d", use_case);
    
    // Select UseCase based on parameter
    switch (use_case) {
        case 1:
            UseCase1(node, misc_tasks);
            break;
        case 2:
            UseCase2(node, misc_tasks);
            break;
        case 3:
            UseCaseTestModBus(node, misc_tasks);
            break;
        case 4:
            UseCase4(node, misc_tasks);
            break;
        case 5:
            UseCase5(node, misc_tasks);
            break;
        case 6:
            UseCase6(node, misc_tasks);
            break;
        case 7:
            UseCase7(node, misc_tasks);
            break;
        default:
            RCLCPP_ERROR(node->get_logger(), "Invalid use case %d, using default (4)", use_case);
            UseCase1(node, misc_tasks);
    }

  rclcpp::spin(node);

  return 0;
}