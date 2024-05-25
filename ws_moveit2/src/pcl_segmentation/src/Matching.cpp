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

#include "wzlscheduler_interfaces/msg/labeled_point_cloud.hpp"
#include "wzlscheduler_interfaces/msg/labeled_point_clouds.hpp"

#define PARAM_SUBSCRIPTION_NAME "subscription_name"
#define PARAM_PUBLISHER_NAME "publisher_name"

using std::placeholders::_1;


// Types
typedef pcl::PointNormal PointNT;
typedef pcl::PointCloud<PointNT> PointCloudT;
typedef pcl::FPFHSignature33 FeatureT;
typedef pcl::FPFHEstimationOMP<PointNT,PointNT,FeatureT> FeatureEstimationT;
typedef pcl::PointCloud<FeatureT> FeatureCloudT;
typedef pcl::visualization::PointCloudColorHandlerCustom<PointNT> ColorHandlerT;

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
      pcl::fromPCLPointCloud2(cloud,*cloud_raw);

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
      //align.setMaxCorrespondenceDistance (2.5f * leaf); // Inlier threshold
      align.setInlierFraction (0.25f); // Required inlier fraction for accepting a pose hypothesis

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