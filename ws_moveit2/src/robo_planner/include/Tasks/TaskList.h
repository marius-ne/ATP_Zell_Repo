#ifndef TASKLIST_HPP
#define TASKLIST_HPP

#include "Task.h"

#include <memory>
#include <vector>

namespace WzlPlanner
{
    class TaskList : public Task
    {

        public:
            void AddTask(std::shared_ptr<Task> task) { tasks.push_back(task); }

            bool Execute() override;

        private:
            std::vector<std::shared_ptr<Task>> tasks;

    };
}

#endif