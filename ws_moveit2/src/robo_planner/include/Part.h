#ifndef PART_HPP
#define PART_HPP

#include <string>
#include <memory>

#include "SceneObjects/SceneObject.h"
#include "Pose.h"

namespace WzlPlanner
{
    class PartBase : public SceneObject
    {
        protected:
            PartBase(const std::string id, const std::string collisionObjectKey = "", const std::string meshObjectKey = "")
                : SceneObject(id, collisionObjectKey, meshObjectKey) 
            {}

        public:
            virtual std::string GetPartName() const = 0;
    };

    class PartChassis : public PartBase
    {
        public:
            PartChassis(const std::string id, const std::string collisionObjectKey = "", const std::string meshObjectKey = "")
                : PartBase(id, collisionObjectKey, meshObjectKey) 
            {}

            std::string GetPartName() const override { return "Chassis"; }
            PartChassis();
    };

} // namepspace

#endif