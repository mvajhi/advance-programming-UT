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

Game_input read_game_information(string line)
{
    Match_info game_info = convert_line_to_raw_info(line);

    Game_input game_details = convert_to_game_input(game_info);

    return game_details;
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

vector<string> choose_score_subset(vector<string> game_info)
{
    vector<string> subset;

    for (size_t i = 0; i < game_info.size(); i++)
        subset.push_back(game_info[i]);

    return subset;
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

pair<string, Player_status> create_new_score(string player_score)
{
    Player_status target_player_status;

    vector<string> info = separate_line(player_score, TEAM_SEPARATOR);
    target_player_status = initialize_status(stod(info[SCORE_POINT_INDEX]));

    return make_pair(info[TEAM_NAME_INDEX], target_player_status);
}

map<string, Player_status> get_score_from_csv(vector<string> scores)
{
    map<string, Player_status> players_status;

    for (string player_score : scores)
        players_status.insert(create_new_score(player_score));

    return players_status;
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
