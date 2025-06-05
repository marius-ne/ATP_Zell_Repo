#ifndef IOINTERFACE_HPP
#define IOINTERFACE_HPP

#include "OpcUaData.h"
#include "ModBusData.h"
#include "rclcpp/rclcpp.hpp"
#include "wzlscheduler_interfaces/srv/set_value_io_interface.hpp"
#include "opcua_interfaces/msg/actuator_write.hpp"
#include "modbus_interfaces/srv/write_register.hpp"
#include "modbus_interfaces/srv/read_register.hpp"
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

namespace WzlPlanner
{
    class IoInterfaceBase
    {
        protected:            

        public:
            virtual bool SetValueBool(const int slot, const bool value) = 0;
    };

    // io interface for testing purpose
    class IoInterfaceDummy 
        : public IoInterfaceBase
    {
        bool SetValueBool(const int slot, const bool value) override;
    };

    class IoInterfaceOpcUa 
        : public IoInterfaceBase
    {
        public:
            IoInterfaceOpcUa(const std::shared_ptr<rclcpp::Node> node)
            {
                node_ = node;

                client_ = node_->create_client<wzlscheduler_interfaces::srv::SetValueIoInterface>("set_value_opcua");
                opcua_actuator_write_publisher_ = node->create_publisher<opcua_interfaces::msg::ActuatorWrite>("Actuator_Write", 10);
            }

            bool SetValueBool(const int slot, const bool value) override;

            void OpcaUaActuatorWrite(const std::shared_ptr<const OpcUaData> data) const;

        private:
            std::shared_ptr<rclcpp::Node> node_;
            rclcpp::Publisher<opcua_interfaces::msg::ActuatorWrite>::SharedPtr opcua_actuator_write_publisher_;
            rclcpp::Client<wzlscheduler_interfaces::srv::SetValueIoInterface>::SharedPtr client_;
    };

    class IoInterfaceModBus 
        : public IoInterfaceBase
    {
        public:
            IoInterfaceModBus(const std::shared_ptr<rclcpp::Node> node)
            {
                node_ = node;

                read_register_client_modbus = node_->create_client<modbus_interfaces::srv::ReadRegister>("read_register_service");
                write_register_client_modbus = node_->create_client<modbus_interfaces::srv::WriteRegister>("write_register_service");
            }

            bool ModBusWrite(const std::shared_ptr<const ModBusData> data, const int value);
            int ModBusRead(const std::shared_ptr<const ModBusData> data);

            // Implement the required method from the base class
            bool SetValueBool(const int slot, const bool value) override {
                // You might want to implement this using ModBusWrite
                (void)slot;
                (void)value;
                return true;
            }

        private:
            std::shared_ptr<rclcpp::Node> node_;
            rclcpp::Client<modbus_interfaces::srv::ReadRegister>::SharedPtr read_register_client_modbus;
            rclcpp::Client<modbus_interfaces::srv::WriteRegister>::SharedPtr write_register_client_modbus;
    };
} // namespace

#endif