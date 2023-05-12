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

int Mission::get_id()
{
    return id;
}


Time_mission::Time_mission(int id_, Time_range time_, int reward_, long taget_to_earn)
    : Mission(id_, time_, reward_)
{
    min_time_to_earn = taget_to_earn;
}

bool Time_mission::is_successful(Total_travels_report report)
{
    return min_time_to_earn <= report.time_lenght;
}

Distance_mission::Distance_mission(int id_, Time_range time_, int reward_, long taget_to_earn)
    : Mission(id_, time_, reward_)
{
    min_destance_to_earn = taget_to_earn;
}

bool Distance_mission::is_successful(Total_travels_report report)
{
    return min_destance_to_earn <= report.distance;
}

Count_mission::Count_mission(int id_, Time_range time_, int reward_, long taget_to_earn)
    : Mission(id_, time_, reward_)
{
    min_count_to_earn = taget_to_earn;
}

bool Count_mission::is_successful(Total_travels_report report)
{
    return min_count_to_earn <= report.count;
}
