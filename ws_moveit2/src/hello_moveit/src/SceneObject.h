#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP

#include <memory>
#include <array>

#include "Pose.h"
#include "Part.h"


namespace WzlPlanner
{
    
    enum SceneObjectType
    {
        ClampingDeviceJaws = 1,
        ClampingDeviceElevation = 2,
        Carrier = 3,
        EquipmentChangeStation = 4,
        VisualScanTower = 5
    };

    class SceneObject
    {
        private:
            std::shared_ptr<WzlPlanner::Pose> pose;

        protected:
            SceneObject() {}

        public:
            std::shared_ptr<WzlPlanner::Pose> GetPose() const { return pose; }
            void SetPose(const std::shared_ptr<WzlPlanner::Pose> pose) { this->pose = pose; }
            virtual SceneObjectType GetObjectType() const = 0;
    };

    class SceneObjectClampingDeviceBase : public SceneObject
    {
        protected:
            SceneObjectClampingDeviceBase() {}

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
            SceneObjectClampingDeviceJaws() {}
            SceneObjectType GetObjectType() const override { return SceneObjectType::ClampingDeviceJaws; }

            void Open() override;
            void Close() override;
    };

    class SceneObjectClampingDeviceElevation : public SceneObjectClampingDeviceBase
    {
        public:
            SceneObjectType GetObjectType() const override { return SceneObjectType::ClampingDeviceElevation; }

            void Open() override;
            void Close() override;
    };

    class SceneObjectCarrierSlot
    {
        private:
            float localPosX, localPosY;
            std::shared_ptr<Pose> poseScene;

        public:
            SceneObjectCarrierSlot(float localPosX, float localPosY)
            {
                this->localPosX = localPosX;
                this->localPosY = localPosY;
            }

            void UpdatePoseScene();
    };

    class SceneObjectCarrier : public SceneObject
    {
        private:
            std::unique_ptr<std::shared_ptr<PartBase>[]> parts;
            

        public:
            SceneObjectType GetObjectType() const override { return SceneObjectType::Carrier; }

            SceneObjectCarrier()
            {
                int countX = 5;
                int countY = 4;
                int totalCount = countX * countY;

                parts = std::make_unique<std::shared_ptr<PartBase>[]>(totalCount);
            }
    };

    class SceneObjectEquipmentChangeStation : public SceneObject
    {
        private:

        public:
            SceneObjectType GetObjectType() const override { return SceneObjectType::EquipmentChangeStation; }
    };

    class SceneObjectVisualScanTower : public SceneObject
    {
        public:
            SceneObjectType GetObjectType() const override { return SceneObjectType::VisualScanTower; }
    };

} // namespace WzlPlanner

#endif // TASK_HPP