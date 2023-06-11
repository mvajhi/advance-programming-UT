#pragma once

#include "define.hpp"
#include "player.hpp"

class FantasyTeam
{
private:
    string name;
    map<string, vector<shared_ptr<Player>>> players;
    bool have_captain;
    string captain_name;

    // check
    void check_can_set_captain(string name);
    void check_can_buy(shared_ptr<Player> player);

    // other
    shared_ptr<Player> find_player(string name);
    double calculate_captain_score(int week);

public:
    FantasyTeam();

    // output
    int get_cost();
    bool get_captain_status();
    string get_captain_name();
    double get_score(int week_num);
    map<string, vector<shared_ptr<Player>>> get_players();

    // check
    bool is_team_full();
    bool can_add_player(string post);
    bool have_this_player(string name);

    // transfer
    void sell_player(string name);
    int find_player_price(string name);
    void buy_player(shared_ptr<Player> target_player);
    int get_player_price(shared_ptr<Player> target_player);

    // other
    void set_captain(string name);
};
