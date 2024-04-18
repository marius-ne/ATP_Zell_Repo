#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <map>

#include "Robot.h"
#include "SceneObjects/SceneObjectInclude.h"
#include "Pose.h"

#include "wzlscheduler_interfaces/srv/scene_object_add.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_remove.hpp"
#include "wzlscheduler_interfaces/srv/scene_object_set_pose.hpp"


namespace WzlPlanner
{
    class Scene
    {

        public:
            Scene(std::shared_ptr<Robot> robot) 
            { 
                robot_ = robot;
                transformBase_ = std::make_shared<Transform>("World");
            }

            std::shared_ptr<WzlPlanner::Transform> GetTransformBase() const { return transformBase_; }

            void AddSceneObject(std::shared_ptr<SceneObject> sceneObject);
            std::shared_ptr<SceneObject> GetSceneObject(const std::string id) const;
            void RemoveSceneObject(const std::shared_ptr<SceneObject> sceneObject);
            void Update() { transformBase_->Update(); }


        private:
            std::shared_ptr<WzlPlanner::Transform> transformBase_;
            std::shared_ptr<Robot> robot_;
            std::map<std::string, std::shared_ptr<SceneObject>> sceneObjects_;

            rclcpp::Client<wzlscheduler_interfaces::srv::SceneObjectAdd>::SharedPtr serviceSceenObjectAdd_;
            rclcpp::Client<wzlscheduler_interfaces::srv::SceneObjectRemove>::SharedPtr serviceSceenObjectRemove_;
            rclcpp::Client<wzlscheduler_interfaces::srv::SceneObjectSetPose>::SharedPtr serviceSceenObjectSetPose_;

    };
} // namespace WzlPlanner

#endif // SCENE_HPP