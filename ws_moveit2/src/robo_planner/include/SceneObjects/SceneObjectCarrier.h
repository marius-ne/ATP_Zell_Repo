#ifndef SCENEOBJECTCARRIER_HPP
#define SCENEOBJECTCARRIER_HPP 

#include "SceneObject.h"
#include "../Part.h"

#include <memory>

namespace WzlPlanner
{    
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
            
            void InitializeTransform(std::shared_ptr<Transform> parent) override 
            {
                SceneObject::InitializeTransform(parent);

                int counter = 0;
                
                for (auto & slot : slots_) 
                {
                    
                    float currentPosX = firstSlotOriginX_ + (counter % slotsCountX_) * slotGapX_;
                    float currentPosY = firstSlotOriginY_ + (counter / slotsCountY) * slotGapY_;

                    slot->InitializeTransform(this->GetTransform());
                    slot->GetTransform()->GetPoseRelative()->SetPositionXYZ(currentPosX, currentPosY, 0);
                    slot->GeTransformAppraocah()->GetPoseRelative()->SetPositionZ(0.2f);

                    counter++;
                }   
            }
    };

}

#endif