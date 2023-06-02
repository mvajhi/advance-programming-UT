#pragma once

#include "define.hpp"
#include "player.hpp"

class FantasyTeam
{
private:
    string name;
    map<string, vector<shared_ptr<Player>>> players;

    // check
    void check_can_buy(shared_ptr<Player> player);

public:
    // output
    double get_score(int week_num);

    // check
    bool can_add_player(string post);
    bool have_this_player(string name);

    // transfer
    void sell_player(string name);
    void buy_player(shared_ptr<Player> target_player);
};
