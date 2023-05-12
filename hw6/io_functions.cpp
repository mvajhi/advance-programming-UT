#include "io_functions.hpp"

vector<string> separate_line(string line, char separator)
{
    vector<string> output;
    string word = "";

    for (size_t i = 0; i < line.size(); i++)
        if (line[i] == separator && word != "")
        {
            output.push_back(word);
            word = "";
        }
        else if (line[i] != separator)
            word += line[i];

    if (word != "")
        output.push_back(word);

    return output;
}

shared_ptr<Reporter> proccess(vector<string> input, Manager &manager)
{
    try
    {
        if (input[0] == ADD_TIME_MISSION)
        {
            manager.add_time_mission(convert_mission_input(input));
            return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
        }
        else if (input[0] == ADD_DISTANCE_MISSION)
        {
            manager.add_distance_mission(convert_mission_input(input));
            return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
        }
        else if (input[0] == ADD_COUNT_MISSION)
        {
            manager.add_count_mission(convert_mission_input(input));
            return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
        }
        else if (input[0] == ASSIGN_MISSION)
        {
            manager.assign_mission(convert_assign_input(input));
            return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
        }
        else if (input[0] == NEW_TRAVEL)
        {
            manager.record_ride(convert_travel_input(input));
            return manager.report_completed_mission(convert_travel_input(input).driver_id);
        }
        else if (input[0] == REPORT)
        {
            return make_shared<Massage_reporter>(manager.full_report());
        }
    }
    catch (const string &error)
    {
        return make_shared<Massage_reporter>(error + "\n");
    }

    return make_shared<Massage_reporter>("bug  I/O  " + to_string(__LINE__));
}

Mission_input convert_mission_input(vector<string> input)
{
    Mission_input output = create_mission_input(input);

    check_mission_input(output);

    // cout
    //     << "id: " << output.id << "\n"
    //     << "reward: " << output.reward << "\n"
    //     << "target: " << output.target << "\n"
    //     << "start: " << output.time.start << "\n"
    //     << "end: " << output.time.end << "\n";

    return output;
}

Mission_input create_mission_input(vector<string> input)
{
    Mission_input output;

    output.id = stoi(input[ID_MISSION_INDEX]);
    output.reward = stoi(input[REWARD_MISSION_INDEX]);
    output.target = stol(input[TARGET_MISSION_INDEX]);
    output.time.start = stol(input[START_TIME_MISSION_INDEX]);
    output.time.end = stol(input[END_TIME_MISSION_INDEX]);

    return output;
}

void check_mission_input(Mission_input input)
{
    if (input.time.start > input.time.end ||
        input.reward < 0 ||
        input.target < 0)
        throw INVALID_INPUT_MASSAGE;
}

Travel_input convert_travel_input(vector<string> input)
{
    Travel_input output;

    output.driver_id = stoi(input[DRIVER_ID_TRAVEL_INDEX]);
    output.distance = stol(input[DISTANCE_TRAVEL_INDEX]);
    output.time.start = stol(input[START_TIME_TRAVEL_INDEX]);
    output.time.end = stol(input[END_TIME_TRAVEL_INDEX]);
    
    if (output.time.start > output.time.end)
        throw INVALID_INPUT_MASSAGE;

    return output;
}

Assign_input convert_assign_input(vector<string> input)
{
    Assign_input output;
    output.mission_id = stoi(input[MISSION_ID_ASSIGN_INDEX]);
    output.driver_id = stoi(input[DRIVER_ID_ASSIGN_INDEX]);
    return output;
}
