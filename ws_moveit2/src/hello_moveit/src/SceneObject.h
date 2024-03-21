#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP

#include <memory>
#include <array>

#include "Pose.h"
#include "Part.h"
#include "Gripper.h"



namespace WzlPlanner
{
    
    enum SceneObjectType
    {
        ClampingDeviceJaws = 1,
        ClampingDeviceElevation = 2,
        Carrier = 3,
        CarrierSlot = 4,
        EquipmentChangeStation = 5,
        EquipmentChangeStationSlot = 6,
        VisualScanTower = 7
    };

    class SceneObject
    {
        private:
            // origin of the scene object
            std::shared_ptr<WzlPlanner::Transform> transformOrigin_;

            // robot approach transform
            std::shared_ptr<WzlPlanner::Transform> transformApproach_;

        protected:
            std::string id_;

            SceneObject(std::string id) 
            {
                id_ = id;
            }

        public:
            //std::shared_ptr<WzlPlanner::Transform> GetTransform() const { return transformOrigin_; }
            virtual std::shared_ptr<Transform> GetTransform() const { return this->transformOrigin_; }
            std::shared_ptr<Transform> GeTransformAppraocah() const { return this->transformApproach_; }
            virtual SceneObjectType GetObjectType() const = 0;
            std::string GetId() const { return id_; };


            virtual void InitializeTransform(const std::shared_ptr<Transform> parent)
            {
                transformOrigin_ = std::make_shared<Transform>(id_);
                transformOrigin_->SetParent(parent);

                transformApproach_ = std::make_shared<WzlPlanner::Transform>(id_  + "_Approach");
                transformApproach_->SetParent(transformOrigin_);
            }
    };

    class SceneObjectClampingDeviceBase : public SceneObject
    {
        protected:
            SceneObjectClampingDeviceBase(std::string id) 
                : SceneObject(id)
            {
            }

            // Interface for Closing/opening the clamping device
            int ioOpen, ioClose;
            bool isOpen, isClose;

            void SetOpen(const bool isOpened);

        public:
            virtual void Open() = 0;
            virtual void Close() = 0;

            bool IsOpen() const { return this->isOpen; }
            bool IsClose() const { return this->isClose; }
    };

    class SceneObjectClampingDeviceJaws : public SceneObjectClampingDeviceBase
    {
        public:
            SceneObjectClampingDeviceJaws(std::string id) 
                : SceneObjectClampingDeviceBase(id)
            {
            }

            SceneObjectType GetObjectType() const override { return SceneObjectType::ClampingDeviceJaws; }

            void Open() override;
            void Close() override;
    };

    class SceneObjectClampingDeviceElevation : public SceneObjectClampingDeviceBase
    {
        public:
            SceneObjectClampingDeviceElevation(std::string id) 
                : SceneObjectClampingDeviceBase(id)
            {
            }

            SceneObjectType GetObjectType() const override { return SceneObjectType::ClampingDeviceElevation; }

            void Open() override;
            void Close() override;
    };

    class SceneObjectCarrierSlot : public SceneObject
    {
        private:
            std::shared_ptr<Pose> poseScene;
            std::shared_ptr<PartBase> part_;

        public:
            SceneObjectType GetObjectType() const override { return SceneObjectType::Carrier; }

            SceneObjectCarrierSlot(std::string id): SceneObject(id) 
            {
                part_ = nullptr;
            }

            void UpdatePoseScene();

            bool HasPart() const { return part_ != nullptr; }
            
            std::shared_ptr<PartBase> PickPart() 
            { 
                auto part = part_;
                part_ = nullptr;
                return part;
            }

            void PlacePart(const std::shared_ptr<PartBase> part) { part_ = part; }


    };

    class SceneObjectCarrier : public SceneObject
    {
        private:
            std::vector<std::unique_ptr<SceneObjectCarrierSlot>> slots_;
            float firstSlotOriginX_, firstSlotOriginY_;
            float slotGapX_, slotGapY_;
            int slotsCountX_, slotsCountY;

        public:
            SceneObjectType GetObjectType() const override { return SceneObjectType::Carrier; }

            SceneObjectCarrier(std::string id) 
                : SceneObject(id)
            {
                firstSlotOriginX_ = 0;
                firstSlotOriginY_ = 0;
                slotGapX_ = 0.3f;
                slotGapY_ = 0.2f;
                slotsCountX_ = 5;
                slotsCountY = 4;
                int totalCount = slotsCountX_ * slotsCountY;

                slots_ = std::vector<std::unique_ptr<SceneObjectCarrierSlot>>(totalCount);
                int indexCounter = 0;

                for (auto& slot: slots_)
                {
                    slot = std::make_unique<SceneObjectCarrierSlot>(id + std::to_string(indexCounter++));
                }
            }

