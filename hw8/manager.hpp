#pragma once

#include "define.hpp"
#include "question.hpp"

class Manager
{
private:
    map<int, shared_ptr<Question>> questions;

public:
    Manager();
};