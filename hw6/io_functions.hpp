#pragma once
#include "define.hpp"
#include "manager.hpp"

vector<string> separate_line(string line, char separator = ' ');
string proccess(vector<string> input, Manager &manager);
Mission_input convert_mission_input(vector<string> input);
Mission_input create_mission_input(vector<string> input);
void check_mission_input(Mission_input input);
Assign_input convert_assign_input(vector<string> input);