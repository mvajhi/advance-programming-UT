#pragma once

#include "define.hpp"
#include "question.hpp"


class Reporter
{
public:
    virtual string get_cli_report() = 0;
};

class Question_reporter : public Reporter
{
private:
    shared_ptr<Question> q;
public:
    Question_reporter(shared_ptr<Question> question_);
    string get_cli_report();
    string get_cli_short_report();
    string get_cli_full_report();
    bool is_correct();
};

class End_reporter : public Reporter
{
private:
    vector<shared_ptr<Question_reporter>> reports;
    string calculate_grade();
public:
    End_reporter(vector<shared_ptr<Question_reporter>> reports_);
    string get_cli_report();
};