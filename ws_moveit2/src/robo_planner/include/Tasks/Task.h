#ifndef TASK_HPP
#define TASK_HPP

#include <vector>
#include <memory>
#include <string>
#include "../../include/ObjectContainer.h"

namespace WzlPlanner
{
    class Task
    {

        public:
            Task();

            virtual bool Execute() 
            { 
                LogStart();

                for (auto &&subtask: subTasks_)
                {
                    if (!subtask->Execute())
                    {
                        Log("Subtask execution failed of: " + std::string(subtask->id_));
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
            }

            void LogEnd()
            {
                auto node = ObjectContainer::Get()->GetNode();
                RCLCPP_INFO(node->get_logger(), (std::string("End task: ") + id_).c_str());
            }

            void Log(const std::string& msg)
            {
                auto node = ObjectContainer::Get()->GetNode();
                RCLCPP_INFO(node->get_logger(), msg.c_str());
            }

        private:
            std::string id_;
    };

} // namespace WzlPlanner

#endif // TASK_HPP