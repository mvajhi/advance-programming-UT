#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//define
const int FILE_PATH_INDEX_ARG = 1;

typedef string Type;
const Type SINGLE_ANSWER = "single_answer";
const Type MULTIPLE_ANSWER = "multiple_answer";
const Type SHORT_ANSWER = "short_answer";

typedef string State;
const State TRUE_ANS = "correct";
const State WRONG_ANS = "wrong";
const State NO_ANS = "no_answer";

const string CLI_SEPARATE1 = " | ";
const string CLI_SEPARATE2 = ", ";

const string CLI_SUBMIT = "submit_answer";
const string CLI_END = "finish_exam";

// struct
struct Question_input
{
    int number;
    Type type;
    vector<string> question_body;
    string answer;
};

struct Submit_input
{
    int number;
    string answer;
};