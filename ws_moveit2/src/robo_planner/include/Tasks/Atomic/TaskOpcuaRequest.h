#ifndef TASKOPCUAREQUEST_HPP
#define TASKOPCUAREQUEST_HPP

#include <memory>
#include <std_msgs/msg/bool.hpp>

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
            // true = offen, false = zu 
            inline static rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr gripper_state_pub_;

        public:
            // Frühe Initialisierung (aus main aufrufen)
            static void InitializeGripperStatePublisher(const rclcpp::Node::SharedPtr& node)
            {
                if (!gripper_state_pub_)
                {
                    auto qos = rclcpp::QoS(rclcpp::KeepLast(1)).reliable().transient_local();
                    gripper_state_pub_ = node->create_publisher<std_msgs::msg::Bool>("gripper/state", qos);
                    RCLCPP_INFO(node->get_logger(), "[GRIPPER] State-Publisher initialisiert (transient_local)");
                }
            }

            //Initial-Status setzen (z.B. unbekannt = false oder letzter bekannter)
            static void PublishInitial(bool open_state)
            {
                //gripper zur zeit über bemi2 aufgerufen
                if (gripper_state_pub_) {
                    std_msgs::msg::Bool init;
                    init.data = open_state;
                    gripper_state_pub_->publish(init);
                }
            }
            
            TaskOpcuaRequest(const std::shared_ptr<OpcUaData>& data)
            {
                data_ = data;
                interface_opcua_ = std::dynamic_pointer_cast<WzlPlanner::IoInterfaceOpcUa>
                    (ObjectContainer::Get()->GetioInterface());

                if (!gripper_state_pub_) {
                    auto node = WzlPlanner::ObjectContainer::Get()->GetNode(); 
                    if (node) {
                        auto qos = rclcpp::QoS(rclcpp::KeepLast(1)).reliable().transient_local();
                        gripper_state_pub_ = node->create_publisher<std_msgs::msg::Bool>("gripper/state", qos);
                        RCLCPP_WARN(node->get_logger(),
                            "[GRIPPER] Publisher spät (Fallback) erstellt.");
                    }
                }
                    
            }

            bool Execute() override
            {
                LogStart();

                if (!interface_opcua_) {
                    auto node = WzlPlanner::ObjectContainer::Get()->GetNode();
                    if (node)
                        RCLCPP_ERROR(node->get_logger(), "[GRIPPER] interface_opcua_ null");
                    LogEnd();
                    return false;
                }

                interface_opcua_->OpcaUaActuatorWrite(data_);

                if (gripper_state_pub_
                    && data_
                    && data_->actuatorId == "ns=4;i=5007"
                    && data_->actuatorWriteType == 1)
                {
                    // OPC UA: actuatorCommandBool1 = true -> ZU, false -> OFFEN 
                    std_msgs::msg::Bool state_msg;
                    state_msg.data = data_->actuatorCommandBool1;  // Topic true = OFFEN, false = ZU
                    gripper_state_pub_->publish(state_msg);

                    auto node = WzlPlanner::ObjectContainer::Get()->GetNode();
                    if (node) {
                        RCLCPP_INFO(
                            node->get_logger(),
                            "[GRIPPER] Zustand publiziert: %s",
                            state_msg.data ? "OFFEN(true)" : "ZU(false)");
                    }
                }

                LogEnd();
                return true;
            }
    };
}

#endif