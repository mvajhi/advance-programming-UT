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
    cout << number << endl;
    cout << "Q_single_answer" << endl;
    cout << question_txt << endl;
    for (auto &&i : options)
        cout << i << endl;
    cout << answer << endl;
}

void Q_single_answer::set_user_ans(string raw_answer)
{
    user_answer = stoi(raw_answer);
    is_ans = true;
    cout << user_answer << endl;
}

string Q_single_answer::get_ans()
{
    return to_string(answer);
}

string Q_single_answer::get_user_ans()
{
    return to_string(user_answer);
}
