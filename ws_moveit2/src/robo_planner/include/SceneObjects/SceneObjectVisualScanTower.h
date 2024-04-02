#ifndef SCENEOBJECTVISUALSCANTOWER_HPP
#define SCENEOBJECTVISUALSCANTOWER_HPP

#include "SceneObject.h"

namespace WzlPlanner
{
    class SceneObjectVisualScanTower : public SceneObject
    {
        public:
            SceneObjectVisualScanTower(std::string id) 
                : SceneObject(id)
                {
                }

            SceneObjectType GetObjectType() const override { return SceneObjectType::VisualScanTower; }
    };
}

#endif