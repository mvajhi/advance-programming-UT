#include "io_functions.hpp"

vector<string> separate_line(string line, char separator, bool ignore_tmp)
{
    vector<string> output;
    string word = "";

    for (size_t i = 0; i < line.size(); i++)
        if (line[i] == separator && (!ignore_tmp || word != ""))
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
        return command_proccess(input, manager);
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
        throw BAD_REQUEST_MASSAGE;
}

void import_files(Manager &manager)
{
    manager.import_real_teams(import_league());
    manager.import_real_weeks(import_league_weeks());
}

User_login_info convert_to_login_info(vector<string> input)
{
    check_sso_input(input);

    User_login_info output;

    output.username = input[USERNAME_INDEX];
    output.password = input[PASSWORD_INDEX];

    return output;
}

shared_ptr<Reporter> command_proccess(vector<string> input, Manager &manager)
{
    if (input.size() == 0)
        return make_shared<Massage_reporter>(BAD_REQUEST_MASSAGE + "\n");
    else if (are_commands_some(input, LOGOUT_COMMAND))
        return manager.logout();
    else if (are_commands_some(input, PASS_WEEK_COMMAND))
        return manager.pass_week();
    else if (are_commands_some(input, SHOW_BUDGET_COMMAND))
        return manager.show_budget();
    else if (are_commands_some(input, USERS_RANKING_COMMAND))
        return manager.get_users_ranking();
    else if (are_commands_some(input, OPEN_TRANSFER_WINDOW_COMMAND))
        return manager.open_transfer_window();
    else if (are_commands_some(input, CLOSE_TRANSFER_WINDOW_COMMAND))
        return manager.close_transfer_window();
    else if (are_commands_some(input, LOGIN_COMMAND))
        return manager.login(convert_to_login_info(input));
    else if (are_commands_some(input, SIGNUP_COMMAND))
        return manager.signup(convert_to_login_info(input));
    else if (are_commands_some(input, BUY_PLAYER_COMMAND))
        return manager.buy_player(convert_to_transfer_input(input));
    else if (are_commands_some(input, SET_CAPTAIN_COMMAND))
        return manager.set_captain(convert_to_captain_input(input));
    else if (are_commands_some(input, REGISTER_ADMIN_COMMAND))
        return manager.register_admin(convert_to_login_info(input));
    else if (are_commands_some(input, SELL_PLAYER_COMMAND))
        return manager.sell_player(convert_to_transfer_input(input));
    else if (are_commands_some(input, TEAM_LIST_COMMAND))
        return manager.get_team_list(convert_to_team_list_input(input));
    else if (are_commands_some(input, BEST_TEAM_COMMAND))
        return manager.get_best_team(convert_to_best_team_input(input));
    else if (are_commands_some(input, GET_SQUAD_COMMAND))
        return manager.get_fantasy_team(convert_to_fantasy_team_name(input));
    else if (are_commands_some(input, TEAM_PLAYERS_COMMAND))
        return manager.get_team_players(convert_to_team_players_input(input));
    else if (are_commands_some(input, MATCH_REPORT_COMMAND))
        return manager.get_week_matches_report(convert_to_matches_input(input));
    else
        return make_shared<Massage_reporter>(BAD_REQUEST_MASSAGE + "\n");
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

int convert_to_best_team_input(vector<string> input)
{
    check_best_team_input(input);

    if (input.size() == BEST_TEAM_COMMAND_MIN_SIZE)
        return Time::get_week();

    return stoi(input[BEST_TEAM_COMMAND_MAX_SIZE - 1]);
}

int convert_to_matches_input(vector<string> input)
{
    check_matches_input(input);

    if (input.size() == MATCHES_COMMAND_MIN_SIZE)
        return Time::get_week();

    return stoi(input[MATCHES_COMMAND_MAX_SIZE - 1]);
}

int convert_to_team_list_input(vector<string> input)
{
    if (input.size() != TEAM_LIST_COMMAND_SIZE)
        throw BAD_REQUEST_MASSAGE;
    return Time::get_week();
}

string convert_to_captain_input(vector<string> input)
{
    check_captain_input(input);

    return merge_input(input, CAPTAIN_NAME_INDEX);
}

Team_players_input convert_to_team_players_input(vector<string> input)
{
    check_team_player_input(input);

    Team_players_input output;
    output.name = replace_char(input[TEAM_NAME_COMMAND_INDEX],
                               TEAM_NAME_SEPARATOR, ' ');
    output.week = Time::get_week();

    if (input.size() <= TEAM_PLAYERS_COMMAND_SIZE)
    {
        output.is_sort_with_rank = false;
        output.just_special_post = false;
        return output;
    }

    output.is_sort_with_rank = find(input.begin(), input.end(),
                                    SORT_BY_SCORE_COMMAND) != input.end();
    output.just_special_post = is_a_post(input[POST_COMMAND_INDEX]);
    output.post = input[POST_COMMAND_INDEX];

    return output;
}

Fantasy_input convert_to_fantasy_team_name(vector<string> input)
{
    Fantasy_input output;
    output.have_name = true;
    if (input.size() == GET_SQUAD_COMMAND_SIZE)
        output.name = input[USERNAME_INDEX];
    else
        output.have_name = false;
    return output;
}

bool is_a_post(string input)
{
    return find(POSTS.begin(), POSTS.end(), input) != POSTS.end();
}

string replace_char(string input, char str_char, char final_char)
{
    string output = "";
    vector<string> separated = separate_line(input, str_char);

    for (auto i : separated)
        output += i + final_char;
    if (output.size() != 0)
        output.pop_back();

    return output;
}

string merge_input(vector<string> input, size_t start_pos)
{
    string output = "";

    for (size_t i = start_pos; i < input.size(); i++)
        output += input[i] + " ";
    output.pop_back();

    return output;
}

string convert_to_transfer_input(vector<string> input)
{
    check_transfer_input(input);

    return merge_input(input, TRANSFER_COMMAND_SIZE - 1);
}

void check_transfer_input(vector<string> input)
{
    if (input.size() < TRANSFER_COMMAND_SIZE)
        throw BAD_REQUEST_MASSAGE;
}

void check_team_player_input(vector<string> input)
{
    if (input.size() > TEAM_PLAYERS_COMMAND_MAX_SIZE)
        throw BAD_REQUEST_MASSAGE;
    if (input.size() < TEAM_PLAYERS_COMMAND_SIZE)
        throw BAD_REQUEST_MASSAGE;
    if (input[3] != "team_name")
        throw BAD_REQUEST_MASSAGE;
    if (input.size() == 6)
        if (input[5] != "rank" &&
            find(POSTS.begin(), POSTS.end(), input[5]) == POSTS.end())
            throw BAD_REQUEST_MASSAGE;
    if (input.size() == 7)
        if (input[6] != "rank")
            throw BAD_REQUEST_MASSAGE;
        else if (find(POSTS.begin(), POSTS.end(), input[5]) == POSTS.end())
            throw BAD_REQUEST_MASSAGE;
        else
            return;
    else
        return;
}

void check_matches_input(vector<string> input)
{
    if (input.size() != MATCHES_COMMAND_MAX_SIZE &&
        input.size() != MATCHES_COMMAND_MIN_SIZE)
        throw BAD_REQUEST_MASSAGE;

    if (input.size() == MATCHES_COMMAND_MAX_SIZE)
        if (input[WEEK_NUM_INDEX] != WEEK_NUM_COMMAND)
            throw BAD_REQUEST_MASSAGE;
        else if (!is_number(input[WEEK_NUM_INDEX + 1]))
            throw BAD_REQUEST_MASSAGE;
        else if (Time::get_week() < stoi(input[WEEK_NUM_INDEX + 1]))
            throw BAD_REQUEST_MASSAGE;
        else
            return;
    else
        return;
}

void check_captain_input(vector<string> input)
{
    if (input.size() < CAPTAIN_COMMAND_SIZE)
        throw BAD_REQUEST_MASSAGE;
}

void check_sso_input(vector<string> input)
{
    if (input.size() != LOGIN_COMMAND_SIZE ||
        input[PASSWORD_INDEX - 1] != PASSWORD_COMMAND)
        throw BAD_REQUEST_MASSAGE;
}

void check_best_team_input(vector<string> input)
{
    if (input.size() != BEST_TEAM_COMMAND_MAX_SIZE &&
        input.size() != BEST_TEAM_COMMAND_MIN_SIZE)
        throw BAD_REQUEST_MASSAGE;

    if (input.size() == BEST_TEAM_COMMAND_MAX_SIZE)
        if (input[WEEK_NUM_INDEX] != WEEK_NUM_COMMAND)
            throw BAD_REQUEST_MASSAGE;
        else if (!is_number(input[WEEK_NUM_INDEX + 1]))
            throw BAD_REQUEST_MASSAGE;
        else if (Time::get_week() < stoi(input[WEEK_NUM_INDEX + 1]))
            throw BAD_REQUEST_MASSAGE;
        else
            return;
    else
        return;
}

bool is_number(string num)
{
    for (auto i : num)
        if (!isdigit(i))
            return false;
    return true;
}
