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
            return make_shared<Massage_reporter>(BAD_REQUEST_MASSAGE + "\n");
        else if (are_commands_some(input, SIGNUP_COMMAND))
            return manager.signup(convert_to_login_info(input));
        else if (are_commands_some(input, LOGIN_COMMAND))
            return manager.login(convert_to_login_info(input));
        else if (are_commands_some(input, LOGOUT_COMMAND))
            return manager.logout();
        else
            return make_shared<Massage_reporter>(BAD_REQUEST_MASSAGE + " else\n");
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

User_login_info convert_to_login_info(vector<string> input)
{
    User_login_info output;
    
    if (input.size() != LOGIN_COMMAND_SIZE)
        throw make_shared<Massage_reporter> (BAD_REQUEST_MASSAGE + "\n");

    output.username = input[USERNAME_INDEX];
    output.password = input[PASSWORD_INDEX];

    return output;
}

bool are_commands_some(vector<string> input, string command)
{
    vector<string> separated_command = separate_line(command, ' ');

    if (input.size() < separated_command.size())
        return false;

    for (size_t i = 0; i < separated_command.size(); i++)
        if (input[i] != separated_command[i])
            return false;
    
    return true;
}