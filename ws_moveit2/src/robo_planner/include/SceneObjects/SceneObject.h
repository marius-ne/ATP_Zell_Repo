#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP

#include <memory>
#include <string>

#include "../Pose.h"
#include "SceneObjectType.h"

namespace WzlPlanner
{
    // The representation of a physical object inside a scene.
    // Each scene object contans 
    class SceneObject
    {
        private:

        protected:
            std::string id_;
            
            // origin of the scene object
            std::shared_ptr<WzlPlanner::Transform> transformOrigin_;

            // robot approach transform
            std::shared_ptr<WzlPlanner::Transform> transformApproach_;

            // the transform in which the execution happens (e.g. pick/place position)
            std::shared_ptr<WzlPlanner::Transform> transformExecution_;


            SceneObject(std::string id) 
            {
                id_ = id;
            }

        public:
            //std::shared_ptr<WzlPlanner::Transform> GetTransform() const { return transformOrigin_; }
            virtual std::shared_ptr<Transform> GetTransform() const { return this->transformOrigin_; }
            std::shared_ptr<Transform> GeTransformAppraocah() const { return this->transformApproach_; }
            std::shared_ptr<Transform> GeTransformExecution() const { return this->transformExecution_; }

            virtual SceneObjectType GetObjectType() const = 0;
            std::string GetId() const { return id_; };


            virtual void InitializeTransform(const std::shared_ptr<Transform> parent)
            {
                transformOrigin_ = std::make_shared<Transform>(id_);
                transformOrigin_->SetParent(parent);

                transformApproach_ = std::make_shared<WzlPlanner::Transform>(id_  + "_Approach");
                transformApproach_->SetParent(transformOrigin_);

                transformExecution_ = std::make_shared<WzlPlanner::Transform>(id_  + "_Execution");
                transformExecution_->SetParent(transformOrigin_);
            }
    };
}

#endif