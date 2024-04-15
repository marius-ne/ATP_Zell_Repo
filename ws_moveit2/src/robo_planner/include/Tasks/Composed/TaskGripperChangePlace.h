#ifndef TASKGRIPPERCHANGEPLACE_HPP
#define TASKGRIPPERCHANGEPLACE_HPP

#include "../Task.h"

#include "../Atomic/TaskMoveToPose.h"
#include "../../SceneObjects/SceneObjectInclude.h"

namespace WzlPlanner
{

    class TaskGripperChangePlace : public Task
    {
        public:
            // if placementIndex is set to -1, the next free slot on the gripper change station is selected
            TaskGripperChangePlace(const std::string gripperChangingStationId, const int placementIndex = -1)
            {
                gripperChangingStationId_ = gripperChangingStationId;
                placementIndex_ = placementIndex;


            }

            void Execute() override;

            //void Initialize(const WzlPlanner::SceneObjectGripperChangeStation changeStation){}

        private:
            std::string gripperChangingStationId_;
            int placementIndex_;

            std::shared_ptr<TaskMoveToPose> subTaskMoveToPoseApproach_;
            std::shared_ptr<TaskMoveToPose> subTaskMoveToPoseUndock_;
            std::shared_ptr<TaskMoveToPose> subTaskMoveToPosePostApproach_;
            std::shared_ptr<TaskMoveToPose> subTaskMoveToPoseFinishApproach_;
    };

}

#endif