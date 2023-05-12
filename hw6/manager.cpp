#include "manager.hpp"

Manager::Manager()
{
}

void Manager::check_duplicate_mission(int id)
{
    if (missions.count(id) != 0)
        throw DUPLICATE_MISSION_ID_MASSAGE;
}

void Manager::check_mission_exist(int id)
{
    if (missions.count(id) == 0)
        throw MISSION_NOT_FOUND_MASSAGE;
}

void Manager::add_time_mission(Mission_input input)
{
    check_duplicate_mission(input.id);
    shared_ptr<Mission> new_mission = make_shared<Time_mission>(input.id, input.time, input.reward, input.target);
    missions.insert(make_pair(input.id, new_mission));
}

void Manager::add_distance_mission(Mission_input input)
{
    check_duplicate_mission(input.id);
    shared_ptr<Mission> new_mission = make_shared<Distance_mission>(input.id, input.time, input.reward, input.target);
    missions.insert(make_pair(input.id, new_mission));
}

void Manager::add_count_mission(Mission_input input)
{
    check_duplicate_mission(input.id);
    shared_ptr<Mission> new_mission = make_shared<Count_mission>(input.id, input.time, input.reward, input.target);
    missions.insert(make_pair(input.id, new_mission));
}

void Manager::assign_mission(Assign_input input)
{
    check_mission_exist(input.mission_id);

    if (drivers.count(input.driver_id) == 0)
        drivers.insert(make_pair(input.driver_id, make_shared<Driver>(input.driver_id)));

    drivers[input.driver_id]->assign_mission(input.mission_id, missions[input.mission_id]);
}

void Manager::record_ride(Travel_input input)
{
    if (drivers.count(input.driver_id) != 0)
        drivers[input.driver_id]->record_ride(input.time, input.distance);
}

shared_ptr<Reporter> Manager::report_completed_mission(int driver_id)
{
    return make_shared<Driver_completed_mission_reporter>(drivers[driver_id]->report_completed_mission(), driver_id);
}

string Manager::full_report()
{
    string output;
    output = "////////////////////////////////////////////////////\n";
    output += "full report\n\tmissions:\n";
    for (auto i : missions)
    {
        output += i.second->report();
        output += "\t\t----------------------\n";
    }
    // output += "\t//////////////////////////////////////\n";
    output += "\tdrivers:\n";
    for (auto i : drivers)
    {
        output += i.second->report();
        output += "\t\t----------------------\n";
    }

    output += "////////////////////////////////////////////////////\n";

    return output;
}
