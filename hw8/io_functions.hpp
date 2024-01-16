#pragma once

#include "define.hpp"
#include "manager.hpp"
#include "reporter.hpp"

vector<Question_input> read_file(string file_path);
vector<string> separate_line(string line);
vector<shared_ptr<Reporter>> command_proccess(vector<string> input, Manager &manager);
void print_report_CLI(vector<shared_ptr<Reporter>> reports);