#include "../include/Pose.h"
#include "Pose.h"

WzlPlanner::Pose::Pose()
{
    this->Set();
}

void WzlPlanner::Pose::Set()
{
    SetPositionXYZ(0, 0, 0);
    SetRotationXYZ(0, 0, 0);
}

void WzlPlanner::Pose::Set(const double x, const double y, const double z, 
    const double rx, const double ry, const double rz)
{
    SetPositionXYZ(x, y, z);
    SetRotationXYZ(rx, ry, rz);
}

void WzlPlanner::Pose::Set(const double x, const double y, const double z, 
    const double i, const double j, const double k, const double w)
{
    SetPositionXYZ(x, y, z);
    SetRotationQuaternion(i, j, k, w);
}

void WzlPlanner::Pose::Set(Pose &pose)
{
    Set(pose.x_, pose.y_, pose.z_, pose.rx_, pose.ry_, pose.rz_);
}

WzlPlanner::Pose::Pose(Pose &copy)
{
    this->x_ = copy.x_;
    this->y_ = copy.y_;
    this->z_ = copy.z_;

    this->rx_ = copy.rx_;
    this->ry_ = copy.ry_;
    this->rz_ = copy.rz_;

    this->i_ = copy.i_;
    this->j_ = copy.j_;
    this->k_ = copy.k_;
    this->w_ = copy.w_;
}

WzlPlanner::Pose::Pose(const double x, const double y, const double z)
{
    this->SetPositionXYZ(x, y, z);
    this->SetRotationXYZ(0, 0, 0);
}

WzlPlanner::Pose::Pose(const double x, const double y, const double z, const double rx, const double ry, const double rz)
{
    this->Set(x, y, z, rx, ry, rz);
}

WzlPlanner::Pose::Pose(const double x, const double y, const double z, const double i, const double j, const double k, const double w)
{
    this->Set(x, y, z, i, j, k, w);
}

WzlPlanner::Pose::Pose(const geometry_msgs::msg::Pose& pose)
{
    this->Set(pose.position.x,
        pose.position.y,
        pose.position.z,
        pose.orientation.x,
        pose.orientation.y,
        pose.orientation.z,
        pose.orientation.w);
}

WzlPlanner::Pose::Pose(const geometry_msgs::msg::Transform& transform)
{
    this->Set(transform.translation.x,
        transform.translation.y,
        transform.translation.z,
        transform.rotation.x,
        transform.rotation.y,
        transform.rotation.z,
        transform.rotation.w);
}

void WzlPlanner::Pose::SetPositionX(const double x)
{
    this->x_ = x;
    UpdatePosition();
}

void WzlPlanner::Pose::SetPositionY(const double y)
{
    this->y_ = y;
    UpdatePosition();
}

void WzlPlanner::Pose::SetPositionZ(const double z)
{
    this->z_ = z;
    UpdatePosition();
}

void WzlPlanner::Pose::SetPositionXYZ(const double x, const double y, const double z)
{
    this->x_ = x;
    this->y_ = y;
    this->z_ = z;

    UpdatePosition();
}

void WzlPlanner::Pose::SetRotationX(const double rx)
{
    this->rx_ = rx;
    this->UpdateRotationQuaternionFromEuler();
}


void WzlPlanner::Pose::SetRotationY(const double ry)
{
    this->ry_ = ry;
    this->UpdateRotationQuaternionFromEuler();
}

void WzlPlanner::Pose::SetRotationZ(const double rz)
{
    this->rz_ = rz;
    this->UpdateRotationQuaternionFromEuler();
}

void WzlPlanner::Pose::SetRotationXYZ(double rx, double ry, double rz)
{
    this->rx_ = rx;
    this->ry_ = ry;
    this->rz_ = rz;
    UpdateRotationQuaternionFromEuler();
}

void WzlPlanner::Pose::SetRotationI(const double i)
{
    this->i_ = i;
    this->UpdateRotationEulerFromQuaternion();
}

