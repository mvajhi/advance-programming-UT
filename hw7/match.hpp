#pragma once

#include "define.hpp"
#include "team.hpp"
#include "reporter.hpp"

class Match
{
private:
    pair<shared_ptr<Team>, int> team1;
    pair<shared_ptr<Team>, int> team2;

    friend class Match_reporter;

public:
    Match(
        shared_ptr<Team> team1_ptr, int goal1,
        shared_ptr<Team> team2_ptr, int goal2);
};