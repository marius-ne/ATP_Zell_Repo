#ifndef TASKGRIPPERPICK_HPP
#define TASKGRIPPERPICK_HPP

#include "Task.h"

#include "../Pose.h"

namespace WzlPlanner
{

    class TaskPick : public Task
    {
        public:
            void Execute() override;
            
            void SetPoseStart(std::shared_ptr<Pose> pose) { this->poseStart = pose; }
            void SetPosePick(std::shared_ptr<Pose> pose) { this->poseEnd = pose; }
            void SetPoseEnd(std::shared_ptr<Pose> pose) { this->poseEnd = pose; }

        private:
            std::shared_ptr<Pose> poseStart;
            std::shared_ptr<Pose> posePick;
            std::shared_ptr<Pose> poseEnd;
    };

}

#endif