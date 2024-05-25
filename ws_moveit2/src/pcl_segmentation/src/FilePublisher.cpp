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

#define PARAM_FILE_PATH "file_path"
#define PARAM_PUBLISHER_NAME "publisher_name"

class FilePublisher : public rclcpp::Node
{
  public:
    FilePublisher(const std::string& file_path, const std::string& publisher_name)
    : Node("file_publisher")
    {
        RCLCPP_INFO(this->get_logger(), "Start file publisher\n");

        this->declare_parameter(PARAM_FILE_PATH, file_path);
        this->declare_parameter(PARAM_PUBLISHER_NAME, publisher_name);

        print_params();
        load_from_file(get_parameter(PARAM_FILE_PATH).as_string());

        using namespace std::chrono_literals;
        publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(this->get_parameter(PARAM_PUBLISHER_NAME).as_string(), 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&FilePublisher::publish_callback, this));
    }

  private:
    void print_params() const
    {
      std::vector<std::string> param_names = 
      {
        PARAM_FILE_PATH, 
        PARAM_PUBLISHER_NAME
      };

      std::vector<rclcpp::Parameter> params = this->get_parameters(param_names);

      RCLCPP_INFO(this->get_logger(), "__________ PARAMS __________\n");

      for (auto &param : params)
      {
          RCLCPP_INFO(this->get_logger(), "%s: %s",
                      param.get_name().c_str(), param.value_to_string().c_str());
      }

      RCLCPP_INFO(this->get_logger(), "............................\n");
    }

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
  std::string file_path = (argc >= 2) ? argv[1] : "";
  std::string publisher_name = (argc >= 3) ? argv[2] : "/tof_point_cloud";

  for (int i = 0; i < argc; i++)
  {
    std::cout << "i: " << std::to_string(i).c_str() << ": " << argv[i] << std::endl;
  }

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FilePublisher>(file_path, publisher_name));
  rclcpp::shutdown();
  return 0;
}