#include "io_functions.hpp"

vector<string> separate_line(string line, char separator)
{
    vector<string> output;
    string word = "";

    for (size_t i = 0; i < line.size(); i++)
        if (line[i] == separator)
        {
            output.push_back(word);
            word = "";
        }
        else
            word += line[i];
    
    if (word != "")
        output.push_back(word);

    return output;
}