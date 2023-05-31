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

    static bool have_red_card(Player_status status);
    static bool is_injured(Player_status status);
    bool check_pre_weeks_status(int week, size_t pre_weeks_check, bool (*have_this_state)(Player_status));
    void update_card_status(Player_status &status);

public:
    Player(string name_, string role_);
    double get_score(int week);
    bool can_play(int week);
    string get_role();
    string get_name();
    void add_new_match(Player_status status, int week);
};