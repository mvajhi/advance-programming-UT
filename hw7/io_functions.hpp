#pragma once
#include "define.hpp"
#include "manager.hpp"
#include "reporter.hpp"

// CLI proccess
shared_ptr<Reporter> proccess(vector<string> input, Manager &manager);
shared_ptr<Reporter> command_proccess(vector<string> input, Manager &manager);

// tools
void check_arg_count(vector<string> input, size_t count);
bool are_commands_some(vector<string> input, string command);
string replace_char(string input, char str_char, char final_char);
vector<string> separate_line(
    string line, char separator = ' ', bool ignore_tmp = true);

// convert
int convert_to_best_team_input(vector<string> input);
int convert_to_team_list_input(vector<string> input);
string convert_to_transfer_input(vector<string> input);
User_login_info convert_to_login_info(vector<string> input);
Team_players_input convert_to_team_players_input(vector<string> input);

// check
bool is_a_post(string input);
void check_sso_input(vector<string> input);
void check_transfer_input(vector<string> input);
void check_best_team_input(vector<string> input);
void check_team_player_input(vector<string> input);

// csv import
League_data import_league();
Team_data read_team(string line);
void import_files(Manager &manager);
Week_state import_week_state(int week_num);
Player_status initialize_status(double score);
Game_input read_game_information(string line);
Match_info convert_line_to_raw_info(string line);
Game_input convert_to_game_input(Match_info game);
map<int, vector<Game_input>> import_league_weeks();
vector<string> choose_score_subset(vector<string> game_info);
map<string, Player_status> create_player_status (Match_info info);
pair<string, Player_status> create_new_score(string player_score);
map<string, Player_status> get_score_from_csv(vector<string> scores);
void update_with_injured_players(
    map<string, Player_status> &player_scores,
    vector<string> injured_players);

void update_with_red_card(
    map<string, Player_status> &player_scores,
    vector<string> red_cards);

void update_with_yellow_card(
    map<string, Player_status> &player_scores,
    vector<string> yellow_cards);
