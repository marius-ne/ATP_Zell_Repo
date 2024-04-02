#ifndef TASKGRIPPEROPEN_HPP
#define TASKGRIPPEROPEN_HPP

#include "Task.h"

namespace WzlPlanner
{
    class TaskGripperOpen : public Task
    {
        public:
            void Execute() override;
        
    };
}

#endif