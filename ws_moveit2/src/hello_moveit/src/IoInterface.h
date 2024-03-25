#ifndef IOINTERFACE_HPP
#define IOINTERFACE_HPP

#include "rclcpp/rclcpp.hpp"
#include "wzlscheduler_interfaces/srv/set_value_io_interface.hpp"
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

namespace WzlPlanner
{
    class IoInterfaceBase
    {
        protected:            

        public:
            virtual bool SetValueBool(int slot, bool value) = 0;
    };

    class IoInterfaceOpcUa : public IoInterfaceBase
    {
        public:
            IoInterfaceOpcUa(const std::shared_ptr<rclcpp::Node> node)
            {
                node_ = node;

                client_ = node_->create_client<wzlscheduler_interfaces::srv::SetValueIoInterface>("set_value_opcua");
            }

            bool SetValueBool(int slot, bool value) override;

        private:
            std::shared_ptr<rclcpp::Node> node_;
            rclcpp::Client<wzlscheduler_interfaces::srv::SetValueIoInterface>::SharedPtr client_;
    };
} // namepspace

#endif