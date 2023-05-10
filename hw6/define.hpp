#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef long int Time;

struct Time_range
{
    Time start;
    Time end;
};

struct Mission_input
{
    int id;
    Time_range time;
    long int target;
    int reward;
};

// return
const string SUCCESS_MASSAGE = "OK";
const string INVALID_INPUT_MASSAGE = "INVALID_ARGUMENTS";

// index
const int ID_INDEX = 1;
const int START_TIME_INDEX = 2;
const int END_TIME_INDEX = 3;
const int TARGET_INDEX = 4;
const int REWARD_INDEX = 5;

// CLI input command
const string ADD_TIME_MISSION = "add_time_mission";
const string ADD_DISTANCE_MISSION = "add_distance_mission";
const string ADD_COUNT_MISSION = "add_count_mission";
