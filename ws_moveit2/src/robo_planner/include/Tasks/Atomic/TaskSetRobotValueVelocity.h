#ifndef TASKSETROBOTVALUEVELOCITY_HPP
#define TASKSETROBOTVALUEVELOCITY_HPP

#include "../Task.h"

namespace WzlPlanner
{
    class TaskSetRobotValueVelocity : public Task
    {
        private:
            // velocity value range [0..1]
            double velocity_ = 1;
            // acceleration value range [0..1]
            double acceleration_ = 1;
            // indicates for which motion planner type the velocity and acceleration value is set
            // 0: ompl; 1: pilz industrial motion planner
            int type_ = 0;

        public:
            TaskSetRobotValueVelocity(const double velocity = 1.0, const double acceleration = 1.0, const double type = 0)
            {
                velocity_ = velocity;
                acceleration_ = acceleration;
                type_ = type;
            }  

            void SetVelocity(const double value) { velocity_ = value; }
            void SetAcceleration(const double value) { acceleration_ = value; }
            void SetType(const int value) { type_ = value; }


            bool Execute() override
            {
                auto robot = ObjectContainer::Get()->GetRobot();
                LogStart();

                robot->SetVelocity(velocity_, acceleration_, type_);

                LogEnd();

                return true;
            }
    };

}

#endif