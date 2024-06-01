#include "../../include/Tasks/Atomic/TaskGripperClose.h"
#include "../../include/ObjectContainer.h"

bool WzlPlanner::TaskGripperClose::Execute()
{
    LogStart();

    auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();

    if (robot->HasGripper())
    {
        robot->GetGripper()->Close();
    }
    else
    {
        RCLCPP_INFO(WzlPlanner::ObjectContainer::Get()->GetNode()->get_logger(), "Can't close gripper: Robot has no gripper attached.");
        return false;
    }

    LogEnd();

    return true;
}