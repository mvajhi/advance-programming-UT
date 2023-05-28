#pragma once

#include "define.hpp"

class Team;

class Player
{
private:
    string name;
    string role;
    shared_ptr<Team> team;
    map<int, Player_status> weeks_games;
    int sum_yellow_card;

    bool have_red_card(int week);
    bool is_injured(int week);

public:
    Player(string name_, string role_);
    int get_score(int week);
    bool can_play(int week);
    string get_role();
    string get_name();
    void add_new_match(Player_status status, int week);
};