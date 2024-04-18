#include "../include/Scene.h"

#include "../include/ObjectContainer.h"

void WzlPlanner::Scene::AddSceneObject(std::shared_ptr<SceneObject> sceneObject)
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

    // trigger ros node to add scene object to the planning scene
    auto request = std::make_shared<wzlscheduler_interfaces::srv::SceneObjectAdd::Request>();
    request->name = sceneObject->GetId();
    request->collisionobjectkey = sceneObject->GetCollisionObjectKey();
    
     while (!this->serviceSceenObjectAdd_->wait_for_service(1s)) 
     {
        if (!rclcpp::ok()) 
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return;
        }

        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = serviceSceenObjectAdd_->async_send_request(request);

    // Wait for the result.
    if (rclcpp::spin_until_future_complete(ObjectContainer::Get()->GetNode(), result) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        auto output = result.get()->result;

        if (output == 1)
        {
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Successfully to call service SceneObjectAdd");
        }
        else
        {
            std::string msg = "Error in call service SceneObjectAdd: " + std::to_string(output);
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), msg.c_str());
        }
    } 
    else 
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service SceneObjectAdd");
    }
}

std::shared_ptr<WzlPlanner::SceneObject> WzlPlanner::Scene::GetSceneObject(const std::string id) const
{
    if (sceneObjects_.count(id) > 0)
    {
        auto msg = std::string("Trying to call GetSceneObject with a non eisting scene object id: ") + id; 
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
}
