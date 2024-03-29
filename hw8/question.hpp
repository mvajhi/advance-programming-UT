#pragma once

#include "define.hpp"

class Question
{
protected:
    int number;
    bool is_ans;
    string question_txt;

private:
    virtual void set_question_body(vector<string> raw_body) = 0;
    virtual void set_answer(string raw_answer) = 0;
    virtual bool is_true_ans() = 0;

public:
    Question(Question_input input);
    virtual void set_user_ans(string raw_answer) = 0;

    // getter
    string get_q_txt();
    string get_q_num();
    virtual string get_ans() = 0;
    virtual string get_user_ans() = 0;
    virtual State get_user_ans_state();
};

class Q_single_answer : public Question
{
private:
    vector<string> options;
    int answer;
    int user_answer;

    void set_question_body(vector<string> raw_body);
    void set_answer(string raw_answer);
    bool is_true_ans();

public:
    Q_single_answer(Question_input input);
    void set_user_ans(string raw_answer);

    // getter
    string get_ans();
    string get_user_ans();
};

class Q_multiple_answer : public Question
{
private:
    vector<string> options;
    vector<int> answer;
    vector<int> user_answer;

    bool is_true_ans();
    void set_answer(string raw_answer);
    vector<int> convert_to_ans(string raw_answer);
    string convert_ans_to_str(vector<int> answer_);
    void set_question_body(vector<string> raw_body);

public:
    Q_multiple_answer(Question_input input);
    void set_user_ans(string raw_answer);

    // getter
    string get_ans();
    string get_user_ans();
};

class Q_short_answer : public Question
{
private:
    string answer;
    string user_answer;

    bool is_true_ans();
    void set_answer(string raw_answer);
    void set_question_body(vector<string> raw_body);

public:
    Q_short_answer(Question_input input);
    void set_user_ans(string raw_answer);

    // getter
    string get_ans();
    string get_user_ans();
};