#ifndef TASK_HPP
#define TASK_HPP

#include <vector>
#include <memory>

#include "Pose.h"

namespace WzlPlanner
{
    class Task
    {

        public:
            Task();

            virtual void Execute() = 0;
            
    };

    class TaskList : public Task
    {

        public:
            void AddTask(std::shared_ptr<Task> task) { tasks.push_back(task); }

            void Execute() override;

        private:
            std::vector<std::shared_ptr<Task>> tasks;

    };

    class TaskMoveToPose : public Task
    {
        
        private:
            std::shared_ptr<Pose> targetPose;

        public:
            void Execute() override;
        
            void SetTargetPose(std::shared_ptr<Pose> targetPose) { this->targetPose = targetPose; }


    };

    class TaskOpenGripper : public Task
    {
        public:
            void Execute() override;
        
    };

    class TaskCloseGripper : public Task
    {
        public:
            void Execute() override;
    };

    class TaskPick : public Task
    {
        public:
            void Execute() override;

        private:
            std::shared_ptr<Pose> posePick;
            std::shared_ptr<Pose> poseStart;
            std::shared_ptr<Pose> poseEnd;
    };

    class TaskPlace : public Task
    {
        public:
            void Execute() override;

        private:
            std::shared_ptr<Pose> posePick;
            std::shared_ptr<Pose> poseStart;
            std::shared_ptr<Pose> poseEnd;
    };

    class TaskPickAndPlace : public Task
    {
        private:
            std::shared_ptr<Pose> posePick;
            std::shared_ptr<Pose> posePlace;
            std::shared_ptr<Pose> poseStart;
            std::shared_ptr<Pose> poseEnd;

        public:
            void Execute() override;
    };

    


} // namespace WzlPlanner

#endif // TASK_HPP