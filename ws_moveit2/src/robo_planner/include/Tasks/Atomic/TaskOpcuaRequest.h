#ifndef TASKOPCUAREQUEST_HPP
#define TASKOPCUAREQUEST_HPP

#include <memory>

#include "../Task.h"
#include "rclcpp/rclcpp.hpp"
#include "../../ObjectContainer.h"
#include "../../OpcUaData.h"

#include "opcua_interfaces/msg/actuator_write.hpp"


namespace WzlPlanner
{

    class TaskOpcuaRequest : public Task
    {
        
        private:
            std::shared_ptr<WzlPlanner::IoInterfaceOpcUa> interface_opcua_;
            std::shared_ptr<OpcUaData> data_;

        public:
        
            TaskOpcuaRequest(const std::shared_ptr<OpcUaData> data)
            {
                data_ = data;

                interface_opcua_ = std::dynamic_pointer_cast<WzlPlanner::IoInterfaceOpcUa>
                    (ObjectContainer::Get()->GetioInterface());
            }

            bool Execute() override
            {
                LogStart();
                std::cout << "opcua call" << std::endl;
                interface_opcua_->OpcaUaActuatorWrite(data_);

                LogEnd();

                return true;
            }
        
    };

    
}

#endif