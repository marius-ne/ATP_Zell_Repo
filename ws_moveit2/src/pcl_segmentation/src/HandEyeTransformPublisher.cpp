
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"

#define PARAM_TF2_HAND_FRAME_NAME "tf2_hand_frame_name"
#define PARAM_TF2_EYE_FRAME_NAME "tf2_eye_frame_name"
#define PARAM_TF2_TRANLSATION_X "tf2_translation_x"
#define PARAM_TF2_TRANLSATION_Y "tf2_translation_y"
#define PARAM_TF2_TRANLSATION_Z "tf2_translation_z"
#define PARAM_TF2_ROTATION_RAD_X "tf2_rotation_rad_x"
#define PARAM_TF2_ROTATION_RAD_Y "tf2_rotation_rad_y"
#define PARAM_TF2_ROTATION_RAD_Z "tf2_rotation_rad_z"

using std::placeholders::_1;

class HandEyeTransformPublisher : public rclcpp::Node
{
  public:
    HandEyeTransformPublisher(const std::string subscription_name, const std::string& publisher_name)
    : Node("hand_eye_transform_publisher")
    {
        RCLCPP_INFO(this->get_logger(), "Start hand eye transform publisher");

        this->declare_parameter(PARAM_TF2_HAND_FRAME_NAME, "tcp_frame");
        this->declare_parameter(PARAM_TF2_EYE_FRAME_NAME, "eye_frame");
        this->declare_parameter(PARAM_TF2_TRANLSATION_X, 0.0);
        this->declare_parameter(PARAM_TF2_TRANLSATION_Y, 0.0);
        this->declare_parameter(PARAM_TF2_TRANLSATION_Z, 0.0);
        this->declare_parameter(PARAM_TF2_ROTATION_RAD_X, 0.0);
        this->declare_parameter(PARAM_TF2_ROTATION_RAD_Y, 0.0);
        this->declare_parameter(PARAM_TF2_ROTATION_RAD_Z, 0.0);

        this->print_params();

        tf_static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);

        // Publish static transforms once at startup
        this->make_transforms();
    }

  private:
    void print_params() const
    {
      std::vector<std::string> param_names = 
      {
        PARAM_TF2_HAND_FRAME_NAME, 
        PARAM_TF2_EYE_FRAME_NAME,
        PARAM_TF2_TRANLSATION_X,
        PARAM_TF2_TRANLSATION_Y,
        PARAM_TF2_TRANLSATION_Z,
        PARAM_TF2_ROTATION_RAD_X,
        PARAM_TF2_ROTATION_RAD_Y,
        PARAM_TF2_ROTATION_RAD_Z
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

    void make_transforms()
    {
      geometry_msgs::msg::TransformStamped t;

      t.header.stamp = this->get_clock()->now();
      t.header.frame_id = get_parameter(PARAM_TF2_HAND_FRAME_NAME).as_string();
      t.child_frame_id = get_parameter(PARAM_TF2_EYE_FRAME_NAME).as_string();

      t.transform.translation.x = get_parameter(PARAM_TF2_TRANLSATION_X).as_double();
      t.transform.translation.y = get_parameter(PARAM_TF2_TRANLSATION_Y).as_double();
      t.transform.translation.z = get_parameter(PARAM_TF2_TRANLSATION_Z).as_double();

      tf2::Quaternion q;
      q.setRPY(
        get_parameter(PARAM_TF2_ROTATION_RAD_X).as_double(),
        get_parameter(PARAM_TF2_ROTATION_RAD_Y).as_double(),
        get_parameter(PARAM_TF2_ROTATION_RAD_Z).as_double()
      );

      t.transform.rotation.x = q.x();
      t.transform.rotation.y = q.y();
      t.transform.rotation.z = q.z();
      t.transform.rotation.w = q.w();

      tf_static_broadcaster_->sendTransform(t);
  }

  geometry_msgs::msg::Transform::Ptr hand_eye_transform_;
  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;
};

int main(int argc, char * argv[])
{
  std::string subscription_name = (argc >= 2) ? argv[1] : "/tof_point_cloud_pose_snapped";
  std::string publisher_name = (argc >= 3) ? argv[2] : "/tof_point_cloud_robot_coordinates";

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<HandEyeTransformPublisher>(subscription_name, publisher_name));
  rclcpp::shutdown();
  return 0;
}