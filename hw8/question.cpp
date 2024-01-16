#include "question.hpp"

Question::Question(Question_input input)
{
    number = input.number;
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

