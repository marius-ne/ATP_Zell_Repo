#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"



using std::placeholders::_1;

class PlaneRemover : public rclcpp::Node
{
  public:
    PlaneRemover()
    : Node("plane_remover")
    {
        subscriber_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "tof_point_cloud", 10, std::bind(&PlaneRemover::topic_callback, this, _1));

        using namespace std::chrono_literals;
        publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/tof_point_cloud_filtered_plane", 10);
    }

  private:
    void topic_callback(const sensor_msgs::msg::PointCloud2 & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "Received pointcloud");

      
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscriber_;
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PlaneRemover>());
  rclcpp::shutdown();
  return 0;
}