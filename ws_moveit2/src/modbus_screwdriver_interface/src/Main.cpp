#include <rclcpp/rclcpp.hpp>
#include <modbus_interfaces/srv/read_register.hpp>
#include <modbus_interfaces/srv/write_register.hpp>
#include <modbus_interfaces/srv/tighten_screw.hpp>
#include <modbus_interfaces/srv/loosen_screw.hpp>
#include <modbus_interfaces/srv/pickup_screw.hpp>
#include "../include/modbus_screwdriver_interface/ModBusData.h"
#include <chrono>
#include <memory>

using namespace std::chrono_literals;

class ModbusScrewdriverInterface : public rclcpp::Node
{
public:
    ModbusScrewdriverInterface() : Node("modbus_screwdriver_interface")
    {
        RCLCPP_INFO(this->get_logger(), "Modbus Screwdriver Interface node started");

        // Create a reentrant callback group for services
        callback_group_ = this->create_callback_group(rclcpp::CallbackGroupType::Reentrant);

        einschrauben_service_ = this->create_service<modbus_interfaces::srv::TightenScrew>("einschrauben",
            std::bind(&ModbusScrewdriverInterface::schraube_einschrauben, this, std::placeholders::_1, std::placeholders::_2),
            rmw_qos_profile_services_default, callback_group_);
        
        ausschrauben_service_ = this->create_service<modbus_interfaces::srv::LoosenScrew>("ausschrauben",
            std::bind(&ModbusScrewdriverInterface::schraube_ausschrauben, this, std::placeholders::_1, std::placeholders::_2),
            rmw_qos_profile_services_default, callback_group_);

        schraube_laden_service_ = this->create_service<modbus_interfaces::srv::PickupScrew>("schraube_laden",
            std::bind(&ModbusScrewdriverInterface::schraube_laden, this, std::placeholders::_1, std::placeholders::_2),
            rmw_qos_profile_services_default, callback_group_);

        // Create clients for the modbus services
        read_client_ = this->create_client<modbus_interfaces::srv::ReadRegister>("read_register_service", 
            rmw_qos_profile_services_default, callback_group_);
        write_client_ = this->create_client<modbus_interfaces::srv::WriteRegister>("write_register_service",
            rmw_qos_profile_services_default, callback_group_);
        
        // Wait for services to be available
        wait_for_services();
        
        RCLCPP_INFO(this->get_logger(), "Ready to communicate with modbus services");
    }

private:
    void schraube_einschrauben(
        const std::shared_ptr<modbus_interfaces::srv::TightenScrew::Request> request,
        std::shared_ptr<modbus_interfaces::srv::TightenScrew::Response> response)
    {
        RCLCPP_INFO(this->get_logger(), "Einschrauben service called");
        
        auto screw_length = request->screw_length;
        auto target_torque = request->torque;
        auto z_force = request->z_force;

        try {
            auto modbus_request = std::make_shared<modbus_interfaces::srv::WriteRegister::Request>();

            // Set screw length
            auto screw_length_data = WzlPlanner::ModBusData::GetModBusData_ScrewLength_Write();
            modbus_request->address = screw_length_data->address;
            modbus_request->value = screw_length;

            auto result = write_client_->async_send_request(modbus_request);
            if (result.wait_for(std::chrono::seconds(5)) != std::future_status::ready) {
                response->success = false;
                response->message = "Failed to write screw length - timeout";
                return;
            }
            auto screw_length_response = result.get();
            if (!screw_length_response->success) {
                response->success = false;
                response->message = "Failed to write screw length: " + screw_length_response->message;
                return;
            }

            // Set target torque
            auto torque_data = WzlPlanner::ModBusData::GetModBusData_TargetTorque_Write();
            modbus_request->address = torque_data->address;
            modbus_request->value = target_torque;
            
            result = write_client_->async_send_request(modbus_request);
            if (result.wait_for(std::chrono::seconds(5)) != std::future_status::ready) {
                response->success = false;
                response->message = "Failed to write target torque - timeout";
                return;
            }
            auto torque_response = result.get();
            if (!torque_response->success) {
                response->success = false;
                response->message = "Failed to write target torque: " + torque_response->message;
                return;
            }

            // Set Z axis force
            auto z_force_data = WzlPlanner::ModBusData::GetModBusData_ZAxesForce_Write();
            modbus_request->address = z_force_data->address;
            modbus_request->value = z_force;
            
            result = write_client_->async_send_request(modbus_request);
            if (result.wait_for(std::chrono::seconds(5)) != std::future_status::ready) {
                response->success = false;
                response->message = "Failed to write Z force - timeout";
                return;
            }
            auto z_force_response = result.get();
            if (!z_force_response->success) {
                response->success = false;
                response->message = "Failed to write Z force: " + z_force_response->message;
                return;
            }

            // Send command to tighten screw
            auto tighten_data = WzlPlanner::ModBusData::GetModBusData_TightenScrew_Write();
            modbus_request->address = tighten_data->address;
            modbus_request->value = tighten_data->value;
            
            result = write_client_->async_send_request(modbus_request);
            if (result.wait_for(std::chrono::seconds(5)) != std::future_status::ready) {
                response->success = false;
                response->message = "Failed to send tighten command - timeout";
                return;
            }
            auto tighten_response = result.get();
            if (!tighten_response->success) {
                response->success = false;
                response->message = "Failed to send tighten command: " + tighten_response->message;
                return;
            }

            RCLCPP_INFO(this->get_logger(), "Tighten screw command sent successfully");
            response->success = true;
            response->message = "Screw tightening completed";
        }
        catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception in schraube_einschrauben: %s", e.what());
            response->success = false;
            response->message = std::string("Exception: ") + e.what();
        }
    }

    void schraube_ausschrauben(
        const std::shared_ptr<modbus_interfaces::srv::LoosenScrew::Request> request,
        std::shared_ptr<modbus_interfaces::srv::LoosenScrew::Response> response)
    {
        RCLCPP_INFO(this->get_logger(), "Ausschrauben service called");

        auto screw_length = request->screw_length;
        auto z_force = request->z_force;

        try {
            auto modbus_request = std::make_shared<modbus_interfaces::srv::WriteRegister::Request>();

            // Set screw length
            auto screw_length_data = WzlPlanner::ModBusData::GetModBusData_ScrewLength_Write();
            modbus_request->address = screw_length_data->address;
            modbus_request->value = screw_length;
            
            auto result = write_client_->async_send_request(modbus_request);
            if (result.wait_for(std::chrono::seconds(5)) != std::future_status::ready) {
                response->success = false;
                response->message = "Failed to write screw length - timeout";
                return;
            }
            auto screw_length_response = result.get();
            if (!screw_length_response->success) {
                response->success = false;
                response->message = "Failed to write screw length: " + screw_length_response->message;
                return;
            }

            // Set Z axis force
            auto z_force_data = WzlPlanner::ModBusData::GetModBusData_ZAxesForce_Write();
            modbus_request->address = z_force_data->address;
            modbus_request->value = z_force;
            
            result = write_client_->async_send_request(modbus_request);
            if (result.wait_for(std::chrono::seconds(5)) != std::future_status::ready) {
                response->success = false;
                response->message = "Failed to write Z force - timeout";
                return;
            }
            auto z_force_response = result.get();
            if (!z_force_response->success) {
                response->success = false;
                response->message = "Failed to write Z force: " + z_force_response->message;
                return;
            }

            // Send command to loosen screw
            auto loosen_data = WzlPlanner::ModBusData::GetModBusData_LoosenScrew_Write();
            modbus_request->address = loosen_data->address;
            modbus_request->value = loosen_data->value;
            
            result = write_client_->async_send_request(modbus_request);
            if (result.wait_for(std::chrono::seconds(5)) != std::future_status::ready) {
                response->success = false;
                response->message = "Failed to send loosen command - timeout";
                return;
            }
            auto loosen_response = result.get();
            if (!loosen_response->success) {
                response->success = false;
                response->message = "Failed to send loosen command: " + loosen_response->message;
                return;
            }

            RCLCPP_INFO(this->get_logger(), "Loosen screw command sent successfully");
            response->success = true;
            response->message = "Screw loosening completed";

        }
        catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception in schraube_ausschrauben: %s", e.what());
            response->success = false;
            response->message = std::string("Exception: ") + e.what();
        }
    }

    void schraube_laden(
        const std::shared_ptr<modbus_interfaces::srv::PickupScrew::Request> request,
        std::shared_ptr<modbus_interfaces::srv::PickupScrew::Response> response)
    {
        RCLCPP_INFO(this->get_logger(), "Schraube laden service called");

        auto screw_length = request->screw_length;
        auto z_force = request->z_force;

        try {
            auto modbus_request = std::make_shared<modbus_interfaces::srv::WriteRegister::Request>();

            // Set screw length
            auto screw_length_data = WzlPlanner::ModBusData::GetModBusData_ScrewLength_Write();
            modbus_request->address = screw_length_data->address;
            modbus_request->value = screw_length;

            auto result = write_client_->async_send_request(modbus_request);
            if (result.wait_for(std::chrono::seconds(5)) != std::future_status::ready) {
                response->success = false;
                response->message = "Failed to write screw length - timeout";
                return;
            }
            auto screw_length_response = result.get();
            if (!screw_length_response->success) {
                response->success = false;
                response->message = "Failed to write screw length: " + screw_length_response->message;
                return;
            }

            // Set Z axis force
            auto z_force_data = WzlPlanner::ModBusData::GetModBusData_ZAxesForce_Write();
            modbus_request->address = z_force_data->address;
            modbus_request->value = z_force;
            
            result = write_client_->async_send_request(modbus_request);
            if (result.wait_for(std::chrono::seconds(5)) != std::future_status::ready) {
                response->success = false;
                response->message = "Failed to write Z force - timeout";
                return;
            }
            auto z_force_response = result.get();
            if (!z_force_response->success) {
                response->success = false;
                response->message = "Failed to write Z force: " + z_force_response->message;
                return;
            }

            // Send command to pickup screw
            auto pickup_data = WzlPlanner::ModBusData::GetModBusData_PickUpScrew_Write();
            modbus_request->address = pickup_data->address;
            modbus_request->value = pickup_data->value;
            
            result = write_client_->async_send_request(modbus_request);
            if (result.wait_for(std::chrono::seconds(5)) != std::future_status::ready) {
                response->success = false;
                response->message = "Failed to send pickup command - timeout";
                return;
            }
            auto pickup_response = result.get();
            if (!pickup_response->success) {
                response->success = false;
                response->message = "Failed to send pickup command: " + pickup_response->message;
                return;
            }

            RCLCPP_INFO(this->get_logger(), "Pickup screw command sent successfully");
            response->success = true;
            response->message = "Screw pickup completed";

        }
        catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception in schraube_laden: %s", e.what());
            response->success = false;
            response->message = std::string("Exception: ") + e.what();
        }
    }

    void wait_for_services()
    {
        RCLCPP_INFO(this->get_logger(), "Waiting for modbus services...");
        
        while (!read_client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for modbus read service");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Modbus read service not available, waiting...");
        }
        
        while (!write_client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for modbus write service");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Modbus write service not available, waiting...");
        }
        
        RCLCPP_INFO(this->get_logger(), "Both modbus services are available!");
    }

    // Callback group for reentrant callbacks
    rclcpp::CallbackGroup::SharedPtr callback_group_;
    
    // Service clients
    rclcpp::Client<modbus_interfaces::srv::ReadRegister>::SharedPtr read_client_;
    rclcpp::Client<modbus_interfaces::srv::WriteRegister>::SharedPtr write_client_;
    
    // Service servers
    rclcpp::Service<modbus_interfaces::srv::TightenScrew>::SharedPtr einschrauben_service_;
    rclcpp::Service<modbus_interfaces::srv::LoosenScrew>::SharedPtr ausschrauben_service_;
    rclcpp::Service<modbus_interfaces::srv::PickupScrew>::SharedPtr schraube_laden_service_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    
    auto node = std::make_shared<ModbusScrewdriverInterface>();
    
    // Use MultiThreadedExecutor to allow concurrent callback execution
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    executor.spin();
    
    rclcpp::shutdown();
    return 0;
}