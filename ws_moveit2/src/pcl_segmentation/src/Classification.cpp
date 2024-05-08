#include <memory>

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
#include <pcl/filters/voxel_grid.h>

#include <pcl/kdtree/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>

#include <pcl_conversions/pcl_conversions.h>

#include "wzlscheduler_interfaces/msg/labeled_point_cloud.hpp"
#include "wzlscheduler_interfaces/msg/labeled_point_clouds.hpp"


using std::placeholders::_1;

class Classification : public rclcpp::Node
{
  public:
    Classification()
    : Node("classification")
    {
        subscriber_ = this->create_subscription<wzlscheduler_interfaces::msg::LabeledPointClouds>(
           "/tof_point_cloud_clustered", 10, std::bind(&Classification::topic_callback, this, _1));

        using namespace std::chrono_literals;
        publisher_cluster_ = this->create_publisher<wzlscheduler_interfaces::msg::LabeledPointClouds>("/tof_point_cloud_classified", 10);

        RCLCPP_INFO(this->get_logger(), "Start classification node");
    }

  private:
    void perform_classification(wzlscheduler_interfaces::msg::LabeledPointCloud & msg) const
    {
        using namespace std;

        // -- convert point cloud --
        pcl::PCLPointCloud2 cloud;
        pcl_conversions::toPCL(msg.pointcloud, cloud);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_raw(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::fromPCLPointCloud2(cloud,*cloud_raw);

        RCLCPP_INFO(this->get_logger(), (string("Received pointcloud with points: ") + string(to_string(cloud_raw->size()))).c_str());

        // todo: find features to classifiy and label the point cloud
    }

    void topic_callback(const wzlscheduler_interfaces::msg::LabeledPointClouds & msg) const
    {
        for (auto&& cluster : msg.elements)
        {
            //perform_classification(cluster);
        }        

        // publish point cloud
        RCLCPP_INFO(this->get_logger(), "Publish labeled clusters");

        publisher_cluster_->publish(msg);      
    }

    rclcpp::Subscription<wzlscheduler_interfaces::msg::LabeledPointClouds>::SharedPtr subscriber_;
    rclcpp::Publisher<wzlscheduler_interfaces::msg::LabeledPointClouds>::SharedPtr publisher_cluster_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Classification>());
  rclcpp::shutdown();
  return 0;
}