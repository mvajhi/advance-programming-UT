#pragma once

#include "define.hpp"
#include "io_functions.hpp"

League_data import_league();
Team_data read_team(string line);
Week_state import_week_state(int week_num);
Player_status initialize_status(double score);
Game_input read_game_information(string line);
Match_info convert_line_to_raw_info(string line);
Game_input convert_to_game_input(Match_info game);
map<int, vector<Game_input>> import_league_weeks();
vector<Player_info> read_player(vector<string> input);
vector<string> choose_score_subset(vector<string> game_info);
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
void update_with_key_changes(
        map<string, Player_status> &players_status,
        vector<string> goals,vector<string> assist
        );