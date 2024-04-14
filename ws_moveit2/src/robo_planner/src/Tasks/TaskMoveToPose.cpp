#include "../../include/Tasks/TaskMoveToPose.h"
#include "../../include/ObjectContainer.h"


void WzlPlanner::TaskMoveToPose::Execute()
{
    auto robot = ObjectContainer::Get()->GetRobot();
    LogStart();

    if (this->targetPose != nullptr)
    {
        
        robot->MoveToPose(targetPose);

        // todo: replace this garbage code with some kind of callback 
        while (robot->GetIsProcessing())
        {
        }
    }
    else
    {
        Log(std::string("Target Pose value is NULL."));
    }

    LogEnd();
}