#pragma once

#include "define.hpp"
#include "manager.hpp"
#include "reporter.hpp"

vector<string> separate_line(string line);
vector<Question_input> read_file(string file_path);
void print_report_CLI(vector<shared_ptr<Reporter>> reports);
vector<shared_ptr<Reporter>> process(vector<string> input, Manager &manager);