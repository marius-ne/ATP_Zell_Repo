#ifndef POSE_HPP
#define POSE_HPP

#include "geometry_msgs/msg/transform.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2/utils.h"

#include <memory>

namespace WzlPlanner
{
    class Transform
    {

        private:
            // the pose relative to the parent transform
            std::shared_ptr<Pose> poseRelative;

            // the pose in absolute world coordinates
            std::shared_ptr<Pose> poseAbsolute;

            std::vector<std::shared_ptr<Transform>> children;

        public:
            std::shared_ptr<Pose> GetPoseRelative() const { return this->poseRelative; }
            std::shared_ptr<Pose> GetPoseAbsolute() const { return this->poseAbsolute; }

            void AddChild(const std::shared_ptr<Transform> child);

            // Updates the absolute poses of this Transform and all it's children
            void Update(const std::shared_ptr<Transform> parent);
    };

    class Pose
    {

        public:
            Pose();
            Pose(Pose &copy);

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
} // namespace WzlPlanner

#endif // POSE_HPP