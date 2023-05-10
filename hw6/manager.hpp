#pragma once

#include "define.hpp"
#include "mission.hpp"

class Manager
{
private:
    map<int ,Mission *> missions;
public:
    Manager();
    ~Manager();
    void add_time_mission(Mission_input input);
    void add_distance_mission(Mission_input input);
    void add_count_mission(Mission_input input);
};
