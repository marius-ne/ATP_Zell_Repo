#include "../../include/Tasks/Task.h"

rclcpp::Publisher<std_msgs::msg::String>::SharedPtr WzlPlanner::Task::task_status_pub_ = nullptr;

WzlPlanner::Task::Task()
{
    this->id_ = std::string("Unnamed");
}
