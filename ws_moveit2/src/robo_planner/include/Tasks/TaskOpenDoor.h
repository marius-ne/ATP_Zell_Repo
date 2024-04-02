#ifndef TASKOPENDOOR_HPP
#define TASKOPENDOOR_HPP

#include "Task.h"

namespace WzlPlanner
{

    class TaskOpenDoor : public Task
    {
        private:
            // 1: Open; 2: Close; 3: Opening; 4: Closing
            int currentState_; 

        public:
            TaskOpenDoor()
            {
                currentState_ = 2;
            }  

            bool OpenDoor();
            bool CloseDooor();
    };

}

#endif