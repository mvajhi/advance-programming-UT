#pragma once
#include "define.hpp"
#include "manager.hpp"
#include "reporter.hpp"

vector<string> separate_line(string line, char separator = ' ');
shared_ptr<Reporter> proccess(vector<string> input, Manager &manager);
void check_arg_count(vector<string> input, size_t count);
Mission_input convert_mission_input(vector<string> input);
Mission_input create_mission_input(vector<string> input);
void check_mission_input(Mission_input input);
Travel_input create_travel_input(vector<string> input);
void check_travel_input(Travel_input input);
Travel_input convert_travel_input(vector<string> input);
Assign_input convert_assign_input(vector<string> input);
Driver_report_input convert_report_input(vector<string> input);
