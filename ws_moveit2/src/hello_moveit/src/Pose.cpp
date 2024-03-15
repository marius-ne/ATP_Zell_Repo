#include "Pose.h"

WzlPlanner::Pose::Pose()
{
    this->SetPositionXYZ(0, 0, 0);
    this->SetRotationXYZ(0, 0, 0);
}

WzlPlanner::Pose::Pose(Pose &copy)
{
    this->x = copy.x;
    this->y = copy.y;
    this->z = copy.z;

    this->rx = copy.rx;
    this->ry = copy.ry;
    this->rz = copy.rz;

    this->i = copy.i;
    this->j = copy.j;
    this->k = copy.k;
    this->w = copy.w;
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
    transform.translation.x = x;
    transform.translation.y = y;
    transform.translation.z = z;

    isDirty = true;
}

void WzlPlanner::Pose::UpdateRotationQuaternionFromEuler()
{
    tf2::Quaternion q;
    q.setRPY(rx, ry, rz);

    i = q.getX();
    j = q.getY();
    k = q.getZ();
    w = q.getW();
    
    transform.rotation.x = q.getX();
    transform.rotation.y = q.getY();
    transform.rotation.z = q.getZ();
    transform.rotation.w = q.getW();

    isDirty = true;
/*
    // test stuff with parent/children transforms
    tf2::Transform tr1;
    tf2::Transform tr2;
    geometry_msgs::msg::TransformStamped trStamped;
    

    tf2::doTransform<tf2::Transform>(tr1, tr2, trStamped);



def quaternion_mult(q,r):
    return [r[0]*q[0]-r[1]*q[1]-r[2]*q[2]-r[3]*q[3],
            r[0]*q[1]+r[1]*q[0]-r[2]*q[3]+r[3]*q[2],
            r[0]*q[2]+r[1]*q[3]+r[2]*q[0]-r[3]*q[1],
            r[0]*q[3]-r[1]*q[2]+r[2]*q[1]+r[3]*q[0]]

def point_rotation_by_quaternion(point,q):
    r = [0]+point
    q_conj = [q[0],-1*q[1],-1*q[2],-1*q[3]]
    return quaternion_mult(quaternion_mult(q,r),q_conj)[1:]
    */
}

void WzlPlanner::Pose::UpdateRotationEulerFromQuaternion()
{
    tf2::Quaternion q(tf2::Vector3(i, j, k), w);
    tf2::getEulerYPR(q, rx, ry, rz);

    isDirty = true;
}

void WzlPlanner::Transform::AddChild(const std::shared_ptr<Transform> child)
{
    children.push_back(child);
    child->Update(std::shared_ptr<Transform>(this));
}

void WzlPlanner::Transform::Update(const std::shared_ptr<Transform> parent)
{
    for(auto&& elem: this->children)
        elem->Update(std::shared_ptr<Transform>(this));
        // todo
}
