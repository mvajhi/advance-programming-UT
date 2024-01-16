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

// struct
struct Question_input
{
    int number;
    Type type;
    vector<string> question_body;
    string answer;
};