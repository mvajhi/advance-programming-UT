#pragma once

#include "define.hpp"
#include "mission.hpp"

class Reporter
{
public:
    virtual void cli_report() = 0;
};

class Massage_reporter : public Reporter
{
private:
    string massage;
public:
    Massage_reporter(string massage_);
    void cli_report();
};

class new_completed_mission_reporter : public Reporter
{
private:
    vector<shared_ptr<Mission_with_status>> completed_missions;
    int driver_id;
public:
    new_completed_mission_reporter(vector<shared_ptr<Mission_with_status>> completed_mission_, int driver_id_);
    void cli_report();
};
