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

    list.AddTask((moveToStartPose));
    list.AddTask(openGripper);
    list.AddTask(moveToPickPose);
    list.AddTask(closeGripper);
    list.AddTask(moveToEndPose);

    list.Execute();
}

void  WzlPlanner::TaskPlace::Execute()
{

}

void WzlPlanner::TaskPickAndPlace::Execute()
{
    this->taskPick->Execute();
    this->taskPlace->Execute();
}

void WzlPlanner::TaskScanScene::Execute()
{

}

void WzlPlanner::TaskScanScene::Initialize(
    float minX, float maxX, int scanCountX, 
    float minY, float maxY, int scanCountY, 
    float z, 
    float eulerX, float eulerY, float eulerZ)
{
    std::vector<std::shared_ptr<Pose>> poses;


    float deltaX = 0;
    float deltaY = 0;

    if (scanCountX <= 1)
    {
        maxX = minX;
    }
    else
    {
        deltaX = (maxX - minX) / scanCountX;
    }

    if (scanCountY <= 1)
    {
        maxY = minY;
    }
    else
    {
        deltaY = (maxY - minY) / scanCountY;
    }

    float currentPositionx = minX;
    float currentPositionY = minY;

    for (int x = 0; x < scanCountX; x++)
    {
        for (int y = 0; y < scanCountY; y++)
        {
            auto pose = std::make_shared<WzlPlanner::Pose>();
            pose->SetPositionXYZ(currentPositionx, currentPositionY, z);
            pose->SetRotationXYZ(eulerX, eulerY, eulerZ);
            poses.push_back(pose);

            currentPositionY += deltaY;
        }

        currentPositionY = minY;
        currentPositionx += deltaX;
    }
}
