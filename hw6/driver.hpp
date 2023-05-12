#pragma once

#include "define.hpp"
#include "mission.hpp"
#include "travel.hpp"

class Driver
{
private:
    int id;
    map<int, shared_ptr<Mission>> missions;
    vector<shared_ptr<Travel>> travels;
public:
    Driver(int id_);
    void assign_mission(int mission_id, shared_ptr<Mission> new_mission);
    void record_ride(Time_range time, long distance);
    string report();
};
