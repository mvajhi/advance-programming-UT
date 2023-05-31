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
        if (input.size() == 0)
            return make_shared<Massage_reporter>(BAD_REQUEST_MASSAGE + "\n");
        else if (are_commands_some(input, SIGNUP_COMMAND))
            return manager.signup(convert_to_login_info(input));
        else if (are_commands_some(input, LOGIN_COMMAND))
            return manager.login(convert_to_login_info(input));
        else if (are_commands_some(input, LOGOUT_COMMAND))
            return manager.logout();
        else if (are_commands_some(input, BEST_TEAM_COMMAND))
            return manager.get_best_team(convert_to_best_team_input(input, manager));
        else if (are_commands_some(input, USERS_RANKING))
            return manager.get_users_ranking();
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
    manager.import_real_teams(import_league());
    manager.import_real_weeks(import_league_weeks());
}

User_login_info convert_to_login_info(vector<string> input)
{
    User_login_info output;

    if (input.size() != LOGIN_COMMAND_SIZE)
        throw make_shared<Massage_reporter>(BAD_REQUEST_MASSAGE + "\n");

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

Team_data read_team(string line)
{
    Team_data new_team;
    vector<string> players = separate_line(line, ROLE_SEPARATOR);
    new_team.team_name = players[TEAM_NAME_INDEX];
    new_team.gk = separate_line(players[GK_INDEX], PLAYER_SEPARATOR);
    new_team.df = separate_line(players[DF_INDEX], PLAYER_SEPARATOR);
    new_team.mf = separate_line(players[MF_INDEX], PLAYER_SEPARATOR);
    new_team.fw = separate_line(players[FW_INDEX], PLAYER_SEPARATOR);
    return new_team;
}

League_data import_league()
{
    string line;

    League_data premier_league;
    ifstream file(LEAGUE_ADDRESS);
    if (!file.is_open())
    {
        cout << " problem in opening file" << endl;
    }
    getline(file, line);
    while (getline(file, line))
    {
        Team_data new_pl_team = read_team(line);
        shared_ptr<Team_data> new_team = make_shared<Team_data>(new_pl_team);
        premier_league.teams.insert(make_pair(new_team->team_name, new_team));
    }
    return premier_league;
}

Player_status initialize_status(double score)
{
    Player_status target;
    target.injured = false;
    target.is_played = true;
    target.red_card = false;
    target.score = score;
    target.yellow_card = 0;
    return target;
}

int convert_to_best_team_input(vector<string> input, Manager &manager)
{
    if (input.size() < BEST_TEAM_COMMAND_SIZE)
        return manager.get_week();
    return stoi(input[BEST_TEAM_COMMAND_SIZE - 1]);
}

map<string, Player_status> get_score_from_csv(vector<string> scores)
{
    map<string, Player_status> players_status;
    Player_status target_player_status;
    for (string player_score : scores)
    {
        vector<string> info = separate_line(player_score, TEAM_SEPARATOR);
        target_player_status = initialize_status(stod(info[SCORE_POINT_INDEX]));
        players_status.insert(make_pair(info[TEAM_NAME_INDEX], target_player_status));
    }
    return players_status;
}

vector<string> choose_score_subset(vector<string> game_info)
{
    vector<string> subset;
    for (size_t i = 0; i < game_info.size(); i++)
    {
        subset.push_back(game_info[i]);
    }
    return subset;
}

// string get_team_names
void update_with_yellow_card(map<string, Player_status> &player_scores, vector<string> yellow_cards)
{
    for (string player : yellow_cards)
        player_scores[player].yellow_card++;
}

void update_with_red_card(map<string, Player_status> &player_scores, vector<string> red_cards)
{
    for (string player : red_cards)
        player_scores[player].red_card = true;
}

void update_with_injured_players(map<string, Player_status> &player_scores, vector<string> injured_players)
{
    for (string player : injured_players)
        player_scores[player].injured = true;
}

Game_input read_game_information(string line)
{
    vector<string> game_info = separate_line(line, ROLE_SEPARATOR, false);
    vector<string> team_names = separate_line(game_info[TEAM_NAME_INDEX], TEAM_SEPARATOR);
    vector<string> team_results = separate_line(game_info[RESULT_INDEX], TEAM_SEPARATOR);
    vector<string> injured_players = separate_line(game_info[INJURED_PLAYER_INDEX], PLAYER_SEPARATOR);
    vector<string> yellow_card_players = separate_line(game_info[YELLOW_CARD_INDEX], PLAYER_SEPARATOR);
    vector<string> red_card_players = separate_line(game_info[RED_CARD_INDEX], PLAYER_SEPARATOR);
    vector<string> score_players = separate_line(game_info[SCORES_INDEX], PLAYER_SEPARATOR);
    vector<string> scores_vec = choose_score_subset(score_players);
    // // TODO
    // cout << line << endl;
    // for (auto i : game_info)
    //     cout << "GAM??    " << i << endl;
    // for (auto i : team_names)
    //     cout << "TNA??    " << i << endl;
    // for (auto i : team_results)
    //     cout << "TRE??    " << i << endl;
    // for (auto i : injured_players)
    //     cout << "INP??    " << i << endl;
    // for (auto i : yellow_card_players)
    //     cout << "YCP??    " << i << endl;
    // for (auto i : red_card_players)
    //     cout << "RCP??    " << i << endl;
    // for (auto i : scores_vec)
    //     cout << "SCO??    " << i << endl;

    ///////////
    map<string, Player_status> player_scores = get_score_from_csv(scores_vec);
    update_with_injured_players(player_scores, injured_players);
    update_with_yellow_card(player_scores, yellow_card_players);
    update_with_red_card(player_scores, red_card_players);
    /////////////

    Game_input game_details;
    game_details.team1.first = team_names[TEAM1_INDEX];
    game_details.team2.first = team_names[TEAM2_INDEX];
    game_details.team1.second = stoi(team_results[TEAM1_INDEX]);
    game_details.team2.second = stoi(team_results[TEAM2_INDEX]);
    game_details.players_status = player_scores;
    return game_details;
}

Week_state import_week_state(int week_num)
{
    string line;
    Week_state new_week;
    vector<Game_input> weeks_games;
    ifstream file(WEEK_ADDRESS + to_string(week_num) + CSV_FORMAT);
    if (!file.is_open())
        cout << "problem in opening file" << endl;

    getline(file, line);
    while (getline(file, line))
        weeks_games.push_back(read_game_information(line));
    new_week.weeks_games = weeks_games;

    // // TODO rm
    // // for (auto i : leagues_weeks)
    // for (auto j : weeks_games)
    // for (auto k : j.players_status)
    // cout << "what???   " << k.first << "\t\tis " << k.second.score << " in week " << week_num << endl;
    return new_week;
}

map<int, vector<Game_input>> import_league_weeks()
{
    map<int, vector<Game_input>> leagues_weeks;
    for (int week_num = FIRST_WEEK; week_num <= FINAL_WEEK; week_num++)
        leagues_weeks.insert(make_pair(week_num, import_week_state(week_num).weeks_games));
    // // TODO rm
    // for (auto i : leagues_weeks)
    // for (auto j : i.second)
    // for (auto k : j.players_status)
    // cout << "what???   " << k.first << "\t\tis " << k.second.score << " in week " << i.first << endl;

    return leagues_weeks;
}
