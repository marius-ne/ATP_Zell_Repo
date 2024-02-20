#include "Task.h"

WzlPlanner::Task::Task()
{
}

void WzlPlanner::TaskList::Execute()
{
    for(auto&& elem: this->tasks)
        elem->Execute(); // virtual dispatch
}

void WzlPlanner::TaskMoveToPose::Execute()
{

}

void WzlPlanner::TaskOpenGripper::Execute()
{

}

void WzlPlanner::TaskCloseGripper::Execute()
{

}

void  WzlPlanner::TaskPick::Execute()
{
    WzlPlanner::TaskList list;

    auto moveToStartPose = std::make_shared<TaskMoveToPose>();
    auto openGripper = std::make_shared<TaskOpenGripper>();
    auto moveToPickPose = std::make_shared<TaskMoveToPose>();
    auto closeGripper = std::make_shared<TaskCloseGripper>();
    auto moveToEndPose = std::make_shared<TaskMoveToPose>();

    moveToStartPose->SetTargetPose(poseStart);
    moveToPickPose->SetTargetPose(posePick);
    moveToEndPose->SetTargetPose(poseEnd);

    list.AddTask((moveToStartPose);)

    // todo...
}

void  WzlPlanner::TaskPlace::Execute()
{

}

void WzlPlanner::TaskPickAndPlace::Execute()
{
    WzlPlanner::TaskList list;


    
}
