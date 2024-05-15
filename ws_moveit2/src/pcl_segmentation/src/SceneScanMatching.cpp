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
#include <pcl/common/io.h> // for concatenateFields

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/ply_io.h>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"

using std::placeholders::_1;

// Types
typedef pcl::PointNormal PointNT;
typedef pcl::PointCloud<PointNT> PointCloudT;
typedef pcl::FPFHSignature33 FeatureT;
typedef pcl::FPFHEstimationOMP<PointNT,PointNT,FeatureT> FeatureEstimationT;
typedef pcl::PointCloud<FeatureT> FeatureCloudT;
typedef pcl::visualization::PointCloudColorHandlerCustom<PointNT> ColorHandlerT;

class SceneScanMathing : public rclcpp::Node
{
  public:
    SceneScanMathing()
    : Node("scanmatch_test")
    {
        RCLCPP_INFO(this->get_logger(), "Start scanmatch test");

        RCLCPP_INFO(this->get_logger(), "Load pointclouds");
        tf_static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);

        load_pointclouds();

        RCLCPP_INFO(this->get_logger(), "Create Publishers");
        using namespace std::chrono_literals;
        publisher_1_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/tof_point_cloud_1", 10);
        publisher_2_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/tof_point_cloud_2", 10);
        publisher_3_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/tof_point_cloud_3", 10);
        publisher_fused_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/tof_point_cloud_fused", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&SceneScanMathing::publish_callback, this));
    }

  private:
    void publish_tf_transform(const std::string parent_frame, const std::string child_frame, const Eigen::Vector3d& translation, 
        const double roll_arc, const double pitch_arc, const double yaw_arc)
    {
      geometry_msgs::msg::TransformStamped t;

      t.header.stamp = this->get_clock()->now();
      t.header.frame_id = parent_frame;
      t.child_frame_id = child_frame;

      t.transform.translation.x = translation.x();
      t.transform.translation.y = translation.y();
      t.transform.translation.z = translation.z();
      tf2::Quaternion q;
      q.setRPY(
        roll_arc,
        pitch_arc,
        yaw_arc
      );

      t.transform.rotation.x = q.x();
      t.transform.rotation.y = q.y();
      t.transform.rotation.z = q.z();
      t.transform.rotation.w = q.w();

      tf_static_broadcaster_->sendTransform(t);
    }

    Eigen::Matrix3d CreateRotationMatrix(const double roll_arc, const double pitch_arc, const double yaw_arc)
    {
        return Eigen::AngleAxisd(yaw_arc, Eigen::Vector3d::UnitZ())
            * Eigen::AngleAxisd(pitch_arc, Eigen::Vector3d::UnitY())
            * Eigen::AngleAxisd(roll_arc, Eigen::Vector3d::UnitX()).toRotationMatrix();
    }

    Eigen::Matrix4d create_transformation(const double translation_x, const double translation_y, const double translation_z,
        const double roll_arc, const double pitch_arc, const double yaw_arc,
        const std::string frame_name_tcp, const std::string frame_name_camera)
    {
        //auto roll_arc = roll_degree * M_PI / 180;
        //auto pitch_arc = pitch_degree * M_PI / 180;
        //auto yaw_arc = yaw_degree * M_PI / 180;

        // Calculate RPC rotation matrix
        /*
        Eigen::Matrix3d R = Eigen::AngleAxisd(roll_arc, Eigen::Vector3d::UnitX())
            * Eigen::AngleAxisd(pitch_arc, Eigen::Vector3d::UnitY())
            * Eigen::AngleAxisd(yaw_arc, Eigen::Vector3d::UnitZ()).toRotationMatrix();
            * */
        Eigen::Matrix3d R = CreateRotationMatrix(roll_arc, pitch_arc, yaw_arc);
            
        // Find your Rotation Matrix
        Eigen::Vector3d t = Eigen::Vector3d(translation_x, translation_y, translation_z);
        // Find your translation Vector
        Eigen::Matrix4d T; // Your Transformation Matrix
        T.setIdentity();   // Set to Identity to make bottom row of Matrix 0,0,0,1
        T.block<3,3>(0,0) = R;
        T.block<3,1>(0,3) = t;

        publish_tf_transform("map", frame_name_tcp, t, roll_arc, pitch_arc, yaw_arc);
        // add hand eye camera calibration

        // Calculate RPC rotation matrix
        
        auto handeye_roll = M_PI;
        auto handeye_pitch = M_PI_2;
        auto handeye_yaw = 0;
        

        //auto handeye_roll = 0;
        //auto handeye_pitch = 0;
        //auto handeye_yaw = 0;

        /*

        Eigen::Matrix3d R_he = Eigen::AngleAxisd(handeye_roll, Eigen::Vector3d::UnitX())
            * Eigen::AngleAxisd(handeye_pitch, Eigen::Vector3d::UnitY())
            * Eigen::AngleAxisd(handeye_yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();
            * */

        Eigen::Matrix3d R_he = CreateRotationMatrix(handeye_roll, handeye_pitch, handeye_yaw);

        // Find your Rotation Matrix
        Eigen::Vector3d t_he = Eigen::Vector3d(0, 0, 300);
        // Find your translation Vector
        Eigen::Matrix4d T_he; // Your Transformation Matrix
        T_he.setIdentity();   // Set to Identity to make bottom row of Matrix 0,0,0,1
        T_he.block<3,3>(0,0) = R_he;
        T_he.block<3,1>(0,3) = t_he;

        publish_tf_transform(frame_name_tcp, frame_name_camera, t_he, handeye_roll, handeye_pitch, handeye_yaw);

        // endpose
        auto t_end = T * T_he;

        return t_end;
    }

    void load_from_file(const std::string file_path, pcl::PointCloud<pcl::PointXYZ>::Ptr& pointcloud, sensor_msgs::msg::PointCloud2::Ptr& sensormsg,
        const double translation_x, const double translation_y, const double translation_z,
        const double roll_arc, const double pitch_arc, const double yaw_arc,
        const std::string frame_name_tcp, const std::string frame_name_camera)
        {
        // Load ply from file
        auto pointcloud_raw = std::make_shared<pcl::PointCloud<pcl::PointXYZ>>();

        pcl::PLYReader reader;
        reader.read(file_path, *pointcloud_raw);      

        auto cloud_transform_1 = create_transformation(translation_x, translation_y, translation_z, roll_arc, pitch_arc, yaw_arc, frame_name_tcp, frame_name_camera);
        pcl::transformPointCloud(*pointcloud_raw, *pointcloud, cloud_transform_1);

        // convert to sensor msg
        sensormsg = std::make_shared<sensor_msgs::msg::PointCloud2>();
        pcl::toROSMsg(*pointcloud, *sensormsg.get());               
    }

    void load_pointclouds()
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_raw_1;
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_raw_2;
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_raw_3;

        sensor_msg_1_ = std::make_shared<sensor_msgs::msg::PointCloud2>();
        sensor_msg_2_ = std::make_shared<sensor_msgs::msg::PointCloud2>();
        sensor_msg_3_ = std::make_shared<sensor_msgs::msg::PointCloud2>();
        sensor_msg_fused_ = std::make_shared<sensor_msgs::msg::PointCloud2>();

        cloud_1_ = std::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
        cloud_2_ = std::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
        cloud_3_ = std::make_shared<pcl::PointCloud<pcl::PointXYZ>>();

        load_from_file("/home/aw/restackcell/ws_moveit2/src/pcl_segmentation/data/0.ply", cloud_1_, sensor_msg_1_, 232, -751, 394, 0.977, -1.582, -1.573, "tcp0", "camera0");
        load_from_file("/home/aw/restackcell/ws_moveit2/src/pcl_segmentation/data/1.ply", cloud_2_, sensor_msg_2_, 764, -581, 55, 0.73, -0.8, -1.4, "tcp1", "camera1");
        load_from_file("/home/aw/restackcell/ws_moveit2/src/pcl_segmentation/data/2.ply", cloud_3_, sensor_msg_3_, -363.4, -633.9, 466, 0.696, -2.222, -2.185, "tcp2", "camera2");

        RCLCPP_INFO(this->get_logger(), "Create transformations");

        //auto cloud_transform_1 = create_transformation(232, -751, 394, 0.977, -1.582, -1.573);
        //auto cloud_transform_2 = create_transformation(764, -581, 55, 0.73, -0.8, -1.4);
        //auto cloud_transform_3 = create_transformation(-363.4, -633.9, 466, 0.696, -2.222, -2.185);

        RCLCPP_INFO(this->get_logger(), "Apply transformations");

        //cloud_1_ = std::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
        //cloud_2_ = std::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
        //cloud_3_ = std::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
        cloud_fused_ = std::make_shared<pcl::PointCloud<pcl::PointXYZ>>();

        //pcl::transformPointCloud(*cloud_raw_1, *cloud_1_, cloud_transform_1);
        //pcl::transformPointCloud(*cloud_raw_2, *cloud_2_, cloud_transform_2);
        //pcl::transformPointCloud(*cloud_raw_3, *cloud_3_, cloud_transform_3);

        RCLCPP_INFO(this->get_logger(), "Fuse pointcloud");

        // fuse pointcloud
        *cloud_fused_ = *cloud_1_ + *cloud_2_ + *cloud_3_;

        sensor_msg_fused_ = std::make_shared<sensor_msgs::msg::PointCloud2>();
        pcl::toROSMsg(*cloud_fused_, *sensor_msg_fused_.get());  
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

      sensor_msg_3_->header.frame_id = "map";
      sensor_msg_3_->header.stamp = now();
      publisher_3_->publish(*sensor_msg_3_.get());

      sensor_msg_fused_->header.frame_id = "map";
      sensor_msg_fused_->header.stamp = now();
      publisher_fused_->publish(*sensor_msg_fused_.get());

      RCLCPP_INFO(this->get_logger(), "Publish pointclods");
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

    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SceneScanMathing>());
  rclcpp::shutdown();
  return 0;
}