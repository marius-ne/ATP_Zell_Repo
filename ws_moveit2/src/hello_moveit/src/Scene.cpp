#include "Scene.h"

void WzlPlanner::Scene::AddSceneObject(std::shared_ptr<SceneObject> sceneObject)
{
    if (sceneObjects_.count(sceneObject->GetId()) > 0)
    {
        std::cout << "Can't add scene object to scene with the key '" << sceneObject->GetId() << "': Key already exists.\n";
        return;
    }

    sceneObjects_.insert({sceneObject->GetId(), sceneObject});
    // todos
    sceneObject->GetTransform()->SetParent(transformBase_);
}

void WzlPlanner::Scene::RemoveSceneObject(const std::shared_ptr<SceneObject> sceneObject)
{
    if (sceneObjects_.count(sceneObject->GetId()) == 0)
    {
        std::cout << "Can't delete scene object to scene with the key '" << sceneObject->GetId() << "': No objct with given key in scene existent.\n";
        return;
    }

    sceneObject->GetTransform()->SetParent(nullptr);
    sceneObjects_.erase(sceneObject->GetId());
}
