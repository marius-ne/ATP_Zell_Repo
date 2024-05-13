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
#define PARAM_MARKER_DISTANCE = "param_marker_distance_name"
#define PARAM_MARKER_OFFSET_X = "param_marker_offset_x"
#define PARAM_MARKER_OFFSET_Y = "param_marker_offset_y"

using std::placeholders::_1;

class PoseSnapper : public rclcpp::Node
{
  public:
    PoseSnapper(const std::string subscription_name, const std::string& publisher_name)
    : Node("posesnapper")
    {
        RCLCPP_INFO(this->get_logger(), "Start pose snapper");

        this->declare_parameter(PARAM_SUBSCRIPTION_NAME, subscription_name);
        this->declare_parameter(PARAM_PUBLISHER_NAME, publisher_name);
        this->declare_parameter(PARAM_MARKER_DISTANCE, 0.1f);
        this->declare_parameter(PARAM_MARKER_OFFSET_X, 0.0);
        this->declare_parameter(PARAM_MARKER_OFFSET_Y, 0.0);

        subscriber_ = this->create_subscription<wzlscheduler_interfaces::msg::LabeledPointClouds>(
            get_parameter(PARAM_SUBSCRIPTION_NAME).as_string(), 10, std::bind(&PoseSnapper::topic_callback, this, _1));

        using namespace std::chrono_literals;
        publisher_ = this->create_publisher<wzlscheduler_interfaces::msg::LabeledPointClouds>(get_parameter(PARAM_PUBLISHER_NAME).as_string(), 10);
    }

  private:
    void print_params() const
    {
      std::vector<std::string> param_names = 
      {
        PARAM_SUBSCRIPTION_NAME, 
        PARAM_PUBLISHER_NAME,
        PARAM_MARKER_DISTANCE,
        PARAM_MARKER_OFFSET_X,
        PARAM_MARKER_OFFSET_Y
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
      auto snap_distance = get_parameter(PARAM_MARKER_DISTANCE).as_double();

      auto new_position_x = msg.poseorigin.position.x + 0.5 * snap_distance;
      auto new_position_y = msg.poseorigin.position.y + 0.5 * snap_distance;
      auto new_position_z = 0;

      new_position_x = (int)new_position_x;
      new_position_y = (int)new_position_y;


      auto msg_snapped = std::make_shared<wzlscheduler_interfaces::msg::LabeledPointCloud>();
      msg_snapped->pointcloud = msg.pointcloud;
      msg_snapped->posecad = 
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
};

int main(int argc, char * argv[])
{
  std::string subscription_name = (argc >= 2) ? argv[1] : "/tof_point_cloud_matched";
  std::string publisher_name = (argc >= 3) ? argv[2] : "/tof_point_cloud_pose_snapped";

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PoseSnapper>(subscription_name, publisher_name));
  rclcpp::shutdown();
  return 0;
}