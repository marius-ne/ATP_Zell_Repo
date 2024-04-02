#ifndef TASK_HPP
#define TASK_HPP

#include <vector>
#include <memory>
#include <string>

namespace WzlPlanner
{
    class Task
    {

        public:
            Task();

            virtual void Execute() 
            { 
                for (auto &&subtask: subTasks_)
                {
                    subtask->Execute();
                }
            };

            virtual void SetId(const std::string id) { id_ = id; }
            std::string GetId() { return id_; }

        protected:
            std::vector<std::shared_ptr<Task>> subTasks_;

        private:
            std::string id_;
    };

} // namespace WzlPlanner

#endif // TASK_HPP