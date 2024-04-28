#ifndef GRIPPER_HPP
#define GRIPPER_HPP


#include "ArenaApi.h"

#include <sensor_msgs/msg/point_cloud2.hpp>

class PointCloudConverter
{

    public:
        std::make_shared<sensor_msgs::msg::PointCloud2> Convert(Arena::IImage* img);
};

#endif