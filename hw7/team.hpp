#pragma once

#include "define.hpp"
#include "player.hpp"

class Team
{
private:
    string name;
    map<string, vector<shared_ptr<Player>>> players;
    map<int, Team_status> weeks_status;

public:
    Team();
    Team_status get_status(int week);
    vector<shared_ptr<Player>> get_players(bool is_sort, bool have_role, string role);
};
