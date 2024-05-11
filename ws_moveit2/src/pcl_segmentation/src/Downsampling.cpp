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


using std::placeholders::_1;

#define PARAM_SUBSCRIPTION_NAME "subscription_name"
#define PARAM_PUBLISHER_NAME "publisher_name"
#define PARAM_LEAF_SIZE "leaf_size"

class Downsampling : public rclcpp::Node
{
  public:
    Downsampling(const std::string subscription_name, const std::string& publisher_name)
    : Node("downsampling")
    {
        RCLCPP_INFO(this->get_logger(), "Start downsampling\n");

        this->declare_parameter(PARAM_SUBSCRIPTION_NAME, subscription_name);
        this->declare_parameter(PARAM_PUBLISHER_NAME, publisher_name);
        this->declare_parameter(PARAM_LEAF_SIZE, 3.0);

        print_params();

        subscriber_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            this->get_parameter(PARAM_SUBSCRIPTION_NAME).as_string(), 10, std::bind(&Downsampling::topic_callback, this, _1));

        using namespace std::chrono_literals;
        publisher_cluster_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(this->get_parameter(PARAM_PUBLISHER_NAME).as_string(), 10);
    }

  private:
    void print_params() const
    {
      std::vector<std::string> param_names = 
      {
        PARAM_SUBSCRIPTION_NAME, 
        PARAM_PUBLISHER_NAME,
        PARAM_LEAF_SIZE
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

    void topic_callback(const sensor_msgs::msg::PointCloud2 & msg) const
    {
        using namespace std;

        // -- convert point cloud --
        pcl::PCLPointCloud2 cloud;
        pcl_conversions::toPCL(msg, cloud);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_raw(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGB>);
        pcl::fromPCLPointCloud2(cloud,*cloud_raw);

        RCLCPP_INFO(this->get_logger(), (string("Received pointcloud with points: ") + string(to_string(cloud_raw->size()))).c_str());

        // filtering with Voxel Grid
        pcl::VoxelGrid<pcl::PointXYZRGB> voxelGrid;
        voxelGrid.setInputCloud(cloud_raw);
        // set the leaf size (x, y, z)
        float leaf_size_x = this->get_parameter(PARAM_LEAF_SIZE).as_double();
        float leaf_size_y = this->get_parameter(PARAM_LEAF_SIZE).as_double();
        float leaf_size_z = this->get_parameter(PARAM_LEAF_SIZE).as_double();

        voxelGrid.setLeafSize(leaf_size_x, leaf_size_y, leaf_size_z);
        // apply the filter to dereferenced cloudVoxel
        voxelGrid.filter(*cloud_filtered);
        
        RCLCPP_INFO(this->get_logger(), (string("Size of filtered cloud: ") + string(to_string(cloud_filtered->size()))).c_str());

        // publish point cloud
        RCLCPP_INFO(this->get_logger(), "Publish point");
        sensor_msgs::msg::PointCloud2 sensor_msg_plane;
        pcl::toROSMsg(*cloud_filtered, sensor_msg_plane);
        
        publisher_cluster_->publish(sensor_msg_plane);      
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscriber_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_cluster_;
};

int main(int argc, char * argv[])
{
  std::string subscription_name = (argc >= 2) ? argv[1] : "/tof_point_cloud";
  std::string publisher_name = (argc >= 3) ? argv[2] : "/tof_point_cloud_downsampled";

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Downsampling>(subscription_name, publisher_name));
  rclcpp::shutdown();
  return 0;
}