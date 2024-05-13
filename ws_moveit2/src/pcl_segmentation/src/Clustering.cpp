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
#define PARAM_PUBLISHER_COLORED_NAME "publisher_name_colored"
#define PARAM_PUBLISHER_CLUSTERED_NAME "publisher_name_clustered"
#define PARAM_CLUSTER_TOLERANCE "cluster_tolerance"
#define PARAM_CLUSTER_SIZE_MIN "cluster_size_min"
#define PARAM_CLUSTER_SIZE_MAX "cluster_size_max"

using std::placeholders::_1;

class Clustering : public rclcpp::Node
{
  public:
    Clustering(const std::string& subscription_name, const std::string& publisher_colored_name, const std::string& publisher_clustered_name)
    : Node("clustering")
    {
        RCLCPP_INFO(this->get_logger(), "Start clustering");

        this->declare_parameter(PARAM_SUBSCRIPTION_NAME, subscription_name);
        this->declare_parameter(PARAM_PUBLISHER_COLORED_NAME, publisher_colored_name);
        this->declare_parameter(PARAM_PUBLISHER_CLUSTERED_NAME, publisher_clustered_name);
        this->declare_parameter(PARAM_CLUSTER_TOLERANCE, 5.0);
        this->declare_parameter(PARAM_CLUSTER_SIZE_MIN, 2000.0);
        this->declare_parameter(PARAM_CLUSTER_SIZE_MAX, 1000000.0);

        print_params();

        subscriber_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            get_parameter(PARAM_SUBSCRIPTION_NAME).as_string(), 10, std::bind(&Clustering::topic_callback, this, _1));

        using namespace std::chrono_literals;
        publisher_colored_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(get_parameter(PARAM_PUBLISHER_COLORED_NAME).as_string(), 10);
        publisher_clustered_ = this->create_publisher<wzlscheduler_interfaces::msg::LabeledPointClouds>(get_parameter(PARAM_PUBLISHER_CLUSTERED_NAME).as_string(), 10);
    }

  private:
    void print_params() const
    {
      std::vector<std::string> param_names = 
      {
        PARAM_SUBSCRIPTION_NAME,
        PARAM_PUBLISHER_COLORED_NAME,
        PARAM_PUBLISHER_CLUSTERED_NAME,
        PARAM_CLUSTER_TOLERANCE,
        PARAM_CLUSTER_SIZE_MIN,
        PARAM_CLUSTER_SIZE_MAX
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
      pcl::fromPCLPointCloud2(cloud,*cloud_raw);

      RCLCPP_INFO(this->get_logger(), (string("Received pointcloud with points: ") + string(to_string(cloud_raw->size()))).c_str());

      RCLCPP_INFO(this->get_logger(), "Build kd-tree");
      // Create the KdTree object for the search method of the extraction
      pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB>);
      tree->setInputCloud (cloud_raw);

      RCLCPP_INFO(this->get_logger(), "Created cluster");
      // create the extraction object for the clusters
      std::vector<pcl::PointIndices> cluster_indices;
      pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ece;

      // specify euclidean cluster parameters
      ece.setClusterTolerance (get_parameter(PARAM_CLUSTER_TOLERANCE).as_double());
      ece.setMinClusterSize (get_parameter(PARAM_CLUSTER_SIZE_MIN).as_double());
      ece.setMaxClusterSize (get_parameter(PARAM_CLUSTER_SIZE_MAX).as_double());
      ece.setSearchMethod (tree);
      ece.setInputCloud (cloud_raw);
      // exctract the indices pertaining to each cluster and store in a vector of pcl::PointIndices
      ece.extract (cluster_indices);

      RCLCPP_INFO(this->get_logger(), (string("Set cluster colors with classes count: ") + string(to_string(cluster_indices.size()))).c_str() );
      
      int j = 0;  
      float colors[6][3] ={{255, 0, 0}, {0,255,0}, {0,0,255}, {255,255,0}, {0,255,255}, {255,0,255}};  
      pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZRGB>);
      pcl::copyPointCloud(*cloud_raw, *cloud_cluster);
      
      std::vector<pcl::PointCloud<pcl::PointXYZRGB>::Ptr> clusters;

      for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin (); it != cluster_indices.end (); ++it)  
      {  
          pcl::PointCloud<pcl::PointXYZRGB>::Ptr cluster_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);  
          pcl::copyPointCloud(*cloud_raw, it->indices, *cluster_cloud);

          clusters.push_back(cluster_cloud);

          for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); pit++) 
          {  
            cloud_cluster->points[*pit].r = colors[j%6][0];  
            cloud_cluster->points[*pit].g = colors[j%6][1];  
            cloud_cluster->points[*pit].b = colors[j%6][2];  
          }  
          j++;  
      }  
      
      // publish point cloud (colored)
      RCLCPP_INFO(this->get_logger(), "Publish point");
      sensor_msgs::msg::PointCloud2 sensor_msg_plane;
      pcl::toROSMsg(*cloud_cluster, sensor_msg_plane);
    
      publisher_colored_->publish(sensor_msg_plane);      

      // publish point cloud (clusters)
      wzlscheduler_interfaces::msg::LabeledPointClouds msg_pointclouds;

      for (auto cloud : clusters)
      {
        wzlscheduler_interfaces::msg::LabeledPointCloud msg_pointcloud;
        msg_pointcloud.label = "unlabeled";

        sensor_msgs::msg::PointCloud2 sensor_msg_cluster;
        pcl::toROSMsg(*cloud_cluster, sensor_msg_cluster);
        
        msg_pointcloud.pointcloud = sensor_msg_cluster;
      }

      publisher_clustered_->publish(msg_pointclouds);
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscriber_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_colored_;
    rclcpp::Publisher<wzlscheduler_interfaces::msg::LabeledPointClouds>::SharedPtr publisher_clustered_;
};

int main(int argc, char * argv[])
{
  std::string subscription_name = (argc >= 2) ? argv[1] : "/tof_point_cloud_filtered_plane_inverted";
  std::string publisher_colored_name = (argc >= 3) ? argv[2] : "/tof_point_cloud_colored";
  std::string publisher_clustered_name = (argc >= 4) ? argv[3] : "/tof_point_cloud_clustered";

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Clustering>(subscription_name, publisher_colored_name, publisher_clustered_name));
  rclcpp::shutdown();
  return 0;
}