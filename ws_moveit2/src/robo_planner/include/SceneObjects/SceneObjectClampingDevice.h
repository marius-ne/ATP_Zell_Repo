#ifndef SCENEOBJECTCLAMPINGDEVICEBASE_HPP
#define SCENEOBJECTCLAMPINGDEVICEBASE_HPP 

#include "SceneObject.h"
#include "SceneObjectType.h"

namespace WzlPlanner
{    
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
}

#endif