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
            Scene(const std::shared_ptr<Robot> robot, const rclcpp::Node::SharedPtr node, const std::string fixedFrameName = "map") 
            { 
                robot_ = robot;
                transformBase_ = std::make_shared<Transform>(fixedFrameName);
                transform_broadcaster_ = std::make_shared<TransformBroadcaster>(node);

                publisherSceenObjectAdd_ = node->create_publisher<wzlscheduler_interfaces::msg::SceneObjectAdd>("scene_object_add", 10);
                publisherSceenObjectRemove_ = node->create_publisher<wzlscheduler_interfaces::msg::SceneObjectRemove>("scene_object_remove", 10);
                publisherSceenObjectSetPose_ = node->create_publisher<wzlscheduler_interfaces::msg::SceneObjectSetPose>("scene_object_set_pose", 10);

                timer_update_= node->create_wall_timer(100ms, std::bind(&Scene::update_timer_callback, this));
            }

            std::shared_ptr<WzlPlanner::Transform> GetTransformBase() const { return transformBase_; }

            void AddSceneObject(const std::shared_ptr<SceneObject> sceneObject, const std::shared_ptr<Pose> poseAbsolute);
            std::shared_ptr<SceneObject> GetSceneObject(const std::string id) const;
            void RemoveSceneObject(const std::shared_ptr<SceneObject> sceneObject);

            void SceneObjectSetPositionAbsolute(const std::shared_ptr<SceneObject> sceneObject, const std::shared_ptr<Pose> poseAbsolute);
            void SceneObjectSetPositionRelative(const std::shared_ptr<SceneObject> sceneObject, const std::shared_ptr<Pose> poseRelative);

            void Update() { transformBase_->Update(); }

            void update_timer_callback() 
            { 
                this->Update(); 
                transform_broadcaster_->Broadcast(transformBase_);
            }

        private:
            void SendSceneObjectPoseService(const std::shared_ptr<WzlPlanner::SceneObject> sceneObject);

            rclcpp::Node::SharedPtr node_;
            std::shared_ptr<WzlPlanner::Transform> transformBase_;
            std::shared_ptr<Robot> robot_;
            std::map<std::string, std::shared_ptr<SceneObject>> sceneObjects_;
            rclcpp::TimerBase::SharedPtr timer_update_;
            std::shared_ptr<TransformBroadcaster> transform_broadcaster_;

            rclcpp::Publisher<wzlscheduler_interfaces::msg::SceneObjectAdd>::SharedPtr publisherSceenObjectAdd_;
            rclcpp::Publisher<wzlscheduler_interfaces::msg::SceneObjectRemove>::SharedPtr publisherSceenObjectRemove_;
            rclcpp::Publisher<wzlscheduler_interfaces::msg::SceneObjectSetPose>::SharedPtr publisherSceenObjectSetPose_;
    };
} // namespace WzlPlanner

#endif // SCENE_HPP