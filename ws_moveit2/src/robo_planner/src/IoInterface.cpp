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

bool WzlPlanner::IoInterfaceModBus::ModBusWrite(const std::shared_ptr<const ModBusData> data, const int value) {
    RCLCPP_DEBUG(rclcpp::get_logger("rclcpp"), "ModBus Write: Address: %d, Value: %d", data->address, value);

    auto request = std::make_shared<modbus_interfaces::srv::WriteRegister::Request>();
    request->address = data->address;
    request->value = value;

    // Wait for service to be available
    while (!write_register_client_modbus->wait_for_service(1s)) 
    {
        if (!rclcpp::ok()) 
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the ModBus write service. Exiting.");
            return false;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ModBus write service not available, waiting again...");
    }

    auto future_result = write_register_client_modbus->async_send_request(request);

    // Wait for the result
    if (rclcpp::spin_until_future_complete(node_, future_result) == rclcpp::FutureReturnCode::SUCCESS)
    {
        auto response = future_result.get();
        auto success = response->success;

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Result of ModBus write: %d", success);
        
        if (!success) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "ModBus write error: %s", response->message.c_str());
        }
        
        return success;
    } 
    else 
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call ModBus write service");
        return false;
    }
}

int WzlPlanner::IoInterfaceModBus::ModBusRead(const std::shared_ptr<const ModBusData> data) {
    RCLCPP_DEBUG(rclcpp::get_logger("rclcpp"), "ModBus Read: Address: %d, Count: %d", data->address, data->count);

    auto request = std::make_shared<modbus_interfaces::srv::ReadRegister::Request>();
    request->address = data->address;
    request->count = data->count;

    // Wait for service to be available
    while (!write_register_client_modbus->wait_for_service(1s)) 
    {
        if (!rclcpp::ok()) 
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the ModBus read service. Exiting.");
            return false;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ModBus read service not available, waiting again...");
    }

    auto future_result = read_register_client_modbus->async_send_request(request);

    // Wait for the result
    if (rclcpp::spin_until_future_complete(node_, future_result) == rclcpp::FutureReturnCode::SUCCESS)
    {

        auto response = future_result.get();
        auto success = response->success;
        auto registers = response->registers;

        if (success) {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Successfully read register from ModBus: %d", registers); 
            return registers;
        }
        else {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "ModBus read error: %s", response->message.c_str());
            return 0;
        }
    } 
    else 
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call ModBus read service");
        return 0;
    }
}

// method is deprecated; use 'OpcaUaActuatorWrite' instead
bool WzlPlanner::IoInterfaceDummy::SetValueBool(const int slot, const bool value)
{
    // silence 'variable unused' warning
    (void)slot;
    (void)value;

    return true;
}