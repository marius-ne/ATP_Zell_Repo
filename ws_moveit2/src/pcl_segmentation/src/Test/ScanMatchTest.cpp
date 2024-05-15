#include <memory>
#include <vector>
#include <Eigen/Core>

#include "rclcpp/rclcpp.hpp"
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/common/time.h>
#include <pcl/console/print.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/fpfh_omp.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/io/pcd_io.h>
#include <pcl/registration/sample_consensus_prerejective.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/ply_io.h>

#include "wzlscheduler_interfaces/msg/labeled_point_cloud.hpp"
#include "wzlscheduler_interfaces/msg/labeled_point_clouds.hpp"

using std::placeholders::_1;

// Types
typedef pcl::PointNormal PointNT;
typedef pcl::PointCloud<PointNT> PointCloudT;
typedef pcl::FPFHSignature33 FeatureT;
typedef pcl::FPFHEstimationOMP<PointNT,PointNT,FeatureT> FeatureEstimationT;
typedef pcl::PointCloud<FeatureT> FeatureCloudT;
typedef pcl::visualization::PointCloudColorHandlerCustom<PointNT> ColorHandlerT;

class ScanMatchTest : public rclcpp::Node
{
  public:
    ScanMatchTest(const std::string subscription_name, const std::string& publisher_name)
    : Node("scanmatch_test")
    {
        RCLCPP_INFO(this->get_logger(), "Start scanmatch test");

        load_from_file("/home/aw/restackcell/ws_moveit2/src/pcl_segmentation/data/0.ply", cloud_1_, sensor_msg_1_);
        load_from_file("/home/aw/restackcell/ws_moveit2/src/pcl_segmentation/data/1.ply", cloud_2_, sensor_msg_2_);
        load_from_file("/home/aw/restackcell/ws_moveit2/src/pcl_segmentation/data/2.ply", cloud_3_, sensor_msg_3_);

        
        using namespace std::chrono_literals;
        publisher_1_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/tof_point_cloud_1", 10);
        publisher_2_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/tof_point_cloud_2", 10);
        publisher_3_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/tof_point_cloud_3", 10);
        publisher_fused_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/tof_point_cloud_fused", 10);

    }

  private:
    void load_from_file(const std::string file_path, pcl::PointCloud<pcl::PointXYZ>::Ptr& pointcloud, sensor_msgs::msg::PointCloud2::Ptr& sensormsg)
        {
        // Load ply from file
        pointcloud = std::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
        pcl::PLYReader reader;
        reader.read(file_path, *pointcloud);      

        // convert to sensor msg
        sensormsg = std::make_shared<sensor_msgs::msg::PointCloud2>();
        pcl::toROSMsg(*pointcloud, *sensormsg.get());               
    }

    void publish_callback() const
    {
      // publish point cloud
      sensor_msg_1_->header.frame_id = "map";
      sensor_msg_1_->header.stamp = now();
      publisher_1_->publish(*sensor_msg_1_.get());     
            
      sensor_msg_2_->header.frame_id = "map";
      sensor_msg_2_->header.stamp = now();
      publisher_2_->publish(*sensor_msg_2_.get());

      //sensor_msg_3_->header.frame_id = "map";
      //sensor_msg_3_->header.stamp = now();
      //publisher_3_->publish(*sensor_msg_3_.get());

      sensor_msg_fused_->header.frame_id = "map";
      sensor_msg_fused_->header.stamp = now();
      publisher_fused_->publish(*sensor_msg_fused_.get());
    }

    void estimate_pose() const
    {
      float scale = 1000.0;

      // Point clouds
      PointCloudT::Ptr object (new PointCloudT);
      PointCloudT::Ptr object_aligned (new PointCloudT);
      PointCloudT::Ptr scene_before_downsampling (new PointCloudT);
      PointCloudT::Ptr scene (new PointCloudT);
      FeatureCloudT::Ptr object_features (new FeatureCloudT);
      FeatureCloudT::Ptr scene_features (new FeatureCloudT);


      pcl::PCLPointCloud2 cloud;
      pcl_conversions::toPCL(msg.pointcloud, cloud);
      pcl::PointCloud<pcl::PointNormal>::Ptr cloud_raw(new pcl::PointCloud<pcl::PointNormal>);
      pcl::fromPCLPointCloud2(cloud,*object);

      // Load ply from file
      auto cloud_ = std::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
      pcl::PLYReader reader;
      reader.read("/home/aw/restackcell/ws_moveit2/src/pcl_segmentation/data/0.ply", *cloud_);      

      // convert to sensor msg
      auto sensor_msg_ = std::make_shared<sensor_msgs::msg::PointCloud2>();
      pcl::toROSMsg(*cloud_, *sensor_msg_.get());   

      // Downsample
      pcl::console::print_highlight ("Downsampling...\n");
      pcl::VoxelGrid<PointNT> grid;
      const float leaf = 0.005f * scale;
      grid.setLeafSize (leaf, leaf, leaf);
      grid.setInputCloud (object);
      grid.filter (*object);
      grid.setInputCloud (scene_before_downsampling);
      grid.filter (*scene);

      // Estimate normals for scene
      pcl::console::print_highlight ("Estimating scene normals...\n");
      pcl::NormalEstimationOMP<PointNT,PointNT> nest;
      nest.setRadiusSearch (0.005 * scale);
      nest.setInputCloud (object);
      nest.setSearchSurface (scene_before_downsampling);
      nest.compute (*scene);

      // Estimate features
      pcl::console::print_highlight ("Estimating features...\n");
      FeatureEstimationT fest;
      fest.setRadiusSearch (0.025 * scale);
      fest.setInputCloud (object);
      fest.setInputNormals (object);
      fest.compute (*object_features);
      fest.setInputCloud (scene);
      fest.setInputNormals (scene);
      fest.compute (*scene_features);

      // Perform alignment
      pcl::console::print_highlight ("Starting alignment...\n");
      pcl::SampleConsensusPrerejective<PointNT,PointNT,FeatureT> align;
      align.setInputSource (object);
      align.setSourceFeatures (object_features);
      align.setInputTarget (scene);
      align.setTargetFeatures (scene_features);
      align.setMaximumIterations (50000); // Number of RANSAC iterations
      align.setNumberOfSamples (3); // Number of points to sample for generating/prerejecting a pose
      align.setCorrespondenceRandomness (5); // Number of nearest features to use
      align.setSimilarityThreshold (0.95f); // Polygonal edge length similarity threshold
      align.setMaxCorrespondenceDistance (2.5f * leaf); // Inlier threshold
      align.setInlierFraction (0.25f); // Required inlier fraction for accepting a pose hypothesis
        /*
      {
        pcl::ScopeTime t("Alignment");
        align.align (*object_aligned);
      }
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
        */   
    }

    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_1_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_2_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_3_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_fused_;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_1_;
    sensor_msgs::msg::PointCloud2::Ptr sensor_msg_1_;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_2_;
    sensor_msgs::msg::PointCloud2::Ptr sensor_msg_2_;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_3_;
    sensor_msgs::msg::PointCloud2::Ptr sensor_msg_3_;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fused_;
    sensor_msgs::msg::PointCloud2::Ptr sensor_msg_fused_;
    
};

int main(int argc, char * argv[])
{
  std::string subscription_name = (argc >= 2) ? argv[1] : "/tof_point_cloud_clustered";
  std::string publisher_name = (argc >= 3) ? argv[2] : "/tof_point_cloud_matched";

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ScanMatchTest>(subscription_name, publisher_name));
  rclcpp::shutdown();
  return 0;
}