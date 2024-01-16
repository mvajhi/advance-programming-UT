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

// enum
enum Question_type
{
    single_answer,
    multiple_answer,
    short_answer
};

// struct
struct Question_input
{
    Question_type type;
    vector<string> question_body;
    string answer;
};
