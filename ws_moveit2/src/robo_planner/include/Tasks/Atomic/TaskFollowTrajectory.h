#ifndef TASKFOLLOWTRAJECTORY_HPP
#define TASKFOLLOWTRAJECTORY_HPP

#include <memory>

#include "../Task.h"
#include "../../Pose.h"

namespace WzlPlanner
{

    /// @brief Makes the robot follow a path with a given set of absolute poses as fixpoints
    class TaskFollowTrajectory : public Task
    {
        
        private:
            std::vector<std::shared_ptr<Pose>> targetPoses_;

        public:
            TaskFollowTrajectory()
            {
            }

            bool Execute() override;
        
            TaskFollowTrajectory* AddPose(std::shared_ptr<Pose> pose) { this->targetPoses_.push_back(pose); return this; }            

    };
}

#endif