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
    int price;

    // check
    bool is_played(int week);
    static bool is_injured(Player_status status);
    static bool have_red_card(Player_status status);
    bool check_pre_weeks_status(
        int week, size_t pre_weeks_check,
        bool (*have_this_state)(Player_status));
    double count_in_weeks_status(
        int week,
        function<double(Player_status)> things_should_count);

    // other
    void update_card_status(Player_status &status);

public:
    Player(Player_info info);

    // check
    bool can_play(int week);

    // output
    int get_price();
    string get_role();
    string get_name();
    double get_score(int week);
    int get_clean_sheet(int week);
    int get_goal(int week);
    int get_assist(int week);
    double get_avg_score(int week);

    // other
    void add_new_match(Player_status status, int week);
};