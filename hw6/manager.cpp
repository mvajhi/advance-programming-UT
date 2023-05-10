#include "manager.hpp"

Manager::Manager()
{
}

Manager::~Manager()
{
    for (auto i : missions)
        delete i.second;
}

void Manager::add_time_mission(Mission_input input)
{
    if (missions.count(input.id) != 0)
        throw DUPLICATE_MISSION_ID_MASSAGE;

    Mission *new_mission = new Time_mission(input.id, input.time, input.reward, input.target);
    missions.insert(make_pair(input.id, new_mission));

    // cout
    //     << "reward: " << missions[1]->get_reward() << "\n"
    //     << "start: " << missions[1]->get_time_range().start << "\n"
    //     << "end: " << missions[1]->get_time_range().end << "\n";
}

void Manager::add_distance_mission(Mission_input input)
{
}

void Manager::add_count_mission(Mission_input input)
{
}
