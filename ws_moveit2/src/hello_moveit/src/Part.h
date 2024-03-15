#ifndef PART_HPP
#define PART_HPP

#include <string>
#include <memory>

#include "Pose.h"

namespace WzlPlanner
{
    class PartBase
    {
        protected:
            // pose offset for robot gripping: opse is applied to the grip position 
            // first the rotation, then the translation is applied
            std::shared_ptr<Pose> grippingPose;

        public:
            virtual std::string GetPartName() const = 0;
            std::shared_ptr<Pose> GetGrippingPose() const { return this->grippingPose; }
    };

    class PartChassis : public PartBase
    {
        public:
            std::string GetPartName() const override { return "Chassis"; }
            PartChassis();
    };

} // namepspace

#endif