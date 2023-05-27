#pragma once

#include "define.hpp"
#include "player.hpp"

class Team
{
private:
    string name;
    // role -> player_ptr
    map<string, vector<shared_ptr<Player>>> players;
    map<int, Team_status> weeks_status;

public:
    Team(string name_, map<string, vector<shared_ptr<Player>>> players_);
    Team_status get_status(int week);
    vector<shared_ptr<Player>> get_players(bool is_sort, bool have_role, string role);
    string get_name();
    void add_new_match(int week, int score, int ga, int gf);
};
