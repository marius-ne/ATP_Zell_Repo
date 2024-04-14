#include "../../include/SceneObjects/SceneObjectClampingDevice.h"
#include "../../include/ObjectContainer.h"

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

void OpenWaitCloseClampingDevice(const int ioSlotIndex, const std::chrono::milliseconds time)
{
    WzlPlanner::ObjectContainer::Get()->GetioInterface()->SetValueBool(ioSlotIndex, true); 

    // wait 1 sec
    std::this_thread::sleep_for(time);

    WzlPlanner::ObjectContainer::Get()->GetioInterface()->SetValueBool(ioSlotIndex, false);
}

void WzlPlanner::SceneObjectClampingDeviceJaws::Open()
{
    OpenWaitCloseClampingDevice(this->ioOpen_, 1000ms);
}

void WzlPlanner::SceneObjectClampingDeviceJaws::Close()
{
    OpenWaitCloseClampingDevice(this->ioClose_, 1000ms);
}

void WzlPlanner::SceneObjectClampingDeviceElevation::Open()
{
    OpenWaitCloseClampingDevice(this->ioOpen_, 1000ms);
}

void WzlPlanner::SceneObjectClampingDeviceElevation::Close()
{
    OpenWaitCloseClampingDevice(this->ioClose_, 1000ms);
}
