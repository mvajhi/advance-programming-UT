#pragma once

#include "define.hpp"
#include "manager.hpp"
#include "reporter.hpp"
#include "csv_proccess.hpp"

// CLI proccess
shared_ptr<Reporter> proccess(vector<string> input, Manager &manager);
shared_ptr<Reporter> command_proccess(vector<string> input, Manager &manager);

// tools
bool is_number(string num);
void check_arg_count(vector<string> input, size_t count);
bool are_commands_some(vector<string> input, string command);
string replace_char(string input, char str_char, char final_char);
vector<string> separate_line(
    string line, char separator = ' ', bool ignore_tmp = true);

// convert
int convert_to_matches_input(vector<string> input);
int convert_to_best_team_input(vector<string> input);
int convert_to_team_list_input(vector<string> input);
string convert_to_transfer_input(vector<string> input);
User_login_info convert_to_login_info(vector<string> input);
Fantasy_input convert_to_fantasy_team_name(vector<string> input);
Team_players_input convert_to_team_players_input(vector<string> input);

// check
bool is_a_post(string input);
void check_sso_input(vector<string> input);
void check_matches_input(vector<string> input);
void check_transfer_input(vector<string> input);
void check_best_team_input(vector<string> input);
void check_team_player_input(vector<string> input);

// csv import
void import_files(Manager &manager);
