#ifndef SCENEOBJECTCLAMPINGDEVICEBASE_HPP
#define SCENEOBJECTCLAMPINGDEVICEBASE_HPP 

#include "SceneObject.h"
#include "SceneObjectType.h"

namespace WzlPlanner
{    
    enum ClampingDeviceStateOpen
    {
        IsOpened,
        IsClosed,
        IsOpening,
        IsClosing
    };

    class SceneObjectClampingDeviceBase : public SceneObject
    {
        protected:
            SceneObjectClampingDeviceBase(const std::string id, const int ioOpen, const int ioClose) 
                : SceneObject(id)
            {
                this->ioOpen_ = ioOpen;
                this->ioClose_ = ioClose;
            }

            // Interface for Closing/opening the clamping device
            int ioOpen_, ioClose_;
            ClampingDeviceStateOpen gripperState_;

            void SetOpen(const bool isOpened);

        public:
            virtual void Open() = 0;
            virtual void Close() = 0;

            bool IsOpen() const { return this->gripperState_ == ClampingDeviceStateOpen::IsOpened; }
            bool IsClose() const { return this->gripperState_ == ClampingDeviceStateOpen::IsClosed; }
    };

    class SceneObjectClampingDeviceJaws : public SceneObjectClampingDeviceBase
    {
        public:
            SceneObjectClampingDeviceJaws(const std::string id, const int ioOpen, const int ioClose) 
                : SceneObjectClampingDeviceBase(id, ioOpen, ioClose)
            {
            }

            SceneObjectType GetObjectType() const override { return SceneObjectType::ClampingDeviceJaws; }

            void Open() override;
            void Close() override;
    };

    class SceneObjectClampingDeviceElevation : public SceneObjectClampingDeviceBase
    {
        public:
            SceneObjectClampingDeviceElevation(const std::string id, const int ioOpen, const int ioClose) 
                : SceneObjectClampingDeviceBase(id, ioOpen, ioClose)
            {
            }

            SceneObjectType GetObjectType() const override { return SceneObjectType::ClampingDeviceElevation; }

            void Open() override;
            void Close() override;
    };
}

#endif