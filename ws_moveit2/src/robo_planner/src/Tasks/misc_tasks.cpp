#include "../../include/Tasks/misc_tasks.h"

#include "../../include/SceneObjects/SceneObject.h"

#include "../../include/ObjectContainer.h"

#include "../../include/Tasks/TaskInclude.h"

MiscTasks::MiscTasks(const rclcpp::Node::SharedPtr &node)
{
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
      std::shared_ptr<WzlPlanner::TaskModBusRead> taskIoModBusReadToolType;
      std::shared_ptr<WzlPlanner::TaskModBusInterpretReadResult> taskIoModBusCheckCorrectToolType;
      std::shared_ptr<WzlPlanner::TaskModBusWrite> taskIoModBusWriteTightenScrew;
    
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
    
        taskIoModBusReadToolType = std::make_shared<WzlPlanner::TaskModBusRead>(
            WzlPlanner::ModBusData::GetModBusData_ToolType_Read());
        taskIoModBusReadToolType->SetId("taskIoModBusReadToolType");
    
        taskIoModBusCheckCorrectToolType = std::make_shared<WzlPlanner::TaskModBusInterpretReadResult>(
            taskIoModBusReadToolType);
        taskIoModBusCheckCorrectToolType->SetId("taskIoModBusCheckCorrectToolType");
        taskIoModBusCheckCorrectToolType->SetComparisonValue("Screwdrivers");
    
        taskIoModBusWriteTightenScrew = std::make_shared<WzlPlanner::TaskModBusWrite>(
            WzlPlanner::ModBusData::GetModBusData_TightenScrew_Write());
        taskIoModBusWriteTightenScrew->SetId("taskIoModBusWriteTightenScrew");
    
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
}

template <typename T>
T get_parameter(const rclcpp::Node::SharedPtr &node, const std::string &name, const T &default_value)
{
  // Placeholder for logic to read or return default_value
  return default_value;
}