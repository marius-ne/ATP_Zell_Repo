#ifndef SCENEOBJECTDOOR_HPP
#define SCENEOBJECTDOOR_HPP

#include "SceneObject.h"
#include "../IoInterface.h"

#include <memory>

namespace WzlPlanner
{

    class SceneObjectDoor : public SceneObject{
        private:

            std::shared_ptr<WzlPlanner::IoInterfaceBase> ioInterface_;
            int ioSlotOpenDoor_;
            int ioSlotCloseDoor_;
            bool valueForOpenDoor_;
            bool valueForCloseDoor_;

            // 1: open; 2: closed; 3: opening; 4: closing
            int state_;

        public:
            SceneObjectDoor(
                const std::string id, 
                const std::shared_ptr<WzlPlanner::IoInterfaceBase> ioInterface, 
                const int ioSlotOpenDoor,
                const int ioSlotCloseDoor,
                const bool valueForOpenDoor = true,
                const bool valueForCloseDoor = false)
                    : SceneObject(id)
                {
                    ioInterface_ = ioInterface;
                    ioSlotOpenDoor_ = ioSlotOpenDoor;
                    ioSlotCloseDoor_ = ioSlotCloseDoor;
                    valueForOpenDoor_ = valueForOpenDoor;
                    valueForCloseDoor_ = valueForCloseDoor;
                }

                SceneObjectType GetObjectType() const override { return SceneObjectType::Door; }

                bool OpenDoor()
                {
                    ioInterface_->SetValueBool(ioSlotOpenDoor_, valueForOpenDoor_);
                    return true;
                }

                bool CloseDoor()
                {
                    ioInterface_->SetValueBool(ioSlotCloseDoor_, valueForCloseDoor_);
                    return true;
                }
    };

}

#endif
