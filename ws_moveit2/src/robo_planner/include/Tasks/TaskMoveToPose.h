#ifndef TASKMOVETOPOSE_HPP
#define TASKMOVETOPOSE_HPP

#include "Task.h"
#include "../Pose.h"

namespace WzlPlanner
{
    class TaskMoveToPose : public Task
    {
        
        private:
            std::shared_ptr<Pose> targetPose;

        public:
            TaskMoveToPose()
            {
                targetPose = nullptr;
            }

            void Execute() override;
        
            void SetTargetPose(std::shared_ptr<Pose> targetPose) { this->targetPose = targetPose; }

    };
}

#endif