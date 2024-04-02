#ifndef OBJECTCONTAINER_HPP
#define OBJECTCONTAINER_HPP

#include <memory>

#include "IoInterface.h"
#include "Robot.h"
#include "Scene.h"

namespace WzlPlanner
{
    // songleton
    class ObjectContainer
    {
        private:
            std::shared_ptr<IoInterfaceBase> ioInterface_;
            std::shared_ptr<WzlPlanner::Robot> robot_;
            std::shared_ptr<WzlPlanner::Scene> scene_;
            std::shared_ptr<rclcpp::Node> node_;

            static ObjectContainer* singleton_;

            ObjectContainer() {}

        public:
            /**
             * Singletons should not be cloneable.
             */
            ObjectContainer(ObjectContainer &other) = delete;
            /**
             * Singletons should not be assignable.
             */
            void operator=(const ObjectContainer &) = delete;

            void Initialize(
                std::shared_ptr<IoInterfaceBase> ioInterface,
                std::shared_ptr<WzlPlanner::Robot> robot,
                std::shared_ptr<WzlPlanner::Scene> scene,
                std::shared_ptr<rclcpp::Node> node)
            {
                ioInterface_ = ioInterface;
                robot_ = robot;
                scene_ = scene;
                node_ = node;
            }

            static ObjectContainer *Get();

            std::shared_ptr<IoInterfaceBase> GetioInterface() const { return ioInterface_; }
            std::shared_ptr<WzlPlanner::Robot> GetRobot() const { return robot_; }
            std::shared_ptr<WzlPlanner::Scene> GetScene() const { return scene_; }
            std::shared_ptr<rclcpp::Node> GetNode() const { return node_; }
 
    };

} // namepspace

#endif