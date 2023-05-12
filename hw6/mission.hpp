#pragma once

#include "define.hpp"

class Mission
{
private:
    int id;
    Time_range time;
    int reward;
public:
    Mission(int id_, Time_range time_, int reward_);
    virtual ~Mission();
    Time_range get_time_range();
    int get_reward();
    virtual bool is_successful(/*input*/) = 0;
    virtual string report();
};

class Time_mission : public Mission
{
private:
    long min_time_to_earn;
public:
    Time_mission(int id_, Time_range time_, int reward_, long taget_to_earn);
    bool is_successful();
    virtual string report();
};

class Distance_mission : public Mission
{
private:
    long min_destance_to_earn;
public:
    Distance_mission(int id_, Time_range time_, int reward_, long taget_to_earn);
    bool is_successful();
    virtual string report();
};

class Count_mission : public Mission
{
private:
    int min_count_to_earn;
public:
    Count_mission(int id_, Time_range time_, int reward_, long taget_to_earn);
    bool is_successful();
    virtual string report();
};

