#ifndef TASKSCANSCENE_HPP
#define TASKSCANSCENE_HPP

#include "Task.h"
#include "../Robot.h"
#include "../SceneObjects/SceneObject.h"

#include <memory>
#include <vector>

namespace WzlPlanner
{
    class TaskScanScene : public Task
    {
        private:
            std::shared_ptr<WzlPlanner::Robot> robot_;
            std::vector<std::shared_ptr<SceneObject>> objectsInScene;

        public:
        
            void Execute() override;
            void Initialize(
                float minX, float maxX, int scanCountX,
                float minY, float maxY, int scaneCountY, 
                float z,
                float eulerX, float eulerY, float eulerZ);
    };
}

#endif