#pragma once

#include "define.hpp"
#include "mission.hpp"

class Driver
{
private:
    int id;
    map<int, Mission *> missions;
    // vector<Travel> travels;
public:
    Driver(int id_);
    void assign_mission(int mission_id, Mission *new_mission);
};
