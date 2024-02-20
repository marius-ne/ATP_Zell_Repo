#ifndef SCENE_LOADER_HPP
#define SCENE_LOADER_HPP

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

namespace WzlPlanner
{
    class SceneLoader
    {

        public:
            SceneLoader(moveit::planning_interface::MoveGroupInterface* moveGoupInterface);

            void Initialize(moveit::planning_interface::MoveGroupInterface* moveGoupInterface);

            moveit_msgs::msg::CollisionObject AddBoxCollisionBox(std::string id, 
                double positionX, double positionY, double positionZ,
                double sizeX, double SizeY, double sizeZ);


        private:
            moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
            moveit::planning_interface::MoveGroupInterface* moveGoupInterface;
    };
} // namespace WzlPlanner

#endif // SCENE_LOADER_HPP