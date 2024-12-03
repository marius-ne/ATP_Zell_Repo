#ifndef TASKPARTATTACH_HPP
#define TASKPARTATTACH_HPP

#include "../Task.h"

namespace WzlPlanner
{
    class TaskPartAttach : public Task
    {
        private:
            std::string partKey_ = " ";

        public:
            TaskPartAttach(const std::string partKey = " ")
            { 
                partKey_ = partKey;
            }  

            bool Execute() override
            {
            auto robot = ObjectContainer::Get()->GetRobot();
            LogStart();

            robot->PartAttach(partKey_);

            LogEnd();

            return true;
            
            }
    };

}

#endif