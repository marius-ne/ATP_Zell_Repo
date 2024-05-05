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

#include <pcl/kdtree/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>

#include <pcl_conversions/pcl_conversions.h>


using std::placeholders::_1;

class Clustering : public rclcpp::Node
{
  public:
    Clustering()
    : Node("clustering")
    {
        subscriber_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            "tof_point_cloud_filtered_plane_inverted", 10, std::bind(&Clustering::topic_callback, this, _1));

        using namespace std::chrono_literals;
        publisher_cluster_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/tof_point_cloud_clustered", 10);

        RCLCPP_INFO(this->get_logger(), "Start plane filter");
    }

  private:
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
      ece.setClusterTolerance (5);
      ece.setMinClusterSize (2000);
      ece.setMaxClusterSize (1000000);
      ece.setSearchMethod (tree);
      ece.setInputCloud (cloud_raw);
      // exctract the indices pertaining to each cluster and store in a vector of pcl::PointIndices
      ece.extract (cluster_indices);

      RCLCPP_INFO(this->get_logger(), (string("Set cluster colors with classes count: ") + string(to_string(cluster_indices.size()))).c_str() );
      
      int j = 0;  
      float colors[6][3] ={{255, 0, 0}, {0,255,0}, {0,0,255}, {255,255,0}, {0,255,255}, {255,0,255}};  
      pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZRGB>);  
      pcl::copyPointCloud(*cloud_raw, *cloud_cluster);
      for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin (); it != cluster_indices.end (); ++it)  
      {  
        for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); pit++) 
        {  
          cloud_cluster->points[*pit].r = colors[j%6][0];  
          cloud_cluster->points[*pit].g = colors[j%6][1];  
          cloud_cluster->points[*pit].b = colors[j%6][2];  
        }  
        j++;  
      }  
      
      // publish point cloud
      RCLCPP_INFO(this->get_logger(), "Publish point");
      sensor_msgs::msg::PointCloud2 sensor_msg_plane;
      pcl::toROSMsg(*cloud_cluster, sensor_msg_plane);
    
      publisher_cluster_->publish(sensor_msg_plane);      
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscriber_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_cluster_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Clustering>());
  rclcpp::shutdown();
  return 0;
}