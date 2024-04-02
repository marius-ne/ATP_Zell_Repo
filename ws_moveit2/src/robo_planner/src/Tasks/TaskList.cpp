#include "../../include/Tasks/TaskList.h"

void WzlPlanner::TaskList::Execute()
{
    for(auto&& elem: this->tasks)
        elem->Execute(); // virtual dispatch
}