#include "../include/Scene.h"

#include "../include/ObjectContainer.h"
#include "Scene.h"

void WzlPlanner::Scene::AddSceneObject(const std::shared_ptr<SceneObject> sceneObject, const std::shared_ptr<Pose> poseAbsolute)
{
    if (sceneObjects_.count(sceneObject->GetId()) > 0)
    {
        auto msg = std::string("Can't add scene object to scene with the key '") 
            + sceneObject->GetId() 
            + std::string("': Key already exists."); 

        RCLCPP_WARN(rclcpp::get_logger("rclcpp"), msg.c_str());
        
        return;
    }

    sceneObjects_.insert({sceneObject->GetId(), sceneObject});
    sceneObject->InitializeTransform(this->transformBase_);
    sceneObject->GetTransform()->GetPoseRelative()->Set(*poseAbsolute.get());
    sceneObject->GetTransform()->GetPoseAbsolute()->Set(*poseAbsolute.get());

    // trigger ros node to add scene object to the planning scene

    auto request = wzlscheduler_interfaces::msg::SceneObjectAdd();
    request.name = sceneObject->GetId();
    request.collisionobjectkey = sceneObject->GetCollisionObjectKey();
    request.coordinates = sceneObject->GetTransform()->GetGeometryMsgPose();
    
    publisherSceenObjectAdd_->publish(request);
}

std::shared_ptr<WzlPlanner::SceneObject> WzlPlanner::Scene::GetSceneObject(const std::string id) const
{
    if (sceneObjects_.count(id) > 0)
    {
        auto msg = std::string("Trying to call GetSceneObject with a non existing scene object id: ") + id; 
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), msg.c_str());

        return nullptr;
    }

    return sceneObjects_.at(id);
}

void WzlPlanner::Scene::RemoveSceneObject(const std::shared_ptr<SceneObject> sceneObject)
{
    if (sceneObjects_.count(sceneObject->GetId()) == 0)
    {
        auto msg = std::string("Can't delete scene object to scene with the key '") 
            + sceneObject->GetId() 
            + std::string("': No objct with given key in scene existent."); 

        RCLCPP_WARN(rclcpp::get_logger("rclcpp"), msg.c_str());

        return;
    }

    sceneObject->GetTransform()->SetParent(nullptr);
    sceneObjects_.erase(sceneObject->GetId());

    // trigger ros node to remove scene object from the planning scene
    auto request = wzlscheduler_interfaces::msg::SceneObjectRemove();
    request.name = sceneObject->GetId();

    publisherSceenObjectRemove_->publish(request);
}


void WzlPlanner::Scene::SceneObjectSetPositionAbsolute(const std::shared_ptr<SceneObject> sceneObject, const std::shared_ptr<Pose> pose)
{
    sceneObject->GetTransform()->GetPoseAbsolute()->Set(*pose.get());
    sceneObject->GetTransform()->GetParent()->Update();

    SendSceneObjectPoseService(sceneObject);
}

void WzlPlanner::Scene::SceneObjectSetPositionRelative(const std::shared_ptr<SceneObject> sceneObject, const std::shared_ptr<Pose> pose)
{
    sceneObject->GetTransform()->GetPoseRelative()->Set(*pose.get());
    sceneObject->GetTransform()->GetParent()->Update();

    SendSceneObjectPoseService(sceneObject);
}

void WzlPlanner::Scene::SendSceneObjectPoseService(const std::shared_ptr<WzlPlanner::SceneObject> sceneObject)
{
    // trigger ros node to move scene object to the absolute target pose
    auto request = wzlscheduler_interfaces::msg::SceneObjectSetPose();
    request.name = sceneObject->GetId();
    request.coordinates = sceneObject->GetTransform()->GetGeometryMsgPose();
}