            int GetMaxSlotCount() const { return slots_.size(); }
            //bool HasFreeSlots() const  { return std::count(slots_.begin(), slots_.end(), [](auto) { return true; }) > 0; }
            //bool HasParts() const { return std::count(slots_.begin(), slots_.end(), HasPart()) < slots_.size(); }

            void InitializeTransform(std::shared_ptr<Transform> parent) override 
            {
                SceneObject::InitializeTransform(parent);

                int counter = 0;

                for (auto & slot : slots_) 
                {
                    float currentPosX = firstSlotOriginX_ + (counter % slotsCountX_) * slotGapX_;
                    float currentPosY = firstSlotOriginY_ + (counter / slotsCountY) * slotGapY_;

                    slot->GetTransform()->GetPoseRelative()->SetPositionXYZ(currentPosX, currentPosY, 0);
                    slot->GeTransformAppraocah()->GetPoseRelative()->SetPositionZ(0.2f);

                    counter++;
                }
            }
    };

    class SceneObjectGripperChangeStationSlot : public SceneObject
    {
        private:
            std::shared_ptr<GripperBase> dockedGripper_;

        public:
            SceneObjectGripperChangeStationSlot(std::string id, std::shared_ptr<GripperBase> initialGripper = nullptr) 
                : SceneObject(id)
            {
                dockedGripper_ = initialGripper;

                // set approach offset
                GeTransformAppraocah()->GetPoseRelative()->SetPositionXYZ(0 , 0.5f, 0);
            }

            SceneObjectType GetObjectType() const override { return SceneObjectType::EquipmentChangeStationSlot; }

            void PlaceGripper(const std::shared_ptr<GripperBase> gripper)
            {
                dockedGripper_ = gripper;
            } 

            std::shared_ptr<GripperBase> PickGripper()
            {
                auto gripper = dockedGripper_;
                dockedGripper_ = nullptr;

                return gripper;
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
                    std::make_shared<SceneObjectGripperChangeStationSlot>(id + "1", std::make_shared<GripperCameraToF>("Camera")),
                    std::make_shared<SceneObjectGripperChangeStationSlot>(id + "2", std::make_shared<GripperDeburringSpindle>("DeburringSpindle")),
                    std::make_shared<SceneObjectGripperChangeStationSlot>(id + "3", std::make_shared<GripperPneumaticSingle>("GripperDouble")),
                    std::make_shared<SceneObjectGripperChangeStationSlot>(id + "4", std::make_shared<GripperPneumaticDouble>("GripperSingle")),
                    std::make_shared<SceneObjectGripperChangeStationSlot>(id + "5", nullptr) 
                };

                if (gripperSlots_.at(0) != nullptr) gripperSlots_.at(0)->GetTransform()->GetPoseRelative()->SetPositionX(-1);
                if (gripperSlots_.at(1) != nullptr) gripperSlots_.at(1)->GetTransform()->GetPoseRelative()->SetPositionX(-0.5);
                if (gripperSlots_.at(2) != nullptr) gripperSlots_.at(2)->GetTransform()->GetPoseRelative()->SetPositionX(0);
                if (gripperSlots_.at(3) != nullptr) gripperSlots_.at(3)->GetTransform()->GetPoseRelative()->SetPositionX(0.5);
                if (gripperSlots_.at(4) != nullptr) gripperSlots_.at(4)->GetTransform()->GetPoseRelative()->SetPositionX(1);
            }

            void InitializeTransform(std::shared_ptr<Transform> parent) override 
            {
                SceneObject::InitializeTransform(parent);

                for (auto&& slot: gripperSlots_)
                {
                    auto test = GetTransform();
                    //SceneObject::InitializeTransform(test);
                    
                    slot->InitializeTransform(test);
                    //slot->InitializeTransform(test);
                }
            }

            SceneObjectType GetObjectType() const override { return SceneObjectType::EquipmentChangeStation; }

            void PlaceGripper(const std::shared_ptr<GripperBase> gripper, const int slotIndex)
            {
                gripperSlots_.at(slotIndex)->PlaceGripper(gripper);
            } 

            std::shared_ptr<GripperBase> PickGripper(int index)
            {
                return gripperSlots_.at(index)->PickGripper();
            }

    };

    class SceneObjectVisualScanTower : public SceneObject
    {
        public:
            SceneObjectVisualScanTower(std::string id) 
                : SceneObject(id)
                {
                }

            SceneObjectType GetObjectType() const override { return SceneObjectType::VisualScanTower; }
    };

} // namespace WzlPlanner

#endif // TASK_HPP