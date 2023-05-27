#pragma once

#include "define.hpp"
#include "team.hpp"
#include "reporter.hpp"

class Match
{
private:
    pair<Team, int> team1;
    pair<Team, int> team2;

public:
    Match();
    shared_ptr<Reporter> get_summery();
};