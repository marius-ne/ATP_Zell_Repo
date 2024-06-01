#ifndef TASKSETROBOTVALUEVELOCITY_HPP
#define TASKSETROBOTVALUEVELOCITY_HPP

#include "../Task.h"

namespace WzlPlanner
{
    class TaskSetRobotValueVelocity : public Task
    {
        private:
            // velocity value range [0..1]
            double value_ = 1;

        public:
            TaskSetRobotValueVelocity()
            {
            }  

            void SetValue(const double value) { value_ = value; }

            bool Execute() override
            {
                auto robot = ObjectContainer::Get()->GetRobot();
                LogStart();

                robot->SetVelocity(value_);

                LogEnd();

                return true;
            }
    };

}

#endif