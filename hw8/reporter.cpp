#include "reporter.hpp"


Question_reporter::Question_reporter(shared_ptr<Question> question_)
{
    q = question_;
}

string Question_reporter::get_cli_short_report()
{
    return q->get_user_ans_state() + " answer.\n";
}

string Question_reporter::get_cli_full_report()
{
    State state = q->get_user_ans_state();
    string output = q->get_q_num()+ " " + state;
    if (state != TRUE_ANS)
        output += CLI_SEPARATE1 + "correct answer: " + q->get_ans();
    if (state == WRONG_ANS)
        output += CLI_SEPARATE2 + "your answer: " + q->get_user_ans();
    return output + "\n";
}
