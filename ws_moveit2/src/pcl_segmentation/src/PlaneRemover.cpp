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
#include <pcl/common/transforms.h>
#include <pcl/filters/passthrough.h>

#include <pcl_conversions/pcl_conversions.h>
#include <math.h>

#define PARAM_SUBSCRIPTION_NAME "subscription_name"
#define PARAM_PUBLISHER_PLANE_NAME "publisher_name_plane"
#define PARAM_PUBLISHER_PLANE_INVERTED_NAME "publisher_name_plane_inverted"
#define PARAM_DISTANCE_THRESHOLD "cluster_tolerance"
#define PARAM_MAX_ITERATIONS "cluster_size_min"
#define PARAM_FILTER_LIMITS_Z_MIN "cluster_filter_limits_z_min"
#define PARAM_FILTER_LIMITS_Z_MAX "cluster_filter_limits_z_max"

using std::placeholders::_1;

class PlaneRemover : public rclcpp::Node
{
  public:
    PlaneRemover(const std::string& subscription_name, const std::string& publisher_plane_name, const std::string& publisher_plane_inverted_name)
    : Node("plane_remover")
    {
        RCLCPP_INFO(this->get_logger(), "Start plane filter");

        this->declare_parameter(PARAM_SUBSCRIPTION_NAME, subscription_name);
        this->declare_parameter(PARAM_PUBLISHER_PLANE_NAME, publisher_plane_name);
        this->declare_parameter(PARAM_PUBLISHER_PLANE_INVERTED_NAME, publisher_plane_inverted_name);
        this->declare_parameter(PARAM_DISTANCE_THRESHOLD, 10);
        this->declare_parameter(PARAM_MAX_ITERATIONS, 1000);
        this->declare_parameter(PARAM_FILTER_LIMITS_Z_MIN, 0.0);
        this->declare_parameter(PARAM_FILTER_LIMITS_Z_MAX, 100000.0);

        subscriber_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
            get_parameter(PARAM_SUBSCRIPTION_NAME).as_string(), 10, std::bind(&PlaneRemover::topic_callback, this, _1));

        using namespace std::chrono_literals;
        publisher_plane_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(get_parameter(PARAM_PUBLISHER_PLANE_NAME).as_string(), 10);
        publisher_plane_inverted_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(get_parameter(PARAM_PUBLISHER_PLANE_INVERTED_NAME).as_string(), 10);
    }

  private:
    void topic_callback(const sensor_msgs::msg::PointCloud2 & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "Received pointcloud");

      // -- convert point cloud --
      pcl::PCLPointCloud2 cloud;
      pcl_conversions::toPCL(msg, cloud);
      pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_unfiltered(new pcl::PointCloud<pcl::PointXYZ>);
      pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
      pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered_inverted(new pcl::PointCloud<pcl::PointXYZ>);
      pcl::fromPCLPointCloud2(cloud,*cloud_unfiltered);

      // -- plane segmentation --
      pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
      pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
      // Create the segmentation object
      pcl::SACSegmentation<pcl::PointXYZ> seg;
      // Optional
      seg.setOptimizeCoefficients (true);
      // Mandatory
      seg.setModelType (pcl::SACMODEL_PLANE);
      seg.setMethodType (pcl::SAC_RANSAC);
      seg.setDistanceThreshold (get_parameter(PARAM_DISTANCE_THRESHOLD).as_double());
      seg.setMaxIterations (get_parameter(PARAM_DISTANCE_THRESHOLD).as_int());
      seg.setInputCloud (cloud_unfiltered);
      seg.segment (*inliers, *coefficients);

      if (inliers->indices.size () == 0)
      {
        PCL_ERROR ("Could not estimate a planar model for the given dataset.");
        return;
      }

      std::cerr << "Model coefficients: " << coefficients->values[0] << " " 
                                          << coefficients->values[1] << " "
                                          << coefficients->values[2] << " " 
                                          << coefficients->values[3] << std::endl;

      // Extract the planar inliers from the input cloud
      pcl::ExtractIndices<pcl::PointXYZ> extract;
      extract.setInputCloud (cloud_unfiltered);
      extract.setIndices(inliers);
      extract.setNegative(false);
      extract.filter (*cloud_filtered);        

      pcl::ExtractIndices<pcl::PointXYZ> extract_inverted;
      extract.setInputCloud (cloud_unfiltered);
      extract.setIndices(inliers);
      extract.setNegative(true);
      extract.filter (*cloud_filtered_inverted);   

      // transform point cloud -> working plate plane should match the world xy-plane
      Eigen::Matrix<float, 1, 3> floor_plane_normal_vector, xy_plane_normal_vector;

      floor_plane_normal_vector[0] = coefficients->values[0];
      floor_plane_normal_vector[1] = coefficients->values[1];
      floor_plane_normal_vector[2] = coefficients->values[2];

      xy_plane_normal_vector[0] = 0.0;
      xy_plane_normal_vector[1] = 0.0;
      xy_plane_normal_vector[2] = 1.0;

      Eigen::Vector3f rotation_vector = xy_plane_normal_vector.cross(floor_plane_normal_vector);
      float theta = -atan2(rotation_vector.norm(), xy_plane_normal_vector.dot(floor_plane_normal_vector)) + M_PI;

      Eigen::Affine3f transform = Eigen::Affine3f::Identity();
      transform.translation() << 0, 0, -coefficients->values[3]; // add plane normal distance as z translation
      transform.rotate (Eigen::AngleAxisf (theta, rotation_vector.normalized()));
      
      std::cout << "Transformation matrix: " << std::endl << transform.matrix() << std::endl;
      pcl::transformPointCloud (*cloud_filtered, *cloud_filtered, transform);
      pcl::transformPointCloud (*cloud_filtered_inverted, *cloud_filtered_inverted, transform);

      // delete all points which are located below the plane
      pcl::PassThrough<pcl::PointXYZ> pass;
      pass.setInputCloud (cloud_filtered_inverted);
      pass.setFilterFieldName ("z");
      pass.setFilterLimits (get_parameter(PARAM_FILTER_LIMITS_Z_MIN).as_int(), get_parameter(PARAM_FILTER_LIMITS_Z_MAX).as_int());
      
      pass.filter (*cloud_filtered_inverted);

      // publish point cloud
      sensor_msgs::msg::PointCloud2 sensor_msg_plane;
      pcl::toROSMsg(*cloud_filtered, sensor_msg_plane);
      publisher_plane_->publish(sensor_msg_plane);      

      sensor_msgs::msg::PointCloud2 sensor_msg_plane_inverted;
      pcl::toROSMsg(*cloud_filtered_inverted, sensor_msg_plane_inverted);
      publisher_plane_inverted_->publish(sensor_msg_plane_inverted);   
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscriber_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_plane_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_plane_inverted_;
};

int main(int argc, char * argv[])
{
  std::string subscription_name = (argc >= 2) ? argv[1] : "/tof_point_cloud_downsampled";
  std::string publisher_plane_name = (argc >= 3) ? argv[2] : "/tof_point_cloud_filtered_plane";
  std::string publisher_plane_inverted_name = (argc >= 4) ? argv[3] : "/tof_point_cloud_filtered_plane_inverted";

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PlaneRemover>(subscription_name, publisher_plane_name, publisher_plane_inverted_name));
  rclcpp::shutdown();
  return 0;
}