#ifndef TASKPARTDETACH_HPP
#define TASKPARTDETACH_HPP

#include "../Task.h"

namespace WzlPlanner
{
    class TaskPartDetach : public Task
    {
        private:
            std::string partKey_ = " ";

        public:
            TaskPartDetach(const std::string partKey = " ")
            { 
                partKey_ = partKey;
            }  

            bool Execute() override
            {
            auto robot = ObjectContainer::Get()->GetRobot();
            LogStart();

            robot->PartDetach(partKey_);

            LogEnd();

            return true;
            
            }
    };

}

#endif