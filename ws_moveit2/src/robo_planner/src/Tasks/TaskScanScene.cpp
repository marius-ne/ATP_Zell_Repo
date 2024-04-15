#include "../../include/Tasks/Composed/TaskScanScene.h"


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
