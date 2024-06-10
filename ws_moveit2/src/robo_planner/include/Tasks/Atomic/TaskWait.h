#ifndef TASKWAIT_HPP
#define TASKWAIT_HPP

#include "../Task.h"

#include <memory>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

namespace WzlPlanner
{
    class TaskWait : public Task
    {
        private:
            
        public:
            TaskWait()
            {
                time_ = 1000ms;
            }  

            bool Execute() override
            {
                // wait 1 sec
                std::this_thread::sleep_for(time_);
                
                return true;
            }

            std::chrono::milliseconds time_;
    };

}

#endif