#ifndef POSE_HPP
#define POSE_HPP

#include "geometry_msgs/msg/transform.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2/utils.h"

namespace WzlPlanner
{
    class Pose
    {

        public:
            Pose();

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

        private:

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