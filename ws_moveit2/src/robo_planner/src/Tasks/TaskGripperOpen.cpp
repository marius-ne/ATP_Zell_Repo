#include "../../include/Tasks/Atomic/TaskGripperOpen.h"
#include "../../include/ObjectContainer.h"


bool WzlPlanner::TaskGripperOpen::Execute()
{
    LogStart();

    auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();

    if (robot->HasGripper())
    {
        robot->GetGripper()->Open();
    }
    else
    {
        RCLCPP_INFO(WzlPlanner::ObjectContainer::Get()->GetNode()->get_logger(), "Can't open gripper: Robot has no gripper attached.");
        return false;
    }

    LogEnd();

    return true;
}