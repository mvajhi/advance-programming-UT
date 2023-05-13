#pragma once

#include "define.hpp"
#include "mission.hpp"
#include "driver.hpp"
#include "reporter.hpp"

class Manager
{
private:
    map<int ,shared_ptr<Mission>> missions;
    map<int, shared_ptr<Driver>> drivers;

    // checker
    void check_duplicate_mission(int id);
    void check_mission_exist(int id);

public:
    Manager();
    shared_ptr<Reporter> add_time_mission(Mission_input input);
    shared_ptr<Reporter> add_distance_mission(Mission_input input);
    shared_ptr<Reporter> add_count_mission(Mission_input input);
    shared_ptr<Reporter> assign_mission(Assign_input input);
    shared_ptr<Reporter> record_ride(Travel_input input);
    shared_ptr<Reporter> report_driver(Driver_report_input input);
};
