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

string proccess(vector<string> input, Manager &manager)
{
    try
    {
        if (input[0] == ADD_TIME_MISSION)
        {
            manager.add_time_mission(convert_mission_input(input));
            return SUCCESS_MASSAGE + "\n";
        }
        else if (input[0] == ADD_DISTANCE_MISSION)
        {
            manager.add_distance_mission(convert_mission_input(input));
            return SUCCESS_MASSAGE + "\n";
        }
        else if (input[0] == ADD_COUNT_MISSION)
        {
            manager.add_count_mission(convert_mission_input(input));
            return SUCCESS_MASSAGE + "\n";
        }
    }
    catch (const string &error)
    {
        return error + "\n";
    }

    return "bug  I/O  " + to_string(__LINE__);
}

Mission_input convert_mission_input(vector<string> input)
{
    Mission_input output;

    output.id = stoi(input[ID_INDEX]);
    output.reward = stoi(input[REWARD_INDEX]);
    output.target = stol(input[TARGET_INDEX]);

    output.time.start = stol(input[START_TIME_INDEX]);
    output.time.end = stol(input[END_TIME_INDEX]);
    if (output.time.start > output.time.end)
        throw INVALID_INPUT_MASSAGE;

    // cout
    //     << "id: " << output.id << "\n"
    //     << "reward: " << output.reward << "\n"
    //     << "target: " << output.target << "\n"
    //     << "start: " << output.time.start << "\n"
    //     << "end: " << output.time.end << "\n";

    return output;
}
