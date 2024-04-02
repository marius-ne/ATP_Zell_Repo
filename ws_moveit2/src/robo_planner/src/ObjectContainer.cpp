#include "../include/ObjectContainer.h"

// Singleton
WzlPlanner::ObjectContainer* WzlPlanner::ObjectContainer::singleton_= nullptr;;

WzlPlanner::ObjectContainer* WzlPlanner::ObjectContainer::Get() 
{
    if (singleton_ == nullptr)
        singleton_ = new WzlPlanner::ObjectContainer();

    return singleton_; 
}