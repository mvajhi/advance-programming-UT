#pragma once

#include "define.hpp"
#include "question.hpp"


class Reporter
{
public:
    virtual string get_cli_short_report() = 0;
    virtual string get_cli_full_report() = 0;
};

class Question_reporter : public Reporter
{
private:
    shared_ptr<Question> q;
public:
    Question_reporter(shared_ptr<Question> question_);
    string get_cli_short_report();
    string get_cli_full_report();
};