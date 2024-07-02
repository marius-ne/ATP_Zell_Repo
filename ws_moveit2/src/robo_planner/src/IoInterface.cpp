#include "../include/IoInterface.h"

#include <chrono>
#include "IoInterface.h"


bool WzlPlanner::IoInterfaceOpcUa::SetValueBool(const int slot, const bool value)
{
    auto valueInt = 0;
    if (value) valueInt = 1;

    auto request = std::make_shared<wzlscheduler_interfaces::srv::SetValueIoInterface::Request>();
    request->slotindex = slot;
    request->value = valueInt;

    while (!client_->wait_for_service(1s)) 
    {
        if (!rclcpp::ok()) 
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = client_->async_send_request(request);

    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node_, result) == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Result: %d", result.get()->result);
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service set_value_io_interface");
    }

    return result.get()->result;
}

void WzlPlanner::IoInterfaceOpcUa::OpcaUaActuatorWrite(const std::shared_ptr<const OpcUaData> data) const
{
    std::cout << "Publish Opcua data: " << "Actuator Id: " << data->actuatorId << ", msg type: " << std::to_string(data->actuatorWriteType) << std::endl;

    auto message = opcua_interfaces::msg::ActuatorWrite();
    message.actuator_id = data->actuatorId;
    message.actuator_write_type  = data->actuatorWriteType;
    

    if (data->actuatorWriteType == 1)
    {
        message.actuator_command_bool1 = data->actuatorCommandBool1;
    }
    else if (data->actuatorWriteType == 2)
    {
        message.actuator_command_bool1 = data->actuatorCommandBool1;
        message.actuator_command_bool2 = data->actuatorCommandBool2;
    }
    
    opcua_actuator_write_publisher_->publish(message);
}

bool WzlPlanner::IoInterfaceDummy::SetValueBool(const int slot, const bool value)
{
    // silence 'variable unused' warning
    (void)slot;
    (void)value;

    return true;
}