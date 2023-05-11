#pragma once

#include "define.hpp"
#include "mission.hpp"

class Driver
{
private:
    int id;
    map<int, shared_ptr<Mission>> missions;
    // vector<Travel> travels;
public:
    Driver(int id_);
    void assign_mission(int mission_id, shared_ptr<Mission> new_mission);
};
