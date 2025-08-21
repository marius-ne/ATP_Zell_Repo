#ifndef TASKPARTATTACH_HPP
#define TASKPARTATTACH_HPP

#include "../Task.h"

namespace WzlPlanner
{
    class TaskPartAttach : public Task
    {
        private:
            std::string partKey_ = " ";
            int partType_; 
            int workpieceOrientation_;

        public:
        TaskPartAttach(const std::string partKey = " ", int partType = 0, int workpieceOrientation = 0)
            { 
                partKey_ = partKey;
                partType_ = partType;
                workpieceOrientation_ = workpieceOrientation;
            }  

            bool Execute() override
            {
            auto robot = ObjectContainer::Get()->GetRobot();
            LogStart();

            robot->PartAttach(partKey_, partType_, workpieceOrientation_);

            LogEnd();

            return true;
            
            }
    };

}

#endif