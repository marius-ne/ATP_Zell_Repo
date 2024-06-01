#ifndef TASKGRIPPERCLOSE_HPP
#define TASKGRIPPERCLOSE_HPP

#include "../Task.h"

namespace WzlPlanner
{
    class TaskGripperClose : public Task
    {
        public:
            bool Execute() override;
    };
}

#endif