#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <iostream>
#include <chrono>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>

#include <pcl_conversions/pcl_conversions.h>

using std::placeholders::_1;

class Matching : public rclcpp::Node
{
  public:
    Matching(const std::string file_path)
    : Node("file_publisher")
    {
        RCLCPP_INFO(this->get_logger(), "Start file publisher");

        load_from_file(file_path);

        using namespace std::chrono_literals;
        publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/tof_point_cloud", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&Matching::publish_callback, this));
    }

  private:
    void load_from_file(const std::string file_path)
    {
      // Load ply from file
      cloud_ = std::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
      pcl::PLYReader reader;
      reader.read(file_path, *cloud_);      

      // convert to sensor msg
      sensor_msg_ = std::make_shared<sensor_msgs::msg::PointCloud2>();
      pcl::toROSMsg(*cloud_, *sensor_msg_.get());               
    }

    void publish_callback() const
    {
      // publish point cloud
      sensor_msg_->header.frame_id = "map";
      sensor_msg_->header.stamp = now();
      publisher_->publish(*sensor_msg_.get());     
    }

    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_;
    sensor_msgs::msg::PointCloud2::Ptr sensor_msg_;
};

int main(int argc, char * argv[])
{
  if (argc >= 2)
  {
    std::cout << "Pointcloud file path: " << argv[1] << std::endl;
  }
  else
  {
    std::cout << "Needs to specify a file path as argument" << std::endl;
    return 0;
  }

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Matching>(argv[1]));
  rclcpp::shutdown();
  return 0;
}