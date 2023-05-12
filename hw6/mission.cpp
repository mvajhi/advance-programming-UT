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

string Mission::report()
{
    string output;
    output =
        "\t\tmission id: " + to_string(id) + "\n"
                                             "\t\tstart time: " +
        to_string(time.start) + "\n"
                                "\t\tend time: " +
        to_string(time.end) + "\n"
                              "\t\treward: " +
        to_string(reward) + "\n";
    return output;
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

string Time_mission::report()
{
    string output = Mission::report();
    output += "\t\ttype: time mission\n";
    output += "\t\tmin time to earn: " + to_string(min_time_to_earn) + "\n";
    return output;
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

string Distance_mission::report()
{
    string output = Mission::report();
    output += "\t\ttype: distance mission\n";
    output += "\t\tmin distance to earn: " + to_string(min_destance_to_earn) + "\n";
    return output;
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

string Count_mission::report()
{
    string output = Mission::report();
    output += "\t\ttype: count mission\n";
    output += "\t\tmin count to earn: " + to_string(min_count_to_earn) + "\n";
    return output;
}
