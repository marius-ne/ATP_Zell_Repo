#ifndef TASKGRIPPERCHANGE_HPP
#define TASKGRIPPERCHANGE_HPP

#include "../Task.h"

#include "TaskGripperChangePlace.h"
#include "TaskGripperChangePick.h"

namespace WzlPlanner
{

    class TaskGripperChange : public Task
    {
        public:
            TaskGripperChange(const std::string gripperChangingStationId, const std::string gripperId, const int gripperPlaceIndex = -1)
            {
                gripperChaningStationId_ = gripperChangingStationId;
                gripperId_ = gripperId;

                subTaskChangeGripperPlace_ = std::make_shared<TaskGripperChangePlace>(gripperChangingStationId, gripperPlaceIndex);
                subTaskChangeGripperPick_ = std::make_shared<TaskChangeGripperPick>(gripperChangingStationId, gripperId);
            }

            bool Execute() override;

            std::string GetGripperId() { return gripperId_; }
            void SetGripperId(const std::string gripperId) { gripperId_ = gripperId; }

            std::string GetGripperChangingStationId() { return gripperChaningStationId_; }
            void SetGripperChangingStationId(const std::string gripperChangingStationId) { gripperChaningStationId_ = gripperChangingStationId; }

            std::shared_ptr<TaskGripperChangePlace> GetSubTaskChangeGripperPlace() const { return subTaskChangeGripperPlace_; }
            std::shared_ptr<TaskChangeGripperPick> GetSubTaskChangeGripperPick_() const { return subTaskChangeGripperPick_; }

        private:
            std::string gripperId_;
            std::string gripperChaningStationId_;

            std::shared_ptr<TaskGripperChangePlace> subTaskChangeGripperPlace_;
            std::shared_ptr<TaskChangeGripperPick> subTaskChangeGripperPick_;
    };

}

#endif