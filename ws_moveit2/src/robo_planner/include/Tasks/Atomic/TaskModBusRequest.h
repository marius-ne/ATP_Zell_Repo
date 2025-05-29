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
        int value_ = 0;

    public:
        TaskModBusWrite(const std::shared_ptr<ModBusData> data)
        {
            data_ = data;
            interface_modbus_ = std::dynamic_pointer_cast<WzlPlanner::IoInterfaceModBus>
                (ObjectContainer::Get()->GetioInterface());
        }
        
        TaskModBusWrite(const std::shared_ptr<ModBusData> data, int value)
            : value_(value)
        {
            data_ = data;
            interface_modbus_ = std::dynamic_pointer_cast<WzlPlanner::IoInterfaceModBus>
                (ObjectContainer::Get()->GetioInterface());
        }

        void SetValue(int value) { value_ = value; }

        bool Execute() override
        {
            LogStart();
            std::cout << "modbus write to address " << data_->address << " value " << value_ << std::endl;
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
        std::vector<int> result_;
        int count_ = 1;

    public:
        TaskModBusRead(const std::shared_ptr<ModBusData> data)
        {
            data_ = data;
            interface_modbus_ = std::dynamic_pointer_cast<WzlPlanner::IoInterfaceModBus>
                (ObjectContainer::Get()->GetioInterface());
        }

        TaskModBusRead(const std::shared_ptr<ModBusData> data, int count)
            : count_(count)
        {
            data_ = data;
            interface_modbus_ = std::dynamic_pointer_cast<WzlPlanner::IoInterfaceModBus>
                (ObjectContainer::Get()->GetioInterface());
        }

        const std::vector<int>& GetResult() const { return result_; }

        bool Execute() override
        {
            LogStart();
            std::cout << "modbus read from address " << data_->address << std::endl;
            result_ = interface_modbus_->ModBusRead(data_);
            bool success = !result_.empty();
            LogEnd();
            return success;
        }
    };
}

#endif