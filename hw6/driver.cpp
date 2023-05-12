#include "driver.hpp"

bool is_inside_time(Time_range outside, Time_range inside)
{
    return outside.start <= inside.start && inside.end <= outside.end;
}

bool Driver::is_travel_inside_mission(shared_ptr<Mission_with_status> mission, shared_ptr<Travel> travel)
{
    return is_inside_time(mission->detail->get_time_range(), travel->get_time_range());
}

void Driver::update_a_mission_data(shared_ptr<Mission_with_status> &mission, shared_ptr<Travel> travel)
{
    mission->driver_report.count++;
    mission->driver_report.distance += travel->get_distance();
    mission->driver_report.time_lenght += travel->get_time_lenght();
}

void Driver::update_missions_data(shared_ptr<Travel> travel)
{
    for (size_t i = 0; i < missions.size(); i++)
        if (!missions[i]->is_complete && is_travel_inside_mission(missions[i], travel))
            update_a_mission_data(missions[i], travel);
}

vector<shared_ptr<Mission_with_status>> Driver::find_new_completed_missions()
{
    vector<shared_ptr<Mission_with_status>> new_completed_mission;

    for (size_t i = 0; i < missions.size(); i++)
        if (!missions[i]->is_complete && missions[i]->detail->is_successful(missions[i]->driver_report))
            new_completed_mission.push_back(missions[i]);

    return new_completed_mission;
}

void Driver::close_missions_completed(vector<shared_ptr<Mission_with_status>> new_completed_missions, shared_ptr<Travel> travel)
{
    for (auto mission : new_completed_missions)
        close_missions_completed(mission, travel);
}

void Driver::close_missions_completed(shared_ptr<Mission_with_status> new_completed_mission, shared_ptr<Travel> travel)
{
        new_completed_mission->is_complete = true;
        new_completed_mission->complete_time = travel->get_time_range().end;
}

// return new complete missions
vector<shared_ptr<Mission_with_status>> Driver::update_missions(shared_ptr<Travel> travel)
{
    update_missions_data(travel);

    vector<shared_ptr<Mission_with_status>> new_completed_missions = find_new_completed_missions();

    close_missions_completed(new_completed_missions, travel);

    return new_completed_missions;
}

Driver::Driver(int id_)
{
    id = id_;
}

bool Driver::is_mission_duplicate(int id)
{
    for (auto mission : missions)
        if (mission->detail->get_id() == id)
            return true;
    return false;
}

void Driver::assign_mission(int mission_id, shared_ptr<Mission> mission)
{
    if (is_mission_duplicate(mission_id))
        throw DUPLICATE_DRIVER_MISSION_MASSAGE;

    Mission_with_status new_mission;
    new_mission.detail = mission;
    new_mission.driver_report.count = 0;
    new_mission.driver_report.distance = 0;
    new_mission.driver_report.distance = 0;
    new_mission.is_complete = false;

    missions.push_back(make_shared<Mission_with_status>(new_mission));
}

vector<shared_ptr<Mission_with_status>> Driver::record_ride(Time_range time, long distance)
{
    shared_ptr<Travel> new_travel = make_shared<Travel>(time, distance);
    vector<shared_ptr<Mission_with_status>> new_completed_missions = update_missions(new_travel);
    return new_completed_missions;
}

