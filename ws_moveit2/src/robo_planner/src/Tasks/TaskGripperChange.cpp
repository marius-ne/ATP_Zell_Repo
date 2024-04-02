#include "../../include/Tasks/TaskGripperChange.h"

#include "../../include/ObjectContainer.h"

void WzlPlanner::TaskGripperChange::Execute()
{
    auto gripperChangeStation = WzlPlanner::ObjectContainer::Get()->GetScene()->GetSceneObject(this->gripperChaningStationId_);

    if (gripperChangeStation == nullptr)
    {
        //LogExecutionFailed(std::string("Gripper change station with the id not found: ") + this->gripperChaningStationId_);
        return;
    }

    auto changeStationSlot = std::static_pointer_cast<WzlPlanner::SceneObjectGripperChangeStation>(gripperChangeStation)->getGripperSlot(this->gripperId_);

    if (gripperChangeStation == nullptr)
    {
        //LogExecutionFailed(std::string("Gripper change station with the id: ") + this->gripperChaningStationId_ + std::string("has no gripper with the id: ") + this->gripperId_);
        return;
    }

    auto approachPose = changeStationSlot->GeTransformAppraocah();


}
