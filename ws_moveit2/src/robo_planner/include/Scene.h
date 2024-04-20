#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <map>

#include "Robot.h"
#include "SceneObjects/SceneObjectInclude.h"
#include "Part.h"
#include "Pose.h"

#include "wzlscheduler_interfaces/msg/scene_object_add.hpp"
#include "wzlscheduler_interfaces/msg/scene_object_remove.hpp"
#include "wzlscheduler_interfaces/msg/scene_object_set_pose.hpp"


namespace WzlPlanner
{
    class Scene
    {

        public:
            Scene(const std::shared_ptr<Robot> robot, rclcpp::Node::SharedPtr node) 
            { 
                robot_ = robot;
                transformBase_ = std::make_shared<Transform>("World");

                publisherSceenObjectAdd_ = node->create_publisher<wzlscheduler_interfaces::msg::SceneObjectAdd>("SceneObjectAdd", 10);
                publisherSceenObjectRemove_ = node->create_publisher<wzlscheduler_interfaces::msg::SceneObjectRemove>("SceneObjectRemove", 10);
                publisherSceenObjectSetPose_ = node->create_publisher<wzlscheduler_interfaces::msg::SceneObjectSetPose>("SceneObjectSetPose", 10);
            }

            std::shared_ptr<WzlPlanner::Transform> GetTransformBase() const { return transformBase_; }

            void AddSceneObject(const std::shared_ptr<SceneObject> sceneObject, const std::shared_ptr<Pose> poseAbsolute);
            std::shared_ptr<SceneObject> GetSceneObject(const std::string id) const;
            void RemoveSceneObject(const std::shared_ptr<SceneObject> sceneObject);

            void SceneObjectSetPositionAbsolute(const std::shared_ptr<SceneObject> sceneObject, const std::shared_ptr<Pose> poseAbsolute);
            void SceneObjectSetPositionRelative(const std::shared_ptr<SceneObject> sceneObject, const std::shared_ptr<Pose> poseRelative);

            void Update() { transformBase_->Update(); }

        private:
            void SendSceneObjectPoseService(const std::shared_ptr<WzlPlanner::SceneObject> sceneObject);

            std::shared_ptr<WzlPlanner::Transform> transformBase_;
            std::shared_ptr<Robot> robot_;
            std::map<std::string, std::shared_ptr<SceneObject>> sceneObjects_;

            rclcpp::Publisher<wzlscheduler_interfaces::msg::SceneObjectAdd>::SharedPtr publisherSceenObjectAdd_;
            rclcpp::Publisher<wzlscheduler_interfaces::msg::SceneObjectRemove>::SharedPtr publisherSceenObjectRemove_;
            rclcpp::Publisher<wzlscheduler_interfaces::msg::SceneObjectSetPose>::SharedPtr publisherSceenObjectSetPose_;
    };
} // namespace WzlPlanner

#endif // SCENE_HPP