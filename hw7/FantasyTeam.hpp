#pragma once

#include "define.hpp"
#include "player.hpp"

class FantasyTeam
{
private:
    string name;
    map<string, vector<shared_ptr<Player>>> players;

public:
    double get_score(int week_num);
    bool can_add_player(string post);
    bool have_this_player(string name);
    void add_player(shared_ptr<Player> target_player); /* in here we can use string of name instead of a Player*/
    void remove_player(string name);
    void show_fantasy_team();
};
