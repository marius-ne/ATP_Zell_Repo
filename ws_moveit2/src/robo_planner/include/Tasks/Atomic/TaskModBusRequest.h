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

    class TaskModBusRequest : public Task
    {
        
        private:
            std::shared_ptr<WzlPlanner::IoInterfaceModBus> interface_modbus_;
            std::shared_ptr<ModBusData> data_;

        public:
        
            TaskModBusRequest(const std::shared_ptr<ModBusData> data)
            {
                data_ = data;

                interface_modbus_ = std::dynamic_pointer_cast<WzlPlanner::IoInterfaceModBus>
                    (ObjectContainer::Get()->GetioInterface());
            }

            bool Execute() override
            {
                LogStart();
                std::cout << "modbus call" << std::endl;
                interface_modbus_->ModBusWrite(data_);

                LogEnd();

                return true;
            }
        
    };

    
}

#endif