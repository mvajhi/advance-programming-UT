#include "reporter.hpp"

Question_reporter::Question_reporter(shared_ptr<Question> question_)
{
    q = question_;
}

string Question_reporter::get_cli_report()
{
    return get_cli_short_report();
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

bool Question_reporter::is_correct()
{
    return q->get_user_ans_state() == TRUE_ANS;
}

End_reporter::End_reporter(vector<shared_ptr<Question_reporter>> reports_)
{
    reports = reports_;
}

string End_reporter::get_cli_report()
{
    string output = "";
    for (auto &&r : reports)
        output += r->get_cli_full_report();
    output += "final grade: " + calculate_grade() + "\n";
    return output;
}

string End_reporter::calculate_grade()
{
    int sum = 0;
    for (auto &&r : reports)
        sum += r->is_correct();
    
    float grade = float(sum) / float(reports.size()) * 100;
    string output = to_string(grade);
    output = output.substr(0, output.find('.') + 2);
    return output;
}