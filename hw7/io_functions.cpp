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
    else if (are_commands_some(input, SIGNUP_COMMAND))
        return manager.signup(convert_to_login_info(input));
    else if (are_commands_some(input, LOGIN_COMMAND))
        return manager.login(convert_to_login_info(input));
    else if (are_commands_some(input, LOGOUT_COMMAND))
        return manager.logout();
    else if (are_commands_some(input, REGISTER_ADMIN_COMMAND))
        return manager.register_admin(convert_to_login_info(input));
    else if (are_commands_some(input, BEST_TEAM_COMMAND))
        return manager.get_best_team(convert_to_best_team_input(input));
    else if (are_commands_some(input, TEAM_PLAYERS_COMMAND))
        return manager.get_team_players(convert_to_team_players_input(input));
    else if (are_commands_some(input, TEAM_LIST_COMMAND))
        return manager.get_team_list(convert_to_team_list_input(input));
    else if (are_commands_some(input, USERS_RANKING_COMMAND))
        return manager.get_users_ranking();
    else if (are_commands_some(input, PASS_WEEK_COMMAND))
        return manager.pass_week();
    else if (are_commands_some(input, OPEN_TRANSFER_WINDOW_COMMAND))
        return manager.open_transfer_window();
    else if (are_commands_some(input, CLOSE_TRANSFER_WINDOW_COMMAND))
        return manager.close_transfer_window();
    else if (are_commands_some(input, BUY_PLAYER_COMMAND))
        return manager.buy_player(convert_to_transfer_input(input));
    else if (are_commands_some(input, SELL_PLAYER_COMMAND))
        return manager.sell_player(convert_to_transfer_input(input));
    else if (are_commands_some(input, GET_SQUAD_COMMAND))
        return manager.get_fantasy_team(convert_to_fantasy_team_name(input));
    else if (are_commands_some(input, MATCH_REPORT_COMMAND))
        return manager.get_week_matches_report(convert_to_best_team_input(input));
        // TODO change arg matches report
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

int convert_to_best_team_input(vector<string> input)
{
    check_best_team_input(input);

    if (input.size() == BEST_TEAM_COMMAND_MIN_SIZE)
        return Time::get_week();

    return stoi(input[BEST_TEAM_COMMAND_MAX_SIZE - 1]);
}

int convert_to_team_list_input(vector<string> input)
{
    if (input.size() != TEAM_LIST_COMMAND_SIZE)
        throw BAD_REQUEST_MASSAGE;
    return Time::get_week();
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

string convert_to_fantasy_team_name(vector<string> input)
{
    // TODO check input
    if (input.size() == GET_SQUAD_COMMAND_SIZE)
        return input[USERNAME_INDEX];
    else
        // TODO
        return "user_logged";
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

string convert_to_transfer_input(vector<string> input)
{
    check_transfer_input(input);

    string output = "";
    for (size_t i = TRANSFER_COMMAND_SIZE - 1; i < input.size(); i++)
        output += input[i] + " ";
    output.pop_back();

    return output;
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
        {
        }
    else
    {
    }
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
        {
        }
    else
    {
    }
}

bool is_number(string num)
{
    for (auto i : num)
        if (!isdigit(i))
            return false;
    return true;
}

map<string, Player_status> get_score_from_csv(vector<string> scores)
{
    map<string, Player_status> players_status;

    for (string player_score : scores)
        players_status.insert(create_new_score(player_score));

    return players_status;
}

map<string, Player_status> create_player_status(Match_info info)
{
    map<string, Player_status> player_scores = get_score_from_csv(
        info.score_players);

    update_with_injured_players(player_scores, info.injured_players);
    update_with_yellow_card(player_scores, info.yellow_card_players);
    update_with_red_card(player_scores, info.red_card_players);

    return player_scores;
}

vector<string> choose_score_subset(vector<string> game_info)
{
    vector<string> subset;

    for (size_t i = 0; i < game_info.size(); i++)
        subset.push_back(game_info[i]);

    return subset;
}

pair<string, Player_status> create_new_score(string player_score)
{
    Player_status target_player_status;

    vector<string> info = separate_line(player_score, TEAM_SEPARATOR);
    target_player_status = initialize_status(stod(info[SCORE_POINT_INDEX]));

    return make_pair(info[TEAM_NAME_INDEX], target_player_status);
}

Game_input convert_to_game_input(Match_info game)
{
    Game_input game_details;

    game_details.team1.first = game.team_names[TEAM1_INDEX];
    game_details.team2.first = game.team_names[TEAM2_INDEX];
    game_details.team1.second = stoi(game.team_results[TEAM1_INDEX]);
    game_details.team2.second = stoi(game.team_results[TEAM2_INDEX]);
    game_details.players_status = create_player_status(game);

    return game_details;
}

// string get_team_names
void update_with_yellow_card(map<string, Player_status> &player_scores,
                             vector<string> yellow_cards)
{
    for (string player : yellow_cards)
        player_scores[player].yellow_card++;
}

void update_with_red_card(map<string, Player_status> &player_scores,
                          vector<string> red_cards)
{
    for (string player : red_cards)
        player_scores[player].red_card = true;
}

void update_with_injured_players(map<string, Player_status> &player_scores,
                                 vector<string> injured_players)
{
    for (string player : injured_players)
        player_scores[player].injured = true;
}

// TODO break it
Game_input read_game_information(string line)
{
    Match_info game_info = convert_line_to_raw_info(line);

    Game_input game_details = convert_to_game_input(game_info);

    return game_details;
}

Week_state import_week_state(int week_num)
{
    string line;
    Week_state new_week;
    vector<Game_input> weeks_games;
    ifstream file(WEEK_ADDRESS + to_string(week_num) + CSV_FORMAT);

    getline(file, line);
    while (getline(file, line))
        weeks_games.push_back(read_game_information(line));
    new_week.weeks_games = weeks_games;

    return new_week;
}

map<int, vector<Game_input>> import_league_weeks()
{
    map<int, vector<Game_input>> leagues_weeks;
    for (int week_num = FIRST_WEEK; week_num <= FINAL_WEEK; week_num++)
        leagues_weeks.insert(
            make_pair(week_num, import_week_state(week_num).weeks_games));

    return leagues_weeks;
}

Match_info convert_line_to_raw_info(string line)
{
    Match_info output;

    vector<string> game_info = separate_line(
        line, ROLE_SEPARATOR, false);

    output.team_names = separate_line(
        game_info[TEAM_NAME_INDEX], TEAM_SEPARATOR);

    output.team_results = separate_line(
        game_info[RESULT_INDEX], TEAM_SEPARATOR);

    output.injured_players = separate_line(
        game_info[INJURED_PLAYER_INDEX], PLAYER_SEPARATOR);

    output.yellow_card_players = separate_line(
        game_info[YELLOW_CARD_INDEX], PLAYER_SEPARATOR);

    output.red_card_players = separate_line(
        game_info[RED_CARD_INDEX], PLAYER_SEPARATOR);

    output.score_players = separate_line(
        game_info[SCORES_INDEX], PLAYER_SEPARATOR);

    output.score_players = choose_score_subset(output.score_players);

    return output;
}
