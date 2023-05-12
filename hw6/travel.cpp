#include "travel.hpp"

Travel::Travel(Time_range time_, long distance_)
{
    time = time_;
    distance = distance_;
}

Time_range Travel::get_time_range()
{
    return time;
}

long Travel::get_distance()
{
    return distance;
}

Time Travel::get_time_lenght()
{
    return time.end - time.start;
}
