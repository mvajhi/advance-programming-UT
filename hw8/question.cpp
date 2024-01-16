#include "question.hpp"

Question::Question(Question_input input)
{
    is_ans = false;
    number = input.number;
}

State Question::get_user_ans_state()
{
    if (!is_ans)
        return NO_ANS;
    if (is_true_ans())
        return TRUE_ANS;
    else
        return WRONG_ANS;
}

string Question::get_q_txt()
{
    return question_txt;
}

string Question::get_q_num()
{
    return to_string(number);
}

void Q_single_answer::set_question_body(vector<string> raw_body)
{
    question_txt = raw_body.front();
    options = vector<string>(raw_body.begin() + 2, raw_body.end());
}

void Q_single_answer::set_answer(string raw_answer)
{
    answer = stoi(raw_answer);
}

bool Q_single_answer::is_true_ans()
{
    return user_answer == answer;
}

Q_single_answer::Q_single_answer(Question_input input)
    : Question(input)
{
    set_question_body(input.question_body);
    set_answer(input.answer);
}

void Q_single_answer::set_user_ans(string raw_answer)
{
    user_answer = stoi(raw_answer);
    is_ans = true;
}

string Q_single_answer::get_ans()
{
    return to_string(answer);
}

string Q_single_answer::get_user_ans()
{
    return to_string(user_answer);
}

void Q_multiple_answer::set_question_body(vector<string> raw_body)
{
    question_txt = raw_body.front();
    options = vector<string>(raw_body.begin() + 2, raw_body.end());
}

vector<int> Q_multiple_answer::convert_to_ans(string raw_answer)
{
    vector<int> output;
    istringstream stream_ans(raw_answer);
    string num;
    while (stream_ans >> num)
        output.push_back(stoi(num));
    return output;
}

string Q_multiple_answer::convert_ans_to_str(vector<int> answer_)
{
    string output = "";
    for (int number : answer_)
        output += to_string(number) + " ";
    output.pop_back();
    return output;
}

void Q_multiple_answer::set_answer(string raw_answer)
{
    answer = convert_to_ans(raw_answer);
}

bool Q_multiple_answer::is_true_ans()
{
    vector<int> sort_ans = answer;
    vector<int> sort_user_ans = user_answer;
    sort(sort_ans.begin(), sort_ans.end());
    sort(sort_user_ans.begin(), sort_user_ans.end());

    if (sort_ans == sort_user_ans)
        return true;
    return false;
}

Q_multiple_answer::Q_multiple_answer(Question_input input)
    : Question(input)
{
    set_question_body(input.question_body);
    set_answer(input.answer);
}

void Q_multiple_answer::set_user_ans(string raw_answer)
{
    user_answer = convert_to_ans(raw_answer);
    is_ans = true;
}

string Q_multiple_answer::get_ans()
{
    return convert_ans_to_str(answer);
}

string Q_multiple_answer::get_user_ans()
{
    return convert_ans_to_str(user_answer);
}

void Q_short_answer::set_question_body(vector<string> raw_body)
{
    question_txt = raw_body[0];
}

void Q_short_answer::set_answer(string raw_answer)
{
    answer = raw_answer;
}

bool Q_short_answer::is_true_ans()
{
    return answer == user_answer;
}

Q_short_answer::Q_short_answer(Question_input input)
    : Question(input)
{
    set_question_body(input.question_body);
    set_answer(input.answer);
}

void Q_short_answer::set_user_ans(string raw_answer)
{
    user_answer = raw_answer;
    is_ans = true;
}

string Q_short_answer::get_ans()
{
    return answer;
}

string Q_short_answer::get_user_ans()
{
    return user_answer;
}
