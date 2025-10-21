#ifndef OBJECTCONTAINER_HPP
#define OBJECTCONTAINER_HPP

#include <memory>

#include "IoInterface.h"
#include "Robot.h"
#include "Scene.h"
#include "GridSnapper.h"

namespace WzlPlanner
{
    // songleton
    class ObjectContainer
    {
        private:
            std::shared_ptr<IoInterfaceBase> ioInterface_;
            std::shared_ptr<IoInterfaceBase> ioInterfaceModBus_;
            std::shared_ptr<IoInterfaceBase> ioInterfaceOpcUa_;
            std::shared_ptr<WzlPlanner::Robot> robot_;
            std::shared_ptr<WzlPlanner::Scene> scene_;
            std::shared_ptr<WzlPlanner::GridSnappper> gridSnapper_;
            std::shared_ptr<rclcpp::Node> node_;

            static ObjectContainer* singleton_;

            ObjectContainer() 
            {
                ioInterface_ = nullptr;
                ioInterfaceModBus_ = nullptr;
                ioInterfaceOpcUa_ = nullptr;
                robot_ = nullptr;
                scene_ = nullptr;
                gridSnapper_ = nullptr;
                node_ = nullptr;
            }

        public:
            /**
             * Singletons should not be cloneable.
             */
            ObjectContainer(ObjectContainer &other) = delete;
            /**
             * Singletons should not be assignable.
             */
            void operator=(const ObjectContainer &) = delete;

            // Original Initialize method - kept for backward compatibility
            void Initialize(
                const std::shared_ptr<IoInterfaceBase> ioInterface,
                const std::shared_ptr<WzlPlanner::Robot> robot,
                const std::shared_ptr<WzlPlanner::Scene> scene,
                const std::shared_ptr<rclcpp::Node> node)
            {
                ioInterface_ = ioInterface;
                robot_ = robot;
                scene_ = scene;
                node_ = node;
            }

            // New Initialize method - supports both interfaces
            void Initialize(
                const std::shared_ptr<IoInterfaceBase> ioInterfaceModBus,
                const std::shared_ptr<IoInterfaceBase> ioInterfaceOpcUa,
                const std::shared_ptr<WzlPlanner::Robot> robot,
                const std::shared_ptr<WzlPlanner::Scene> scene,
                const std::shared_ptr<rclcpp::Node> node)
            {
                ioInterfaceModBus_ = ioInterfaceModBus;
                ioInterfaceOpcUa_ = ioInterfaceOpcUa;
                ioInterface_ = ioInterfaceOpcUa; // Default to OpcUa for backward compatibility
                robot_ = robot;
                scene_ = scene;
                node_ = node;
            }

            void Initialize(const std::shared_ptr<WzlPlanner::GridSnappper> gridSnapper)
            {
                gridSnapper_ = gridSnapper;
            }

            static ObjectContainer *Get();

            std::shared_ptr<IoInterfaceBase> GetioInterface() const { return ioInterface_; }
            std::shared_ptr<IoInterfaceBase> GetIoInterfaceModBus() const { return ioInterfaceModBus_; }
            std::shared_ptr<IoInterfaceBase> GetIoInterfaceOpcUa() const { return ioInterfaceOpcUa_; }
            std::shared_ptr<WzlPlanner::Robot> GetRobot() const { return robot_; }
            std::shared_ptr<WzlPlanner::Scene> GetScene() const { return scene_; }
            std::shared_ptr<WzlPlanner::GridSnappper> GetGridSnapper() const { return gridSnapper_; }
            std::shared_ptr<rclcpp::Node> GetNode() const { return node_; }
 
            void SetIoInterface(const std::shared_ptr<IoInterfaceBase> ioInterface) { this->ioInterface_ = ioInterface; }
            void SetRobot(const std::shared_ptr<WzlPlanner::Robot> robot) { this->robot_ = robot; }
    };

} // namepspace

#endif