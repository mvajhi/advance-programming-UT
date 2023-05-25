#pragma once
#include "define.hpp"
#include "manager.hpp"
#include "reporter.hpp"

void import_files(Manager &manager);
vector<string> separate_line(string line, char separator = ' ');
shared_ptr<Reporter> proccess(vector<string> input, Manager &manager);
void check_arg_count(vector<string> input, size_t count);
User_login_info convert_to_login_info(vector<string> input);
bool are_commands_some(vector<string> input, string command);
Team read_team(string line);
League import_league();
