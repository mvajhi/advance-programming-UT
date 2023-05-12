#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>

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

struct Assign_input
{
    int driver_id;
    int mission_id;
};


// return
const string SUCCESS_MASSAGE = "OK";
const string INVALID_INPUT_MASSAGE = "INVALID_ARGUMENTS";
const string DUPLICATE_MISSION_ID_MASSAGE = "DUPLICATE_MISSION_ID";
const string DUPLICATE_DRIVER_MISSION_MASSAGE = "DUPLICATE_DRIVER_MISSION";
const string MISSION_NOT_FOUND_MASSAGE = "MISSION_NOT_FOUND";

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
const string ASSIGN_MISSION = "assign_mission";
const string REPORT = "report";