void WzlPlanner::Pose::SetRotationJ(const double j)
{
    this->j_ = j;
    this->UpdateRotationEulerFromQuaternion();
}

void WzlPlanner::Pose::SetRotationK(const double k)
{
    this->k_ = k;
    this->UpdateRotationEulerFromQuaternion();
}

void WzlPlanner::Pose::SetRotationW(const double w)
{
    this->w_ = w;
    this->UpdateRotationEulerFromQuaternion();
}

void WzlPlanner::Pose::SetRotationQuaternion(const double i, const double j, const double k, const double w)
{
    this->i_ = i;
    this->j_ = j;
    this->k_ = k;
    this->w_ = w;

    UpdateRotationEulerFromQuaternion();
}

geometry_msgs::msg::Transform WzlPlanner::Pose::GetGeometryMsgTransformFromPose() const
{
    auto transform = geometry_msgs::msg::Transform();
    transform.translation.x = x_;
    transform.translation.y = y_;
    transform.translation.z = z_;

    tf2::Quaternion q;
    q.setRPY(rx_, ry_, rz_);

    transform.rotation.x = q.getX();
    transform.rotation.y = q.getY();
    transform.rotation.z = q.getZ();
    transform.rotation.w = q.getW();

    return transform;
}


geometry_msgs::msg::Pose WzlPlanner::Pose::GetGeometryMsgPoseFromPose() const
{
    auto pose = geometry_msgs::msg::Pose();
    pose.position.x = x_;
    pose.position.y = y_;
    pose.position.z = z_;

    tf2::Quaternion q;
    q.setRPY(rx_, ry_, rz_);

    pose.orientation.x = q.getX();
    pose.orientation.y = q.getY();
    pose.orientation.z = q.getZ();
    pose.orientation.w = q.getW();

    return pose;
}

void WzlPlanner::Pose::UpdatePosition()
{
    transform_.translation.x = x_;
    transform_.translation.y = y_;
    transform_.translation.z = z_;

    isDirty = true;
}

void WzlPlanner::Pose::UpdateRotationQuaternionFromEuler()
{
    tf2::Quaternion q;
    q.setRPY(rx_, ry_, rz_);

    i_= q.getX();
    j_= q.getY();
    k_= q.getZ();
    w_= q.getW();
    
    transform_.rotation.x = q.getX();
    transform_.rotation.y = q.getY();
    transform_.rotation.z = q.getZ();
    transform_.rotation.w = q.getW();

    isDirty = true;
}

void WzlPlanner::Pose::UpdateRotationEulerFromQuaternion()
{
    tf2::Quaternion q(tf2::Vector3(i_, j_, k_), w_);
    tf2::getEulerYPR(q, rx_, ry_, rz_);

    isDirty = true;
}


void WzlPlanner::Transform::GetChildrenRecursive(std::vector<std::shared_ptr<Transform>> &collectedTransforms) const
{
    for (auto const& [key, val] : children_)
    {
        collectedTransforms.push_back(val);
        GetChildrenRecursive(collectedTransforms);
    }
}

Eigen::Affine3d create_rotation_matrix(double ax, double ay, double az) 
{
  auto rx = Eigen::Affine3d(Eigen::AngleAxisd(ax, Eigen::Vector3d(1, 0, 0)));
  auto ry = Eigen::Affine3d(Eigen::AngleAxisd(ay, Eigen::Vector3d(0, 1, 0)));
  auto rz = Eigen::Affine3d(Eigen::AngleAxisd(az, Eigen::Vector3d(0, 0, 1)));
  return rz * ry * rx;
}



