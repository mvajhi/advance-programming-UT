#pragma once

#include "define.hpp"
#include "question.hpp"
#include "reporter.hpp"

class Manager
{
private:
    map<int, shared_ptr<Question>> questions;
    bool end;

public:
    Manager(vector<Question_input> questions_);
    shared_ptr<Reporter> submit(Submit_input input);
    shared_ptr<Reporter> get_end_report();
    void end_quiz();
    bool is_end();
};