#pragma once

#include "define.hpp"

class Manager
{
private:
    /* data */
public:
    Manager(/* args */);
    void add_time_mission(Mission_input input);
    void add_distance_mission(Mission_input input);
    void add_count_mission(Mission_input input);
};
