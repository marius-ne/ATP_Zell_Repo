#include "../../include/Tasks/Composed/TaskGripperChange.h"

#include "../../include/ObjectContainer.h"

bool WzlPlanner::TaskGripperChange::Execute()
{
    auto gripperChangeStation = WzlPlanner::ObjectContainer::Get()->GetScene()->GetSceneObject(this->gripperChaningStationId_);

    if (gripperChangeStation == nullptr)
    {
        //LogExecutionFailed(std::string("Gripper change station with the id not found: ") + this->gripperChaningStationId_);
        return false;
    }

    auto changeStationSlot = std::static_pointer_cast<WzlPlanner::SceneObjectGripperChangeStation>(gripperChangeStation)->getGripperSlot(this->gripperId_);

    if (gripperChangeStation == nullptr)
    {
        //LogExecutionFailed(std::string("Gripper change station with the id: ") + this->gripperChaningStationId_ + std::string("has no gripper with the id: ") + this->gripperId_);
        return false;
    }

    auto approachPose = changeStationSlot->GeTransformAppraocah();
    
    return true;
}
