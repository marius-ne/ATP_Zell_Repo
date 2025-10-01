#include <rclcpp/rclcpp.hpp>
#include <modbus_interfaces/srv/read_register.hpp>
#include <modbus_interfaces/srv/write_register.hpp>
#include <chrono>
#include <memory>

using namespace std::chrono_literals;

class ModbusScrewdriverInterface : public rclcpp::Node
{
public:
    ModbusScrewdriverInterface() : Node("modbus_screwdriver_interface")
    {
        RCLCPP_INFO(this->get_logger(), "Modbus Screwdriver Interface node started");

        //TODO DEFINE ALL SERVICES, DEFINE CALLBACK FUNCTIONS, DEFINE THE SERVICE MESSAGES

        einschrauben_service = this->create_service<modbus_interfaces::srv::>("einschrauben",
            std::bind(&ModbusScrewdriverInterface::handle_einschrauben, this, std::placeholders::_1, std::placeholders::_2));
        
        // Create clients for the modbus services
        read_client_ = this->create_client<modbus_interfaces::srv::ReadRegister>("read_register_service");
        write_client_ = this->create_client<modbus_interfaces::srv::WriteRegister>("write_register_service");
        
        // Wait for services to be available
        wait_for_services();
        
        RCLCPP_INFO(this->get_logger(), "Ready to communicate with modbus services");
    }



private:
    void wait_for_services()
    {
        RCLCPP_INFO(this->get_logger(), "Waiting for modbus services...");
        
        while (!read_client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for read service");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Read service not available, waiting...");
        }
        
        while (!write_client_->wait_for_service(1s)) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for write service");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Write service not available, waiting...");
        }
        
        RCLCPP_INFO(this->get_logger(), "Both modbus services are available!");
    }

    // Service clients
    rclcpp::Client<modbus_interfaces::srv::ReadRegister>::SharedPtr read_client_;
    rclcpp::Client<modbus_interfaces::srv::WriteRegister>::SharedPtr write_client_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    
    auto node = std::make_shared<ModbusScrewdriverInterface>();
    

    
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}