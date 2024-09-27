#include "../../include/Tasks/Atomic/TaskMoveToPose.h"
#include "../../include/ObjectContainer.h"


bool WzlPlanner::TaskMoveToPose::Execute()
{
    auto robot = ObjectContainer::Get()->GetRobot();
    LogStart();

    if (this->targetPose != nullptr)
    {
        if (!robot->MoveToPose(targetPose, moveType))
        {
            Log("Unable to perform MoveToPose Task.");
            return false;
        }
    }
    else
    {
        Log(std::string("Target Pose value is NULL."));
        return false;
    }

    LogEnd();

    return true;
}