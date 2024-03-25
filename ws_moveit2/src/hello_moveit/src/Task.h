#ifndef TASK_HPP
#define TASK_HPP

#include <vector>
#include <memory>

#include "Pose.h"
#include "SceneObject.h"

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

    class TaskScanScene : public Task
    {
        private:
            std::vector<std::shared_ptr<SceneObject>> objectsInScene;

        public:
            void Execute() override;
            void Initialize(
                float minX, float maxX, int scanCountX,
                float minY, float maxY, int scaneCountY, 
                float z,
                float eulerX, float eulerY, float eulerZ);
    };

    // Scans the scene and get an object inside the scene
    class GetObjectInScene : public Task
    {
        private:
            std::vector<std::shared_ptr<SceneObject>> lastScan;

        public:
            void Execute() override;
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
            
            void SetPoseStart(std::shared_ptr<Pose> pose) { this->poseStart = pose; }
            void SetPosePick(std::shared_ptr<Pose> pose) { this->poseEnd = pose; }
            void SetPoseEnd(std::shared_ptr<Pose> pose) { this->poseEnd = pose; }

        private:
            std::shared_ptr<Pose> poseStart;
            std::shared_ptr<Pose> posePick;
            std::shared_ptr<Pose> poseEnd;
    };

    class TaskPlace : public Task
    {
        public:
            void Execute() override;

        private:
            std::shared_ptr<Pose> poseStart;
            std::shared_ptr<Pose> posePlace;
            std::shared_ptr<Pose> poseEnd;
    };

    class TaskPickAndPlace : public Task
    {
        private:
            std::shared_ptr<TaskPick> taskPick;
            std::shared_ptr<TaskPlace> taskPlace;

        public:
            void SetTaskPick(std::shared_ptr<TaskPick> taskPick) { this->taskPick = taskPick; }
            void SetTaskPlace(std::shared_ptr<TaskPlace> taskPlace) { this->taskPlace = taskPlace; }

            void Execute() override;
    };

    class TaskOpenDoor : public Task
    {
        private:
            // 1: Open; 2: Close; 3: Opening; 4: Closing
            int currentState_; 

        public:
            TaskOpenDoor()
            {
                currentState_ = 2;
            }  

            bool OpenDoor();
            bool CloseDooor();
    };

} // namespace WzlPlanner

#endif // TASK_HPP