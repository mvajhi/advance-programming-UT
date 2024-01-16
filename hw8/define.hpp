#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <fstream>

using namespace std;

//define
const int FILE_PATH_INDEX_ARG = 1;
const string SINGLE_ANSWER = "single_answer";
const string MULTIPLE_ANSWER = "multiple_answer";
const string SHORT_ANSWER = "short_answer";

// struct
struct Question_input
{
    int number;
    string type;
    vector<string> question_body;
    string answer;
};