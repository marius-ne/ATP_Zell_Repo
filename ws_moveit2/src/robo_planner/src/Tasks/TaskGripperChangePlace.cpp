#include "../../include/Tasks/Composed/TaskGripperChangePlace.h"

#include "../../include/ObjectContainer.h"

void WzlPlanner::TaskGripperChangePlace::Execute()
{
    auto gripperChangeStation = ObjectContainer::Get()->GetScene()->GetSceneObject(this->gripperChangingStationId_);
    
    if (gripperChangeStation == nullptr)
    {
        //LogExecutionFailed(std::string("Gripper change station with the id not found: ") + this->gripperChangingStationId_);
        return;
    }

    auto gripperChangeStationCast = std::static_pointer_cast<WzlPlanner::SceneObjectGripperChangeStation>(gripperChangeStation);
    int targetSlot = this->placementIndex_;

    if (targetSlot== -1)
    {
        // no target slot indicated: get the next free slot on the changing station
        auto freeSlot = gripperChangeStationCast->GetNextFreeGripperSlot();

        if (freeSlot == nullptr)
        {
            //LogExecutionFailed(std::string("Gripper change station with the id has not free slot to place the current gripper: ") + this->gripperChangingStationId_);
            return;
        }

        targetSlot = gripperChangeStationCast->GetNextFreeGripperSlot()->GetIndex();
    }

    // move robot tcp to target approach position


    // move robot tcp to target docking slot and release the current gripper

    // move robot tcp to target post approach position




}