#include "Pose.h"

WzlPlanner::Pose::Pose()
{
    this->SetPositionXYZ(0, 0, 0);
    this->SetRotationXYZ(0, 0, 0);
}

void WzlPlanner::Pose::SetPositionX(const double x)
{
    this->x = x;
    UpdatePosition();
}

void WzlPlanner::Pose::SetPositionY(const double y)
{
    this->y = y;
    UpdatePosition();
}

void WzlPlanner::Pose::SetPositionZ(const double z)
{
    this->z = z;
    UpdatePosition();
}

void WzlPlanner::Pose::SetPositionXYZ(const double x, const double y, const double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    UpdatePosition();
}

void WzlPlanner::Pose::SetRotationX(const double rx)
{
    this->rx = rx;
    this->UpdateRotationQuaternionFromEuler();
}


void WzlPlanner::Pose::SetRotationY(const double ry)
{
    this->ry = ry;
    this->UpdateRotationQuaternionFromEuler();
}

void WzlPlanner::Pose::SetRotationZ(const double rz)
{
    this->rz = rz;
    this->UpdateRotationQuaternionFromEuler();
}

void WzlPlanner::Pose::SetRotationXYZ(double rx, double ry, double rz)
{
    this->rx = rx;
    this->ry = ry;
    this->rz = rz;
    UpdateRotationQuaternionFromEuler();
}

void WzlPlanner::Pose::SetRotationI(const double i)
{
    this->i = i;
    this->UpdateRotationEulerFromQuaternion();
}

void WzlPlanner::Pose::SetRotationJ(const double j)
{
    this->j = j;
    this->UpdateRotationEulerFromQuaternion();
}

void WzlPlanner::Pose::SetRotationK(const double k)
{
    this->k = k;
    this->UpdateRotationEulerFromQuaternion();
}

void WzlPlanner::Pose::SetRotationW(const double w)
{
    this->w = w;
    this->UpdateRotationEulerFromQuaternion();
}

void WzlPlanner::Pose::SetRotationQuaternion(const double i, const double j, const double k, const double w)
{
    this->i = i;
    this->j = j;
    this->k = k;
    this->w = w;

    UpdateRotationEulerFromQuaternion();
}

void WzlPlanner::Pose::UpdatePosition()
{
    transform.translation.x = 0;
    transform.translation.y = 0;
    transform.translation.z = 0;
}

void WzlPlanner::Pose::UpdateRotationQuaternionFromEuler()
{
    tf2::Quaternion q;
    q.setRPY(rx, ry, rz);

    i = q.getX();
    j = q.getY();
    k = q.getZ();
    w = q.getW();
}

void WzlPlanner::Pose::UpdateRotationEulerFromQuaternion()
{
    tf2::Quaternion q(tf2::Vector3(i, j, k), w);
    tf2::getEulerYPR(q, rx, ry, rz);
}

