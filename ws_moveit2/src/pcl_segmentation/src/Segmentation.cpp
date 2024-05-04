#include "rclcpp/rclcpp.hpp"
#include "../include/Clustering.h"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Clustering>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}