void WzlPlanner::Transform::Update(const std::shared_ptr<Transform> parent)
{
    Eigen::Matrix4d parentBaseTransform;
    auto parentRotationX = 0.0;
    auto parentRotationY = 0.0;
    auto parentRotationZ = 0.0;
    
    if (parent == nullptr)
    {
        parentBaseTransform = Eigen::Matrix4d::Identity();
    }
    else
    {
        parentBaseTransform = parent->baseTransform_;
        parentRotationX = parent->poseAbsolute_->GetRotationX();
        parentRotationY = parent->poseAbsolute_->GetRotationY();
        parentRotationZ = parent->poseAbsolute_->GetRotationZ();
    }

    auto relX = poseRelative_->GetPositionX();
    auto relY = poseRelative_->GetPositionY();
    auto relZ = poseRelative_->GetPositionZ();

    Eigen::Vector4d positionRelative(relX, relY, relZ, 1);
    Eigen::Vector4d positionAbsolute = parentBaseTransform * positionRelative;

    poseAbsolute_->Set(
        positionAbsolute.x(),
        positionAbsolute.y(),
        positionAbsolute.z(),
        parentRotationX + poseRelative_->GetRotationX(),
        parentRotationY + poseRelative_->GetRotationY(),
        parentRotationZ + poseRelative_->GetRotationZ()
    );

    Eigen::Affine3d r = create_rotation_matrix(poseAbsolute_->GetRotationX(), poseAbsolute_->GetRotationY(), poseAbsolute_->GetRotationZ());
    Eigen::Affine3d t(Eigen::Translation3d(Eigen::Vector3d(positionAbsolute.x(), positionAbsolute.y(), positionAbsolute.z())));
    baseTransform_ = (t * r).matrix(); // Create 4x4 affine tranformation matrix (as a reference base coordinate system for a transformed point)

    // update all children
    for (auto&& child: children_)
    {
        child.second->Update(shared_from_this());
    }
}

void WzlPlanner::Transform::UpdateRelative(const std::shared_ptr<Transform> parent)
{
    Eigen::Matrix4d parentBaseTransform;
    auto parentRotationX = 0.0;
    auto parentRotationY = 0.0;
    auto parentRotationZ = 0.0;

    if (parent == nullptr)
    {
        parentBaseTransform = Eigen::Matrix4d::Identity();
    }
    else
    {
        parentBaseTransform = parent->baseTransform_;
        parentRotationX = parent->poseAbsolute_->GetRotationX();
        parentRotationY = parent->poseAbsolute_->GetRotationY();
        parentRotationZ = parent->poseAbsolute_->GetRotationZ();
    }    
}

void WzlPlanner::Transform::Print(int depth)
{
    std::string indent = "";

    for (int i = 0; i < depth; i++)
    {
        indent.append("  ");
    }

    std::cout << indent.c_str() << id_ << ", Children: " << children_.size() << ", Abs: X:" << poseAbsolute_->GetPositionX() 
            << ", Y: " << poseAbsolute_->GetPositionY()
            << ", Z: " << poseAbsolute_->GetPositionZ()
            << ", RotX: " << poseAbsolute_->GetRotationX()
            << ", RotY: " << poseAbsolute_->GetRotationY()
            << ", RotZ: " << poseAbsolute_->GetRotationZ()
            << ", ; Rel: X:" << poseRelative_->GetPositionX() 
            << ", Y: " << poseRelative_->GetPositionY()
            << ", Z: " << poseRelative_->GetPositionZ()
            << ", RotX: " << poseRelative_->GetRotationX()
            << ", RotY: " << poseRelative_->GetRotationY()
            << ", RotZ: " << poseRelative_->GetRotationZ()
    << std::endl;

    for (auto&& child: children_)
    {
        child.second->Print(depth + 1);
    }
}

WzlPlanner::Transform::Transform(std::string id)
{
    id_ = id;
    poseRelative_ = std::make_shared<Pose>();
    poseAbsolute_ = std::make_shared<Pose>();
}

