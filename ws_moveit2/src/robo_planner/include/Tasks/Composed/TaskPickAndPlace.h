#ifndef TASKPICKANDPLACE_HPP
#define TASKPICKANDPLACE_HPP

#include "../Task.h"

#include "TaskPick.h"
#include "TaskPlace.h"

namespace WzlPlanner
{

    class TaskPickAndPlace : public Task
    {
        public:

            TaskPickAndPlace()
            {
                taskPick_ = std::make_shared<TaskPick>();
                taskPlace_ = std::make_shared<TaskPlace>();

                subTasks_.push_back(taskPick_);
                subTasks_.push_back(taskPlace_);
            }

            void SetId(const std::string id) override 
            {
                Task::SetId(id);

                taskPick_->SetId(id + "_Pick");
                taskPlace_->SetId(id + "_Place");
            }

            std::shared_ptr<TaskPick> GetTaskPick() const { return taskPick_; }
            std::shared_ptr<TaskPlace> GetTaskPlace() const { return taskPlace_; }

        private:
            std::shared_ptr<TaskPick> taskPick_;
            std::shared_ptr<TaskPlace> taskPlace_;
    };

}

#endif