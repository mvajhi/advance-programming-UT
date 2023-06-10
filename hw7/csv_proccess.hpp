#pragma once

#include "define.hpp"
#include "io_functions.hpp"

League_data import_league();
Team_data read_team(string line);
Week_state import_week_state(int week_num);
Match_detail read_game_information(string line);
Match_info convert_line_to_raw_info(string line);
map<int, vector<Match_detail>> import_league_weeks();
Match_detail convert_to_match_detail(Match_info game);
vector<Player_info> read_player(vector<string> input);
map<string, Player_status> create_player_status (Match_info info);
pair<string, Player_status> create_new_status(string player_name);
map<string, Player_status> get_teamsheet_from_csv(vector<string> team1_players,vector<string> team2_players);
void update_with_injured_players(
    map<string, Player_status> &player_scores,
    vector<string> injured_players);

void update_with_red_card(
    map<string, Player_status> &player_scores,
    vector<string> red_cards);

void update_with_yellow_card(
    map<string, Player_status> &player_scores,
    vector<string> yellow_cards);
