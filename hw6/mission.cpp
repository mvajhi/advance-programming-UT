#include "mission.hpp"

Mission::Mission(int id_, Time_range time_, int reward_)
{
    id = id_;
    time = time_;
    reward = reward_;
}

Mission::~Mission()
{
}

Time_range Mission::get_time_range()
{
    return time;
}

int Mission::get_reward()
{
    return reward;
}

Time_mission::Time_mission(int id_, Time_range time_, int reward_, long taget_to_earn)
    : Mission(id_, time_, reward_)
{
    min_time_to_earn = taget_to_earn;
}

bool Time_mission::is_successful()
{
    return false;
}

Distance_mission::Distance_mission(int id_, Time_range time_, int reward_, long taget_to_earn)
    : Mission(id_, time_, reward_)
{
    min_destance_to_earn = taget_to_earn;
}

bool Distance_mission::is_successful()
{
    return false;
}

Count_mission::Count_mission(int id_, Time_range time_, int reward_, long taget_to_earn)
    : Mission(id_, time_, reward_)
{
     min_count_to_earn = taget_to_earn;
}

bool Count_mission::is_successful()
{
     return false;
}
