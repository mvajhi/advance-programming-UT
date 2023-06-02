#include "match.hpp"

Match::Match(
    shared_ptr<Team> team1_ptr, int goal1, shared_ptr<Team> team2_ptr, int goal2)
{
    team1 = make_pair(team1_ptr, goal1);
    team2 = make_pair(team2_ptr, goal2);
}
