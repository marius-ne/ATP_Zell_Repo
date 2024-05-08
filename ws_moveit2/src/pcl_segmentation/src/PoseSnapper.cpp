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


using std::placeholders::_1;

class PoseSnapper : public rclcpp::Node
{
  public:
    PoseSnapper()
    : Node("posesnapper")
    {
        subscriber_ = this->create_subscription<wzlscheduler_interfaces::msg::LabeledPointClouds>(
            "tof_point_cloud_clustered", 10, std::bind(&PoseSnapper::topic_callback, this, _1));

        using namespace std::chrono_literals;
        publisher_ = this->create_publisher<wzlscheduler_interfaces::msg::LabeledPointClouds>("/tof_point_cloud_matched", 10);

        RCLCPP_INFO(this->get_logger(), "Start plane filter");
    }

  private:

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
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PoseSnapper>());
  rclcpp::shutdown();
  return 0;
}