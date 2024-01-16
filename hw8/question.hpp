#pragma once

#include "define.hpp"

class Question
{
protected:
    int number;
    string question_txt;
private:
    virtual void set_question_body(vector<string> raw_body) = 0;
    virtual void set_answer(string raw_answer) = 0;

public:
    Question(Question_input input);
};

class Q_single_answer : public Question
{
private:
    vector<string> options;
    int answer;

    void set_question_body(vector<string> raw_body);
    void set_answer(string raw_answer);
public:
    Q_single_answer(Question_input input);
};