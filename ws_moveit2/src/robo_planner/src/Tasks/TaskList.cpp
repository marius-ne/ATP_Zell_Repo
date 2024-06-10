#include "../../include/Tasks/TaskList.h"

bool WzlPlanner::TaskList::Execute()
{
    /*
    for(auto&& elem: this->tasks)
    {
        if (!elem->Execute()) // virtual dispatch
        {
            return false;
        }
    }
    */

    return Task::Execute();
}