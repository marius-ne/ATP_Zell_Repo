#ifndef TASKMOVETOPOSE_HPP
#define TASKMOVETOPOSE_HPP

#include "../Task.h"
#include "../../Pose.h"

namespace WzlPlanner
{

    class TaskMoveToPose : public Task
    {
        
        private:
            std::shared_ptr<Pose> targetPose;
            RobotMoveType moveType;

        public:
            TaskMoveToPose()
            {
                targetPose = nullptr;
            }

            bool Execute() override;
        
            TaskMoveToPose* SetTargetPose(std::shared_ptr<Pose> targetPose) { this->targetPose = targetPose; return this; }
            TaskMoveToPose* SetMoveType(const RobotMoveType moveType) { this->moveType = moveType; return this; }
            RobotMoveType GetMoveType() const { return moveType; }

    };
}

#endif