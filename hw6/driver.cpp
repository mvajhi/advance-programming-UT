#include "driver.hpp"

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

string Driver::report()
{
    string output;
    output = "\t\tid: " + to_string(id) + "\n";
    output += "\t\tmy mission:\n";
    for (auto i : missions)
    {
        output += "\t\t\tid: " + to_string(i.first) + "\n";
        output += "\t\t\tstatus: " + to_string(i.second->is_successful()) + "\n";
        output += "\t\t\t----------\n";
    }

    output += "\t\tcount travel: " + to_string(travels.size()) + "\n";

    return output;
}
