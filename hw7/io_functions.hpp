#pragma once
#include "define.hpp"
#include "manager.hpp"
#include "reporter.hpp"

void import_files(Manager &manager);
vector<string> separate_line(string line, char separator = ' ', bool ignore_tmp = true);
shared_ptr<Reporter> proccess(vector<string> input, Manager &manager);
void check_arg_count(vector<string> input, size_t count);
User_login_info convert_to_login_info(vector<string> input);
bool are_commands_some(vector<string> input, string command);
Team_data read_team(string line);
League_data import_league();
Week_state import_week_state(int week_num);
Game_input read_game_information(string line);
map<int, vector<Game_input>> import_league_weeks();
void update_with_injured_players(map<string, Player_status> &player_scores, vector<string> injured_players);
void update_with_red_card(map<string, Player_status> &player_scores, vector<string> red_cards);
void update_with_yellow_card(map<string, Player_status> &player_scores, vector<string> yellow_cards);
vector<string> choose_score_subset(vector<string> game_info);
map<string, Player_status> get_score_from_csv(vector<string> scores);
Player_status initialize_status(double score);
int convert_to_best_team_input(vector<string> input, Manager &manager);
int convert_to_team_list_input(vector<string> input, Manager &manager);
Team_players_input convert_to_team_players_input(vector<string> input, Manager &manager);
bool is_a_post(string input);
string replace_char(string input, char str_char, char final_char);

