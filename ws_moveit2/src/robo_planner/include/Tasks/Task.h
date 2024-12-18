#ifndef TASK_HPP
#define TASK_HPP

#include <vector>
#include <memory>
#include <string>
#include "../../include/ObjectContainer.h"
#include "std_msgs/msg/string.hpp"

namespace WzlPlanner
{
    class Task
    {

        public:
            Task();

            static void InitializePublisher(rclcpp::Node::SharedPtr node) {
                task_status_pub_ = node->create_publisher<std_msgs::msg::String>("/task_status", 10);
            }

            virtual bool Execute() 
            { 
                LogStart();

                for (auto &&subtask: subTasks_)
                {
                    if (!subtask->Execute())
                    {
                        Log("Subtask execution failed of: " + std::string(subtask->id_));
                        
                        // Publish failure to topic
                        if (task_status_pub_) {
                            auto msg = std_msgs::msg::String();
                            msg.data = "Subtask execution failed of: " + std::string(subtask->id_);
                            task_status_pub_->publish(msg);
                        }
                        
                        return false;
                    }
                }

                LogEnd();

                return true;
            };

            virtual void SetId(const std::string id) { id_ = id; }
            std::string GetId() { return id_; }

        protected:
            std::vector<std::shared_ptr<Task>> subTasks_;

            void LogStart()
            {
                auto node = ObjectContainer::Get()->GetNode();
                RCLCPP_INFO(node->get_logger(), (std::string("Start task: ") + id_).c_str());
            
                if (task_status_pub_) {
                    auto msg = std_msgs::msg::String();
                    msg.data = "Start task: " + id_;
                    task_status_pub_->publish(msg);
                }
            
            }

            void LogEnd()
            {
                auto node = ObjectContainer::Get()->GetNode();
                RCLCPP_INFO(node->get_logger(), (std::string("End task: ") + id_).c_str());
            
                if (task_status_pub_) {
                    auto msg = std_msgs::msg::String();
                    msg.data = "End task: " + id_;
                    task_status_pub_->publish(msg);
                }
            
            }

            void Log(const std::string& msg)
            {
                auto node = ObjectContainer::Get()->GetNode();
                RCLCPP_INFO(node->get_logger(), msg.c_str());
            }

        private:
            std::string id_;
            static rclcpp::Publisher<std_msgs::msg::String>::SharedPtr task_status_pub_;

    };

} // namespace WzlPlanner

#endif // TASK_HPP