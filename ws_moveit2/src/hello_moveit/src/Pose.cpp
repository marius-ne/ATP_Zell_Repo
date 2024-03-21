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
    Set(pose.x, pose.y, pose.z, pose.rx, pose.ry, pose.rz);
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


void WzlPlanner::Transform::GetChildrenRecursive(std::vector<std::shared_ptr<Transform>> &collectedTransforms) const
{
    for (auto const& [key, val] : children_)
    {
        collectedTransforms.push_back(val);
        GetChildrenRecursive(collectedTransforms);
    }

    // old implementation withn childrens as list
    //for(auto&& child: children_)
    //{
    //    collectedTransforms.push_back(child);
    //    GetChildrenRecursive(collectedTransforms);
    //}
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