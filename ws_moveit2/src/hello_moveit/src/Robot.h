#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <memory>

#include "Pose.h"

namespace WzlPlanner
{
    class Robot
    {
        protected:
            bool isProcessing_;

        public:
            Robot() {}

            bool GetIsProcessing() const { return isProcessing_; }

            void MoveToPose(std::shared_ptr<WzlPlanner::Pose> targetPose);
    };

    class RobotDummy : public Robot
    {

    };

    class RobotUR : public Robot
    {

    };

} // namespace WzlPlanner

#endif // ROBOT_HPP