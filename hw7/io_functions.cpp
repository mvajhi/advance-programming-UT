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
        if (input.size() == 0)
            return make_shared<Massage_reporter>("INVALID_INPUT_MASSAGE\n");
        else
            return make_shared<Massage_reporter>("INVALID_INPUT_MASSAGE else\n");
    }
    catch (const string &error)
    {
        return make_shared<Massage_reporter>(error + "\n");
    }

    return make_shared<Massage_reporter>("bug  I/O  " + to_string(__LINE__));
}

void check_arg_count(vector<string> input, size_t count)
{
    if (input.size() == count)
        throw "INVALID_INPUT_MASSAGE";
}

void import_files(Manager &manager)
{
}
