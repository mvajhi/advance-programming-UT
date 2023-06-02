#pragma once

#include "define.hpp"
#include "mission.hpp"
#include <algorithm>

class Reporter
{
public:
    virtual void get_cli_report() = 0;
};

class Massage_reporter : public Reporter
{
private:
    string massage;
public:
    Massage_reporter(string massage_);
    void get_cli_report();
};

class new_completed_missions_reporter : public Reporter
{
private:
    vector<shared_ptr<Mission_with_status>> completed_missions;
    int driver_id;
public:
    new_completed_missions_reporter(vector<shared_ptr<Mission_with_status>> completed_mission_, int driver_id_);
    void get_cli_report();
};

class all_missions_reporter : public Reporter
{
private:
    vector<shared_ptr<Mission_with_status>> missions;
    int driver_id;
public:
    all_missions_reporter(vector<shared_ptr<Mission_with_status>> mission_, int driver_id_);
    void get_cli_report();
};
