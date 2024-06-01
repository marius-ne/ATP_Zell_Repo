#include "../../include/Tasks/Atomic/TaskFollowTrajectory.h"
#include "../../include/ObjectContainer.h"


bool WzlPlanner::TaskFollowTrajectory::Execute()
{
    auto robot = ObjectContainer::Get()->GetRobot();
    LogStart();

    robot->FollowTrajectory(this->targetPoses_);

    LogEnd();

    return true;
}