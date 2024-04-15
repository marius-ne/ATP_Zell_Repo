#ifndef TASKGRIPPERCHANGEPICK_HPP
#define TASKGRIPPERCHANGEPICK_HPP

#include "../Task.h"

namespace WzlPlanner
{

    class TaskChangeGripperPick : public Task
    {
        public:
            // if placementIndex is set to -1, the next free slot on the gripper change station is selected
            TaskChangeGripperPick(const std::string gripperChangingStationId, const std::string gripperId)
            {
                grippperChangingStationId_ = gripperChangingStationId;
                gripperId_ = gripperId;
            }

            void Execute() override;

        private:
            //TaskChangeGripperPick(const TaskChangeGripperPick& copy) {}
            //TaskChangeGripperPick(TaskChangeGripperPick&& copy) {}
            std::string grippperChangingStationId_;
            std::string gripperId_;
    };
    
}

#endif