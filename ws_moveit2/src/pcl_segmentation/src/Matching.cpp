#include <memory>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <iostream>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>

#include <pcl/kdtree/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>

#include <pcl_conversions/pcl_conversions.h>

#include "wzlscheduler_interfaces/msg/labeled_point_cloud.hpp"
#include "wzlscheduler_interfaces/msg/labeled_point_clouds.hpp"

#define PARAM_SUBSCRIPTION_NAME "subscription_name"
#define PARAM_PUBLISHER_NAME "publisher_name"

using std::placeholders::_1;

class Matching : public rclcpp::Node
{
  public:
    Matching(const std::string subscription_name, const std::string& publisher_name)
    : Node("matching")
    {
        RCLCPP_INFO(this->get_logger(), "Start matching");

        this->declare_parameter(PARAM_SUBSCRIPTION_NAME, subscription_name);
        this->declare_parameter(PARAM_PUBLISHER_NAME, publisher_name);

        print_params();

        subscriber_ = this->create_subscription<wzlscheduler_interfaces::msg::LabeledPointClouds>(
            get_parameter(PARAM_SUBSCRIPTION_NAME).as_string(), 10, std::bind(&Matching::topic_callback, this, _1));

        using namespace std::chrono_literals;
        publisher_ = this->create_publisher<wzlscheduler_interfaces::msg::LabeledPointClouds>(get_parameter(PARAM_PUBLISHER_NAME).as_string(), 10);
    }

  private:
    void print_params() const
    {
      std::vector<std::string> param_names = 
      {
        PARAM_SUBSCRIPTION_NAME, 
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

    void estimate_pose(const wzlscheduler_interfaces::msg::LabeledPointCloud & msg) const
    {
      (void) msg;
      // todo: do pose estimation using matching algos
    }

    void topic_callback(const wzlscheduler_interfaces::msg::LabeledPointClouds & msg) const
    {
        for (auto&& cluster : msg.elements)
        {
            estimate_pose(cluster);
        }        

        // publish point cloud
        RCLCPP_INFO(this->get_logger(), "Publish matched clusters with poses");

        publisher_->publish(msg);         
    }

    rclcpp::Subscription<wzlscheduler_interfaces::msg::LabeledPointClouds>::SharedPtr subscriber_;
    rclcpp::Publisher<wzlscheduler_interfaces::msg::LabeledPointClouds>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  std::string subscription_name = (argc >= 2) ? argv[1] : "/tof_point_cloud_clustered";
  std::string publisher_name = (argc >= 3) ? argv[2] : "/tof_point_cloud_matched";

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Matching>(subscription_name, publisher_name));
  rclcpp::shutdown();
  return 0;
}