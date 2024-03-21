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
            Pose();
            Pose(Pose &copy);

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

            double GetPositionX() const { return x; }
            double GetPositionY() const { return y; }
            double GetPositionZ() const { return z; }

            double GetRotationX() const{ return rx; }
            double GetRotationY() const{ return ry; }
            double GetRotationZ() const{ return rz; }

            double GetRotationI() const { return i; }
            double getRotationJ() const { return j; }
            double GetRotationK() const { return k; }
            double GetRotationW() const { return w; }

            void Reset() { this->isDirty = false; }
            bool IsDirty() const { return this->isDirty; }

        private:

            bool isDirty;
            geometry_msgs::msg::Transform transform;

            double x, y, z;
            double rx, ry, rz;
            double i, j, k, w;

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
            TransformBroadcaster(rclcpp::Node& node);

            void Broadcast(std::shared_ptr<Transform> transformBase, rclcpp::Clock& clock);

        private:
            std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

            void GetChildrenRecursive(std::shared_ptr<Transform> baseTransform, std::vector<std::shared_ptr<Transform>>& collectedTransforms);

            void MakeTransform(geometry_msgs::msg::TransformStamped& t, rclcpp::Clock& clock,
                std::string parentFrame, std::string childFrame,
                float x, float y, float z,
                float roll, float pitch, float yaw);
    };
    
} // namespace WzlPlanner

#endif // POSE_HPP