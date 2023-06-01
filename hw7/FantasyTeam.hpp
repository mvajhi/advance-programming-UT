#pragma once

#include "define.hpp"
#include "player.hpp"

class FantasyTeam
{
private:
    string name;
    map<string, vector<shared_ptr<Player>>> players;

    void check_can_buy(shared_ptr<Player> player);

public:
    double get_score(int week_num);
    bool can_add_player(string post);
    bool have_this_player(string name);
    void buy_player(shared_ptr<Player> target_player);
    void sell_player(string name);
    void show_fantasy_team();
};
