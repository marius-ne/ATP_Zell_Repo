#ifndef TASKMODBUSREQUEST_HPP
#define TASKMODBUSREQUEST_HPP

#include <memory>

#include "../Task.h"
#include "rclcpp/rclcpp.hpp"
#include "../../ObjectContainer.h"
#include "../../ModBusData.h"

#include "modbus_interfaces/srv/write_register.hpp"
#include "modbus_interfaces/srv/read_register.hpp"


namespace WzlPlanner
{
    // Write operation class
    class TaskModBusWrite : public Task 
    {
    private:
        std::shared_ptr<WzlPlanner::IoInterfaceModBus> interface_modbus_;
        std::shared_ptr<ModBusData> data_;
        int value_ = data_->value; // The default value is the one from ModBusData, but can be overridden by SetValue()

    public:
        TaskModBusWrite(const std::shared_ptr<ModBusData> data)
        {
            data_ = data;
            interface_modbus_ = std::dynamic_pointer_cast<WzlPlanner::IoInterfaceModBus>
                (ObjectContainer::Get()->GetioInterface());
        }

        void SetValue(int value) { value_ = value; } // use this to override the default "value_" from ModBusData

        bool Execute() override
        {
            LogStart();
            bool success = interface_modbus_->ModBusWrite(data_, value_);
            LogEnd();
            return success;
        }
    };

    // Read operation class
    class TaskModBusRead : public Task
    {
    private:
        std::shared_ptr<WzlPlanner::IoInterfaceModBus> interface_modbus_;
        std::shared_ptr<ModBusData> data_;
        int result_;

    public:
        TaskModBusRead(const std::shared_ptr<ModBusData> data)
        {
            data_ = data;
            interface_modbus_ = std::dynamic_pointer_cast<WzlPlanner::IoInterfaceModBus>
                (ObjectContainer::Get()->GetioInterface());
        }

        const int& GetResult() const { return result_; } // So that other tasks can access the result of the request
        std::shared_ptr<ModBusData> GetData() const { return data_; } // So that other tasks can access the data which was used for the request

        bool Execute() override
        {
            LogStart();

            result_ = interface_modbus_->ModBusRead(data_);
            
            LogEnd();
            return true;
        }
    };
}

#endif