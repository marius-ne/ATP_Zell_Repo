#include <memory>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"

#include <iostream>
#include <memory>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>

#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

#include <pcl/kdtree/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>

#include <pcl_conversions/pcl_conversions.h>

#include "wzlscheduler_interfaces/msg/labeled_point_cloud.hpp"
#include "wzlscheduler_interfaces/msg/labeled_point_clouds.hpp"

#define PARAM_SUBSCRIPTION_NAME "subscription_name"
#define PARAM_PUBLISHER_NAME "publisher_name"

using std::placeholders::_1;

class TransformationRobot : public rclcpp::Node
{
  public:
    TransformationRobot(const std::string subscription_name, const std::string& publisher_name)
    : Node("transformation_robot")
    {
        RCLCPP_INFO(this->get_logger(), "Start transformation robot");

        this->declare_parameter(PARAM_SUBSCRIPTION_NAME, subscription_name);
        this->declare_parameter(PARAM_PUBLISHER_NAME, publisher_name);


        subscriber_ = this->create_subscription<wzlscheduler_interfaces::msg::LabeledPointClouds>(
            get_parameter(PARAM_SUBSCRIPTION_NAME).as_string(), 10, std::bind(&TransformationRobot::topic_callback, this, _1));

        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

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

    void snap_pose(const wzlscheduler_interfaces::msg::LabeledPointCloud & msg) const
    {
      (void) msg;
      // todo: pose snapping 
      // infos needed: grid origin in robot/world/coordinates
      // grid hole distance
      // roughly estimated pose which needs to be snapped
      // positions of drill holes on the equipment (in the equipments local coordinate system)
    }

    void topic_callback(const wzlscheduler_interfaces::msg::LabeledPointClouds & msg) const
    {
        for (auto&& cluster : msg.elements)
        {
            snap_pose(cluster);
        }        

        // publish point cloud
        RCLCPP_INFO(this->get_logger(), "Publish matched clusters with poses");

        publisher_->publish(msg);         
    }

    rclcpp::Subscription<wzlscheduler_interfaces::msg::LabeledPointClouds>::SharedPtr subscriber_;
    rclcpp::Publisher<wzlscheduler_interfaces::msg::LabeledPointClouds>::SharedPtr publisher_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_{nullptr};
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
};

int main(int argc, char * argv[])
{
  std::string subscription_name = (argc >= 2) ? argv[1] : "/tof_point_cloud_pose_snapped";
  std::string publisher_name = (argc >= 3) ? argv[2] : "/tof_point_cloud_robot_coordinates";

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TransformationRobot>(subscription_name, publisher_name));
  rclcpp::shutdown();
  return 0;
}