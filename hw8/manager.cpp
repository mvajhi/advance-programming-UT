#include "manager.hpp"

Manager::Manager(vector<Question_input> questions_)
{
    end = false;
    for (auto &&q : questions_)
        if (q.type == SHORT_ANSWER)
            questions[q.number] = make_shared<Q_short_answer>(q);
        else if (q.type == MULTIPLE_ANSWER)
            questions[q.number] = make_shared<Q_multiple_answer>(q);
        else
            questions[q.number] = make_shared<Q_single_answer>(q);
}

shared_ptr<Reporter> Manager::submit(Submit_input input)
{
    questions[input.number]->set_user_ans(input.answer);
    return make_shared<Question_reporter>(questions[input.number]);
}

shared_ptr<Reporter> Manager::get_end_report()
{
    vector<shared_ptr<Question_reporter>> reports;
    for (size_t i = 1; i <= questions.size(); i++)
        reports.push_back(make_shared<Question_reporter>(questions[i]));
    
    return make_shared<End_reporter>(reports);
}

void Manager::end_quiz()
{
    end = true;
}

bool Manager::is_end()
{
    if (end)
        return true;
    for (auto &&q : questions)
        if (q.second->get_user_ans_state() == NO_ANS)
            return false;
    return true;
}
