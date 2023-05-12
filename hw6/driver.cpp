#include "driver.hpp"

bool is_inside_time(Time_range outside, Time_range inside)
{
    return outside.start <= inside.start && inside.end <= outside.end;
}

mission_with_status Driver::check_mission_status(shared_ptr<Mission> mission)
{
    mission_with_status output;
    output.detail = mission;
    output.is_complete = false;

    Total_travels_report sum;
    sum.count = 0;
    sum.distance = 0;
    sum.time_lenght = 0;

    for (auto travel : travels)
        if (is_inside_time(mission->get_time_range(), travel->get_time_range()))
        {
            sum.count++;
            sum.distance += travel->get_distance();
            sum.time_lenght += travel->get_time_lenght();
            if (mission->is_successful(sum))
            {
                output.is_complete = true;
                output.complete_time = travel->get_time_range().end;
                break;
            }
        }

    return output;
}

Driver::Driver(int id_)
{
    id = id_;
}

void Driver::assign_mission(int mission_id, shared_ptr<Mission> new_mission)
{
    if (missions.count(mission_id) != 0)
        throw DUPLICATE_DRIVER_MISSION_MASSAGE;

    missions.insert(make_pair(mission_id, new_mission));
}

void Driver::record_ride(Time_range time, long distance)
{
    travels.push_back(make_shared<Travel>(time, distance));
}

vector<mission_with_status> Driver::report_all_mission()
{
    vector<mission_with_status> output;

    for (auto mission : missions)
        output.push_back(check_mission_status(mission.second));

    return output;
}

vector<mission_with_status> Driver::report_completed_mission()
{
    vector<mission_with_status> all_missions = report_all_mission();
    vector<mission_with_status> completed_missions;

    for (auto mission : all_missions)
        if (mission.is_complete)
            completed_missions.push_back(mission);

    return completed_missions;
}

string Driver::report()
{
    string output;
    output = "\t\tid: " + to_string(id) + "\n";
    output += "\t\tmy mission:\n";
    for (auto i : missions)
    {
        output += "\t\t\tid: " + to_string(i.first) + "\n";
        // output += "\t\t\tstatus: " + to_string(i.second->is_successful()) + "\n";
        output += "\t\t\t----------\n";
    }

    output += "\t\tcount travel: " + to_string(travels.size()) + "\n";

    return output;
}
