#ifndef POSE_HPP
#define POSE_HPP

#include "geometry_msgs/msg/transform.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/utils.h"
#include "rclcpp/rclcpp.hpp"
#include "tf2_eigen/tf2_eigen.hpp"

#include <map>

namespace WzlPlanner
{
    class Pose
    {

        public:
            RCLCPP_SMART_PTR_DEFINITIONS(WzlPlanner::Pose)

            Pose();
            Pose(Pose &copy);
            Pose(const double x, const double y, const double z);
            Pose(const double x, const double y, const double z,
                const double rx, const double ry, const double rz);
            Pose(const double x, const double y, const double z,
                const double i, const double j, const double k, const double w);
            Pose(const geometry_msgs::msg::Pose& pose);
            Pose(const geometry_msgs::msg::Transform& pose);

            void Set();
            void Set(const double x, const double y, const double z,
                const double rx, const double ry, const double rz);
            void Set(const double x, const double y, const double z,
                const double i, const double j, const double k, const double w);
            void Set(Pose &pose);

            void SetPositionX(const double x);
            void SetPositionY(const double y);
            void SetPositionZ(const double z);

            void SetPositionXYZ(const double x, const double y, const double z);

            void SetRotationX(const double rx);
            void SetRotationY(const double ry);
            void SetRotationZ(const double rz);

            void SetRotationXYZ(const double rx, const double ry, const double rz);

            void SetRotationI(const double i);
            void SetRotationJ(const double j);
            void SetRotationK(const double k);
            void SetRotationW(const double w);

            void SetRotationQuaternion(const double i, const double j, const double k, const double w);

            double GetPositionX() const { return x_; }
            double GetPositionY() const { return y_; }
            double GetPositionZ() const { return z_; }

            double GetRotationX() const{ return rx_; }
            double GetRotationY() const{ return ry_; }
            double GetRotationZ() const{ return rz_; }

            double GetRotationI() const { return i_; }
            double GetRotationJ() const { return j_; }
            double GetRotationK() const { return k_; }
            double GetRotationW() const { return w_; }

            void Reset() { this->isDirty = false; }
            bool IsDirty() const { return this->isDirty; }

            // Gets the Ros geometry msg as a relative transform (transform between this coordinate frame and it's parent)            
            geometry_msgs::msg::Transform GetGeometryMsgTransformFromPose() const;

            // Gets the ros geometry msg as an absolute pose (absolute pose in the world coordinate frame)
            geometry_msgs::msg::Pose GetGeometryMsgPoseFromPose() const;

        private:

            bool isDirty;
            geometry_msgs::msg::Transform transform_;

            double x_, y_, z_;
            double rx_, ry_, rz_;
            double i_, j_, k_, w_;

            void UpdatePosition();
            void UpdateRotationQuaternionFromEuler();
            void UpdateRotationEulerFromQuaternion();
            
    };

    class Transform : public std::enable_shared_from_this<Transform>
    {

        public:
            Transform(std::string id);
            Transform(std::string id, std::shared_ptr<Pose> pose);
            Transform(std::string id, std::shared_ptr<Pose> pose, std::shared_ptr<Transform> parent);
            Transform(std::string id, std::shared_ptr<Transform> parent);

            std::shared_ptr<Pose> GetPoseRelative() const { return poseRelative_; }
            std::shared_ptr<Pose> GetPoseAbsolute() const { return poseAbsolute_; }
            std::map<std::string, std::shared_ptr<Transform>> GetChildren() const { return children_; }
            void GetChildrenRecursive(std::vector<std::shared_ptr<Transform>>& collectedTransforms) const;
            std::string GetId() const { return id_; }
            std::shared_ptr<Transform> GetParent() const { return parent_; }

            void SetParent(const std::shared_ptr<Transform> parent);

            // Gets the Ros geometry msg as a relative transform (transform between this coordinate frame and it's parent)            
            geometry_msgs::msg::Transform GetGeometryMsgTransform() const;

            // Gets the ros geometry msg as an absolute pose (absolute pose in the world coordinate frame)
            geometry_msgs::msg::Pose GetGeometryMsgPose() const;

            // Updates the absolute poses of this Transform and all it's children
            void Update(const std::shared_ptr<Transform> parent = nullptr);
            void UpdateRelative(const std::shared_ptr<Transform> parent = nullptr);

            void Print(int depth = 0);

        private:
            std::string id_;
            std::map<std::string, std::shared_ptr<Transform>> children_;
            std::shared_ptr<Transform> parent_;
            std::shared_ptr<Pose> poseRelative_;
            std::shared_ptr<Pose> poseAbsolute_;
            Eigen::Matrix4d baseTransform_; // transform of the coordinate base (in relation to it's parent coordinate system)

    };

    class TransformBroadcaster
    {
        public:
            TransformBroadcaster(const rclcpp::Node::SharedPtr node)
            {
                clock_ = node->get_clock();
                tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*node);
            }

            void Broadcast(std::shared_ptr<Transform> transformBase);

        private:
            void GetChildrenRecursive(std::shared_ptr<Transform> baseTransform, std::vector<std::shared_ptr<Transform>>& collectedTransforms);

            void MakeTransform(geometry_msgs::msg::TransformStamped& t,
                std::string parentFrame, std::string childFrame,
                float x, float y, float z,
                float roll, float pitch, float yaw);

            std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
            rclcpp::Clock::SharedPtr clock_;
    };
    
} // namespace WzlPlanner

#endif // POSE_HPP