#pragma once

#include "define.hpp"
#include "mission.hpp"
#include "travel.hpp"

class Driver
{
private:
    int id;
    vector<shared_ptr<Mission_with_status>> missions;

    bool is_mission_duplicate(int id);
    bool is_travel_inside_mission(shared_ptr<Mission_with_status> mission, shared_ptr<Travel> travel);
    void update_a_mission_data(shared_ptr<Mission_with_status> &mission, shared_ptr<Travel> travel);
    void update_missions_data(shared_ptr<Travel> travel);
    vector<shared_ptr<Mission_with_status>> find_new_completed_missions();
    void close_missions_completed(vector<shared_ptr<Mission_with_status>> new_completed_missions, shared_ptr<Travel> travel);
    void close_missions_completed(shared_ptr<Mission_with_status> new_completed_mission, shared_ptr<Travel> travel);
    vector<shared_ptr<Mission_with_status>> update_missions(shared_ptr<Travel> travel);

public:
    Driver(int id_);
    void assign_mission(int mission_id, shared_ptr<Mission> mission);
    vector<shared_ptr<Mission_with_status>> record_ride(Time_range time, long distance);
    vector<shared_ptr<Mission_with_status>> get_all_missions();
};
