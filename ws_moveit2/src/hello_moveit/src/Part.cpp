#include "Part.h"

WzlPlanner::PartChassis::PartChassis()
{
    this->grippingPose = std::make_shared<Pose>();
    this->grippingPose->SetPositionXYZ(0, 0, 0);
    this->grippingPose->SetRotationXYZ(0, 0, 0);
}
