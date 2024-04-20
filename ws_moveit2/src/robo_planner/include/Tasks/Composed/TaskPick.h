#ifndef TASKPICK_HPP
#define TASKPICK_HPP

#include "../Task.h"

#include "../../Pose.h"
#include "../../SceneObjects/SceneObject.h"
#include "../../Part.h"

#include "../Atomic/TaskMoveToPose.h"
#include "../Atomic/TaskGripperOpen.h"
#include "../Atomic/TaskGripperClose.h"

namespace WzlPlanner
{
    class TaskPick : public Task
    {
        public:
            TaskPick()
            {
                taskMoveToPoseApproach_ = std::make_shared<TaskMoveToPose>();
                taskGripperOpen_ = std::make_shared<TaskGripperOpen>();
                taskMoveToPosePick_ = std::make_shared<TaskMoveToPose>();
                taskGripperClose_ = std::make_shared<TaskGripperClose>();
                taskMoveToPoseEnd_ = std::make_shared<TaskMoveToPose>();

                subTasks_.push_back(taskMoveToPoseApproach_);
                subTasks_.push_back(taskGripperOpen_);
                subTasks_.push_back(taskMoveToPosePick_);
                subTasks_.push_back(taskGripperClose_);
                subTasks_.push_back(taskMoveToPoseEnd_);
            }

            void SetId(const std::string id) override 
            {
                Task::SetId(id);

                taskMoveToPoseApproach_->SetId(id + "_MoveToPoseApproach");
                taskGripperOpen_->SetId(id + "_GripperOpen");
                taskMoveToPosePick_->SetId(id + "_MoveToPosePick");
                taskGripperClose_->SetId(id + "_GripperClose");
                taskMoveToPoseEnd_->SetId(id + "_MoveToPoseEnd");
            }

            void Initialize(const std::shared_ptr<WzlPlanner::SceneObject> sceneObject)
            {
                auto poseApproach = sceneObject->GeTransformAppraocah()->GetPoseAbsolute();
                auto posePick = sceneObject->GeTransformExecution()->GetPoseAbsolute();
                auto poseEnd = sceneObject->GeTransformAppraocah()->GetPoseAbsolute();

                taskMoveToPoseApproach_->SetTargetPose(poseApproach);
                taskMoveToPosePick_->SetTargetPose(posePick);
                taskMoveToPoseEnd_->SetTargetPose(poseEnd);
            }

            void Initialize(const std::shared_ptr<WzlPlanner::PartBase> scenePart)
            {
                auto poseApproach = scenePart->GeTransformAppraocah()->GetPoseAbsolute();
                auto posePick = scenePart->GeTransformExecution()->GetPoseAbsolute();
                auto poseEnd = scenePart->GeTransformAppraocah()->GetPoseAbsolute();

                taskMoveToPoseApproach_->SetTargetPose(poseApproach);
                taskMoveToPosePick_->SetTargetPose(posePick);
                taskMoveToPoseEnd_->SetTargetPose(poseEnd);
            }

            std::shared_ptr<TaskMoveToPose> GetTaskMoveToPoseApproach() const { return taskMoveToPoseApproach_; }
            std::shared_ptr<TaskGripperOpen> GetTaskGripperOpen() const { return taskGripperOpen_; }
            std::shared_ptr<TaskMoveToPose> GetTaskMoveToPosePick() const { return taskMoveToPosePick_; }
            std::shared_ptr<TaskGripperClose> GetTaskGripperClose() const { return taskGripperClose_; }
            std::shared_ptr<TaskMoveToPose> GetTaskMoveToEnd() const { return taskMoveToPoseEnd_; }

        private:
            std::shared_ptr<TaskMoveToPose> taskMoveToPoseApproach_;
            std::shared_ptr<TaskGripperOpen> taskGripperOpen_;
            std::shared_ptr<TaskMoveToPose> taskMoveToPosePick_;
            std::shared_ptr<TaskGripperClose> taskGripperClose_;
            std::shared_ptr<TaskMoveToPose> taskMoveToPoseEnd_;

    };
}

#endif