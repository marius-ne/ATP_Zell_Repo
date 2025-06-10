#ifndef MISC_TASKS_HPP 
#define MISC_TASKS_HPP

#include <memory>
#include <chrono> 
#include <rclcpp/rclcpp.hpp>

class MiscTasks
{
public:
  // Constructor
  MiscTasks(const rclcpp::Node::SharedPtr &node);

public:
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
};

#endif // MISC_TASKS_HPP