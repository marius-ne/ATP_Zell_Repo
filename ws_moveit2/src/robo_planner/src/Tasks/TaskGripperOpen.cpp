#include "../../include/Tasks/TaskGripperOpen.h"
#include "../../include/ObjectContainer.h"

void WzlPlanner::TaskGripperOpen::Execute()
{
    //auto slotGripperOpen = WzlPlanner::ObjectContainer_->GetRobot()->

    //WzlPlanner::ObjectContainer_->GetioInterface()->SetValueBool(this->)

    LogStart();

    auto robot = WzlPlanner::ObjectContainer::Get()->GetRobot();


    if (robot->HasGripper())
    {
        robot->GetGripper()->Open();
    }
    else
    {
        RCLCPP_INFO(WzlPlanner::ObjectContainer::Get()->GetNode()->get_logger(), "Can't open gripper: Robot has no gripper attached.");
    }

    LogEnd();
}