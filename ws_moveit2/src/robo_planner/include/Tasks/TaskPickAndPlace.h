#ifndef TASKPICKANDPLACE_HPP
#define TASKPICKANDPLACE_HPP

#include "Task.h"

#include "TaskPick.h"
#include "TaskPlace.h"

namespace WzlPlanner
{

    class TaskPickAndPlace : public Task
    {
        private:
            std::shared_ptr<TaskPick> taskPick;
            std::shared_ptr<TaskPlace> taskPlace;

        public:
            void SetTaskPick(std::shared_ptr<TaskPick> taskPick) { this->taskPick = taskPick; }
            void SetTaskPlace(std::shared_ptr<TaskPlace> taskPlace) { this->taskPlace = taskPlace; }

            void Execute() override;
    };

}

#endif