#pragma once

#include "define.hpp"

class Travel
{
private:
    Time_range time;
    long distance;
public:
    Travel(Time_range time_, long distance_);
};
