#ifndef TASKGETOBJECTSINSCENE_HPP
#define TASKGETOBJECTSINSCENE_HPP

#include "../Task.h"

#include "../../../include/SceneObjects/SceneObjectInclude.h"

namespace WzlPlanner
{

    // Scans the scene and get an object inside the scene
    class GetObjectInScene : public Task
    {
        private:
            std::vector<std::shared_ptr<SceneObject>> lastScan;

        public:
            bool Execute() override;
    };
}

#endif