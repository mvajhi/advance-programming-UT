#include "match.hpp"

Match::Match(
    shared_ptr<Team> team1, int goal1, shared_ptr<Team> team2, int goal2)
{
    make_pair(team1, goal1);
    make_pair(team2, goal2);
}
