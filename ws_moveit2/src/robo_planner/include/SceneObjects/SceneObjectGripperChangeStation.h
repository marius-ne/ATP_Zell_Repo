#ifndef SCENEOBJECTGRIPPERCHANGESTATION_HPP
#define SCENEOBJECTGRIPPERCHANGESTATION_HPP

#include "SceneObject.h"
#include "SceneObjectType.h"
#include "../Gripper.h"

#include <memory>

namespace WzlPlanner
{

    class SceneObjectGripperChangeStationSlot : public SceneObject
    {
        private:
            std::shared_ptr<GripperBase> dockedGripper_;
            int index_;

            //std::shared_ptr<WzlPlanner::Transform> transformApproach_;

        public:
            SceneObjectGripperChangeStationSlot(std::string id, int index, std::shared_ptr<GripperBase> initialGripper = nullptr) 
                : SceneObject(id)
            {
                dockedGripper_ = initialGripper;
                index_ = index;

                // set approach offset
                //GeTransformAppraocah()->GetPoseRelative()->SetPositionXYZ(0 , 0.5f, 0);
            }

            SceneObjectType GetObjectType() const override { return SceneObjectType::EquipmentChangeStationSlot; }
            int GetIndex() const { return index_; }

            void PlaceGripper(const std::shared_ptr<GripperBase> gripper)
            {
                dockedGripper_ = gripper;
            } 

            bool HasGripper() { return dockedGripper_ != nullptr; }
            bool HasGripper(const std::string gripperId) { return HasGripper() && dockedGripper_->GetId() == gripperId; }

            std::shared_ptr<GripperBase> PickGripper()
            {
                auto gripper = dockedGripper_;
                dockedGripper_ = nullptr;

                return gripper;
            }

            void InitializeTransform(std::shared_ptr<Transform> parent) override 
            {
                transformOrigin_ = std::make_shared<Transform>(id_);
                transformOrigin_->SetParent(parent);

                transformApproach_ = std::make_shared<WzlPlanner::Transform>(id_  + "_Approach");
                transformApproach_->SetParent(parent);

                //for (auto&& slot: gripperSlots_)
                //{
                //    slot->InitializeTransform(GetTransform());
                //}
            }
    };

    class SceneObjectGripperChangeStation : public SceneObject
    {
        private:
            std::vector<std::shared_ptr<SceneObjectGripperChangeStationSlot>> gripperSlots_;

        public:
            SceneObjectGripperChangeStation(std::string id) 
                : SceneObject(id)
            {
                // todo: this is just an example with 3 spaces
                //gripperSlots_ = std::vector<std::shared_ptr<GripperBase>>(5);
                //gripperSlots_.at(0) = std::make_shared<GripperCameraToF>();

                gripperSlots_ = std::vector<std::shared_ptr<SceneObjectGripperChangeStationSlot>>
                {
                    std::make_shared<SceneObjectGripperChangeStationSlot>(id + "1", 0, std::make_shared<GripperCameraToF>("Camera")),
                    std::make_shared<SceneObjectGripperChangeStationSlot>(id + "2", 1, std::make_shared<GripperDeburringSpindle>("DeburringSpindle", 6)),
                    std::make_shared<SceneObjectGripperChangeStationSlot>(id + "3", 2, std::make_shared<GripperPneumaticSingle>("GripperDouble", 0, 1)),
                    std::make_shared<SceneObjectGripperChangeStationSlot>(id + "4", 3, std::make_shared<GripperPneumaticDouble>("GripperSingle", 2, 3, 4, 5)),
                    std::make_shared<SceneObjectGripperChangeStationSlot>(id + "5", 4, nullptr) 
                };

                //if (gripperSlots_.at(0) != nullptr) gripperSlots_.at(0)->GetTransform()->GetPoseRelative()->SetPositionX(-1);
                //if (gripperSlots_.at(1) != nullptr) gripperSlots_.at(1)->GetTransform()->GetPoseRelative()->SetPositionX(-0.5);
                //if (gripperSlots_.at(2) != nullptr) gripperSlots_.at(2)->GetTransform()->GetPoseRelative()->SetPositionX(0);
                //if (gripperSlots_.at(3) != nullptr) gripperSlots_.at(3)->GetTransform()->GetPoseRelative()->SetPositionX(0.5);
                //if (gripperSlots_.at(4) != nullptr) gripperSlots_.at(4)->GetTransform()->GetPoseRelative()->SetPositionX(1);
            }

            void InitializeTransform(std::shared_ptr<Transform> parent) override 
            {
                SceneObject::InitializeTransform(parent);

                for (auto&& slot: gripperSlots_)
                {
                    slot->InitializeTransform(GetTransform());
                }
            }

            SceneObjectType GetObjectType() const override { return SceneObjectType::EquipmentChangeStation; }

            void PlaceGripper(const std::shared_ptr<GripperBase> gripper, const int slotIndex)
            {
                gripperSlots_.at(slotIndex)->PlaceGripper(gripper);
            } 

            std::shared_ptr<GripperBase> PickGripper(const int index)
            {
                return gripperSlots_.at(index)->PickGripper();
            }

            std::shared_ptr<GripperBase> PickGripper(const std::string gripperId)
            {
                for (auto&& gripperSlot: gripperSlots_)
                {
                    if (gripperSlot->HasGripper(gripperId))
                    {
                        return gripperSlot->PickGripper();
                    }
                }

                return nullptr;
            }

            std::shared_ptr<SceneObjectGripperChangeStationSlot> getGripperSlot(const std::string gripperId)
            {
                for (auto&& gripperSlot: gripperSlots_)
                {
                    if (gripperSlot->HasGripper(gripperId))
                    {
                        return gripperSlot;
                    }
                }

                return nullptr;
            }

            std::shared_ptr<SceneObjectGripperChangeStationSlot> GetNextFreeGripperSlot()
            {
               for (auto&& gripperSlot: gripperSlots_)
                {
                    if (!gripperSlot->HasGripper())
                    {
                        return gripperSlot;
                    }
                } 

                return nullptr;
            }

    };

}

#endif