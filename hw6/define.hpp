#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>

using namespace std;

typedef long int Time;
class Mission;

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

struct Travel_input
{
    int driver_id;
    Time_range time;
    long distance;
};

struct Total_travels_report
{
    int count;
    long distance;
    long time_lenght;
};

struct Mission_with_status
{
    shared_ptr<Mission> detail;
    Total_travels_report driver_report;
    Time complete_time;
    bool is_complete;
};

// return
const string SUCCESS_MASSAGE = "OK";
const string INVALID_INPUT_MASSAGE = "INVALID_ARGUMENTS";
const string DUPLICATE_MISSION_ID_MASSAGE = "DUPLICATE_MISSION_ID";
const string DUPLICATE_DRIVER_MISSION_MASSAGE = "DUPLICATE_DRIVER_MISSION";
const string MISSION_NOT_FOUND_MASSAGE = "MISSION_NOT_FOUND";

// index
const int ID_MISSION_INDEX = 1;
const int START_TIME_MISSION_INDEX = 2;
const int END_TIME_MISSION_INDEX = 3;
const int TARGET_MISSION_INDEX = 4;
const int REWARD_MISSION_INDEX = 5;

const int MISSION_ID_ASSIGN_INDEX = 1;
const int DRIVER_ID_ASSIGN_INDEX = 2;

const int START_TIME_TRAVEL_INDEX = 1;
const int END_TIME_TRAVEL_INDEX = 2;
const int DRIVER_ID_TRAVEL_INDEX = 3;
const int DISTANCE_TRAVEL_INDEX = 4;

// arg count
const size_t MISSION_ARG_COUNT = 5;
const size_t ASSIGN_ARG_COUNT = 2;
const size_t TRAVEL_ARG_COUNT = 4;

// CLI input command
const string ADD_TIME_MISSION = "add_time_mission";
const string ADD_DISTANCE_MISSION = "add_distance_mission";
const string ADD_COUNT_MISSION = "add_count_mission";
const string ASSIGN_MISSION = "assign_mission";
const string NEW_TRAVEL = "record_ride";
