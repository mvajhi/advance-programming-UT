#pragma once

#include "define.hpp"

class Travel
{
private:
    Time_range time;
    long distance;
public:
    Travel(Time_range time_, long distance_);
    Time_range get_time_range();
    long get_distance();
    Time get_time_lenght();
};
