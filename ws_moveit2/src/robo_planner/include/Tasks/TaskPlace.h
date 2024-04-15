#ifndef TASKPLACE_HPP
#define TASKPLACE_HPP

#include "Task.h"

#include "../Pose.h"
#include "../SceneObjects/SceneObject.h"

#include "TaskMoveToPose.h"
#include "TaskGripperOpen.h"
#include "TaskGripperClose.h"

namespace WzlPlanner
{

    class TaskPlace : public Task
    {
        public:
            TaskPlace()
            {
                taskMoveToPoseApproach_ = std::make_shared<TaskMoveToPose>();
                taskGripperOpen_ = std::make_shared<TaskGripperOpen>();
                taskMoveToPosePlace_ = std::make_shared<TaskMoveToPose>();
                taskGripperClose_ = std::make_shared<TaskGripperClose>();
                taskMoveToPoseEnd_ = std::make_shared<TaskMoveToPose>();

                subTasks_.push_back(taskMoveToPoseApproach_);
                subTasks_.push_back(taskGripperOpen_);
                subTasks_.push_back(taskMoveToPosePlace_);
                subTasks_.push_back(taskGripperClose_);
                subTasks_.push_back(taskMoveToPoseEnd_);
            }

            void SetId(const std::string id) override 
            {
                Task::SetId(id);

                taskMoveToPoseApproach_->SetId(id + "_MoveToPoseApproach");
                taskGripperOpen_->SetId(id + "_GripperOpen");
                taskMoveToPosePlace_->SetId(id + "_MoveToPosePlace");
                taskGripperClose_->SetId(id + "_GripperClose");
                taskMoveToPoseEnd_->SetId(id + "_MoveToPoseEnd");
            }

            void Initialize(const std::shared_ptr<WzlPlanner::SceneObject> sceneObject)
            {
                auto poseApproach = sceneObject->GeTransformAppraocah()->GetPoseAbsolute();
                auto posePlace = sceneObject->GeTransformExecution()->GetPoseAbsolute();
                auto poseEnd = sceneObject->GeTransformAppraocah()->GetPoseAbsolute();

                taskMoveToPoseApproach_->SetTargetPose(poseApproach);
                taskMoveToPosePlace_->SetTargetPose(posePlace);
                taskMoveToPoseEnd_->SetTargetPose(poseEnd);
            }

            std::shared_ptr<TaskMoveToPose> GetTaskMoveToPoseApproach() const { return taskMoveToPoseApproach_; }
            std::shared_ptr<TaskGripperOpen> GetTaskGripperOpen() const { return taskGripperOpen_; }
            std::shared_ptr<TaskMoveToPose> GetTaskMoveToPosePlace() const { return taskMoveToPosePlace_; }
            std::shared_ptr<TaskGripperClose> GetTaskGripperClose() const { return taskGripperClose_; }
            std::shared_ptr<TaskMoveToPose> GetTaskMoveToEnd() const { return taskMoveToPoseEnd_; }


        private:

            std::shared_ptr<TaskMoveToPose> taskMoveToPoseApproach_;
            std::shared_ptr<TaskGripperOpen> taskGripperOpen_;
            std::shared_ptr<TaskMoveToPose> taskMoveToPosePlace_;
            std::shared_ptr<TaskGripperClose> taskGripperClose_;
            std::shared_ptr<TaskMoveToPose> taskMoveToPoseEnd_;
    };

}

#endif