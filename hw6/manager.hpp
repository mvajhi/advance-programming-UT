#pragma once

#include "define.hpp"
#include "mission.hpp"
#include "driver.hpp"

class Manager
{
private:
    map<int ,shared_ptr<Mission>> missions;
    map<int, shared_ptr<Driver>> drivers;
public:
    Manager();
    void check_duplicate_mission(int id);
    void add_time_mission(Mission_input input);
    void add_distance_mission(Mission_input input);
    void add_count_mission(Mission_input input);
    void assign_mission(Assign_input input);

    // TODO rm this
    string full_report();
};