WzlPlanner::Transform::Transform(std::string id, std::shared_ptr<Pose> pose)
{
    id_ = id;
    
    poseRelative_ = pose;
    poseAbsolute_ = std::make_shared<Pose>();
    poseAbsolute_->Set(*poseRelative_.get());
}

WzlPlanner::Transform::Transform(std::string id, std::shared_ptr<Pose> pose, std::shared_ptr<Transform> parent)
{
    id_ = id;
    poseRelative_ = pose;
    poseAbsolute_ = std::make_shared<Pose>();;
    parent->children_.insert({id, shared_from_this()});
    parent_ = parent;
    parent->Update();
}

WzlPlanner::Transform::Transform(std::string id, std::shared_ptr<Transform> parent)
{
    id_ = id;
    poseRelative_ = std::make_shared<Pose>();
    poseAbsolute_ = std::make_shared<Pose>();
    parent->children_.insert({id, shared_from_this()});
    parent_ = parent;
    parent->Update();
}

void WzlPlanner::Transform::SetParent(const std::shared_ptr<Transform> parent)
{
    if (parent_ != nullptr)
    {
        parent_->children_.erase(this->id_);
    }

    if (parent != nullptr)
    {
        if (parent->children_.count(id_) > 0)
        {
            std::cout << "Transform with id '" << parent_->GetId() << "' already has a child with the id '" << id_ << "'." << std::endl; 
            return;
        }

        parent->children_.insert({id_, shared_from_this()});
    }

    parent->Update();
}

geometry_msgs::msg::Transform WzlPlanner::Transform::GetGeometryMsgTransform() const
{
    return GetPoseRelative()->GetGeometryMsgTransformFromPose();
}

geometry_msgs::msg::Pose WzlPlanner::Transform::GetGeometryMsgPose() const
{
    return GetPoseAbsolute()->GetGeometryMsgPoseFromPose();
}

void WzlPlanner::TransformBroadcaster::Broadcast(std::shared_ptr<Transform> transformBase, rclcpp::Clock &clock)
{
    std::vector<std::shared_ptr<Transform>> allTransforms;
    std::vector<geometry_msgs::msg::TransformStamped> tfTransforms;

    GetChildrenRecursive(transformBase, allTransforms);

    // construct tf transforms
    for (auto&& transform: allTransforms)
    {
        if (transform->GetParent() == nullptr)
        {
            continue;
        }

        auto pose = transform->GetPoseRelative();
        geometry_msgs::msg::TransformStamped tfTransform;
        MakeTransform(tfTransform, clock, transformBase->GetId(), transform->GetId(),
          pose->GetPositionX(),
          pose->GetPositionY(),
          pose->GetPositionZ(),
          pose->GetRotationX(),
          pose->GetRotationY(),
          pose->GetRotationZ());

        tfTransforms.push_back(std::move(tfTransform));
    }

    // broadcast
    this->tf_broadcaster_->sendTransform(tfTransforms);
}

void WzlPlanner::TransformBroadcaster::MakeTransform(geometry_msgs::msg::TransformStamped &t, rclcpp::Clock& clock, 
    std::string parentFrame, std::string childFrame, 
    float x, float y, float z, 
    float roll, float pitch, float yaw)
{
    t.header.stamp = clock.now();
    t.header.frame_id = parentFrame;
    t.child_frame_id = childFrame;
    
    t.transform.translation.x = x;
    t.transform.translation.y = y;
    t.transform.translation.z = z;
    tf2::Quaternion q;
    q.setRPY(roll, pitch, yaw);
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();
}

void WzlPlanner::TransformBroadcaster::GetChildrenRecursive(std::shared_ptr<Transform> baseTransform, std::vector<std::shared_ptr<Transform>> &collectedTransforms)
{
    collectedTransforms.push_back(baseTransform);

    for(auto&& child: baseTransform->GetChildren())
    {
        collectedTransforms.push_back(child.second);
        child.second->GetChildrenRecursive(collectedTransforms);
    }
}