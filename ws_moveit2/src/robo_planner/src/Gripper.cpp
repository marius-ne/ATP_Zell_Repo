#include "../include/Gripper.h"
#include "../include/ObjectContainer.h"

#include <memory>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

std::shared_ptr<WzlPlanner::IoInterfaceBase> GetIoInterface() 
{
    return WzlPlanner::ObjectContainer::Get()->GetioInterface();
}

void OpenWaitClose(const int ioSlotIndex, const std::chrono::milliseconds time)
{
    GetIoInterface()->SetValueBool(ioSlotIndex, true); 

    // wait 1 sec
    std::this_thread::sleep_for(time);

    GetIoInterface()->SetValueBool(ioSlotIndex, false);
}

void WzlPlanner::GripperPneumaticSingle::Open()
{
    OpenWaitClose(this->ioOpen_, 1000ms);
}

void WzlPlanner::GripperPneumaticSingle::Close()
{
    OpenWaitClose(this->ioClose_, 1000ms);
}

void WzlPlanner::GripperPneumaticDouble::Open()
{
    GetIoInterface()->SetValueBool(this->ioOpen1, true); 
    GetIoInterface()->SetValueBool(this->ioOpen2, true); 

    // wait 1 sec
    std::this_thread::sleep_for(1000ms);

    GetIoInterface()->SetValueBool(this->ioOpen1, false); 
    GetIoInterface()->SetValueBool(this->ioOpen2, false); 
}

void WzlPlanner::GripperPneumaticDouble::Close()
{
    GetIoInterface()->SetValueBool(this->ioClose1, true); 
    GetIoInterface()->SetValueBool(this->ioClose2, true); 

    // wait 1 sec
    std::this_thread::sleep_for(1000ms);

    GetIoInterface()->SetValueBool(this->ioClose1, false); 
    GetIoInterface()->SetValueBool(this->ioClose2, false); 
    
}

void WzlPlanner::GripperCameraToF::Scan()
{
    // todo
    // call camera scripts
}

void WzlPlanner::GripperDeburringSpindle::Open()
{
    // start deburring spindle
    GetIoInterface()->SetValueBool(this->ioRun_, true);
}

void WzlPlanner::GripperDeburringSpindle::Close()
{
    // stop deburring spindle
    GetIoInterface()->SetValueBool(this->ioRun_, false);
}
