#include "csv_proccess.hpp"

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
vector<Player_info> read_player(vector<string> input)
{
    Player_info new_player ;
    vector<Player_info> players ;
    for (auto player : input)
    {
        new_player.name = separate_line(player,PRICE_SEPARATOR)[NAME_INDEX];
        new_player.price = stoi(separate_line(player,PRICE_SEPARATOR)[PRICE_INDEX]);
        players.push_back((new_player));
    }
    return players;
}
Team_data read_team(string line)
{
    Team_data new_team;
    vector<string> players = separate_line(line, ROLE_SEPARATOR);
    new_team.team_name = players[TEAM_NAME_INDEX];
    new_team.gk = read_player(separate_line(players[GK_INDEX], PLAYER_SEPARATOR));
    new_team.df = read_player(separate_line(players[DF_INDEX], PLAYER_SEPARATOR));
    new_team.mf = read_player(separate_line(players[MF_INDEX], PLAYER_SEPARATOR));
    new_team.fw = read_player(separate_line(players[FW_INDEX], PLAYER_SEPARATOR));
    return new_team;
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

Player_status initialize_status()
{
    Player_status target;
    target.injured = false;
    target.is_played = true;
    target.red_card = false;
    target.score = INITIAL_PLAYER_SCORE;
    target.yellow_card = 0;
    return target;
}

Game_input read_game_information(string line)
{
    Match_info game_info = convert_line_to_raw_info(line);

    Game_input game_details = convert_to_game_input(game_info);

    return game_details;
}

Key_change convert_to_key_change_info(vector<string> important_change)
{
    Key_change chances;
    vector<string> goal_info;
    for(auto goal : important_change)
    {
        goal_info = separate_line(goal,GOALS_ASSISTS_SEPARATOR) ;
        chances.goals.push_back(goal_info[GOAL_INDEX]);
        chances.assists.push_back((goal_info[ASSISTS_INDEX]));
    }
    return chances;
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

    output.goals_and_assists = convert_to_key_change_info(separate_line(
            game_info[GOALS_ASSIST_INDEX], PLAYER_SEPARATOR));

    output.team1_players = separate_line(
            game_info[TEAM1_PLAYERS_INDEX],PLAYER_SEPARATOR);

    output.team2_players = separate_line(
            game_info[TEAM2_PLAYERS_INDEX],PLAYER_SEPARATOR);

    return output;
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

map<int, vector<Game_input>> import_league_weeks()
{
    map<int, vector<Game_input>> leagues_weeks;
    for (int week_num = FIRST_WEEK; week_num <= FINAL_WEEK; week_num++)
        leagues_weeks.insert(
            make_pair(week_num, import_week_state(week_num).weeks_games));

    return leagues_weeks;
}

map<string, Player_status> create_player_status(Match_info info)
{
    map<string , Player_status> players_status = get_teamsheet_from_csv(info.team1_players,info.team2_players);
    update_with_injured_players(players_status, info.injured_players);
    update_with_yellow_card(players_status, info.yellow_card_players);
    update_with_red_card(players_status, info.red_card_players);
    update_with_key_changes(players_status,info.goals_and_assists.goals , info.goals_and_assists.assists);

    return players_status;
}

pair<string, Player_status> create_new_status(string player_name)
{
    Player_status target_player_status;

    target_player_status = initialize_status();

    return make_pair(player_name, target_player_status);
}

map<string, Player_status> get_teamsheet_from_csv(vector<string> team1_players, vector<string> team2_players)
{
    map<string, Player_status> players_status;

    for (string player : team1_players)
        players_status.insert(create_new_status(player));
    for (string player : team2_players)
        players_status.insert(create_new_status(player));
    return players_status;
}

// string get_team_names
void update_with_yellow_card(map<string, Player_status> &players_status,
                             vector<string> yellow_cards)
{
    for (string player : yellow_cards)
        players_status[player].yellow_card++;
}

void update_with_red_card(map<string, Player_status> &players_status,
                          vector<string> red_cards)
{
    for (string player : red_cards)
        players_status[player].red_card = true;
}

void update_with_injured_players(map<string, Player_status> &players_status,
                                 vector<string> injured_players)
{
    for (string player : injured_players)
        players_status[player].injured = true;
}

void update_with_key_changes(map<string, Player_status> &players_status,
                  vector<string> goals,vector<string> assist)
{
    for (size_t goal_number = 0 ; goal_number < goals.size() ; goal_number++)
    {
        if (assist[goal_number] != OWN_GOAL_COMMAND)
            players_status[goals[goal_number]].goal++;
        else
            players_status[goals[goal_number]].own_goal++;
    }
}


