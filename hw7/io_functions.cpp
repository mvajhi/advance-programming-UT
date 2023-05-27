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

Team read_team(string line)
{
    Team new_team;
    vector<string> players = separate_line(line,ROLE_SEPARATOR);
    new_team.team_name = players[TEAM_NAME_INDEX];
    new_team.gk =separate_line(players[GK_INDEX],PLAYER_SEPARATOR);
    new_team.df =separate_line(players[DF_INDEX],PLAYER_SEPARATOR);
    new_team.mf =separate_line(players[MF_INDEX],PLAYER_SEPARATOR);
    new_team.fw =separate_line(players[FW_INDEX],PLAYER_SEPARATOR);
    return new_team;


}

League_data import_league()
{
    string line;

    League_data premier_league;
    ifstream file(LEAGUE_ADDRESS);
    if (!file.is_open())
    {
        cout << " problem in opening file"<<endl;
    }
    getline(file,line);
    while(getline(file,line))
    {
        Team new_pl_team = read_team(line);
        shared_ptr<Team> new_team = make_shared<Team>(new_pl_team);
        premier_league.teams.insert(make_pair(new_team->team_name,new_team));
    }
    return premier_league;

}