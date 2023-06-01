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

    double get_sum_weeks(int week, function<double(Team_status)> thing_collect);
    vector<shared_ptr<Player>> get_team_players(bool have_role, string role);
    vector<shared_ptr<Player>> sort_players(vector<shared_ptr<Player>> team_players, bool is_sort_by_score, int week = 0);
    void create_weeks();

public:
    Team(string name_, map<string, vector<shared_ptr<Player>>> players_);
    Team_status get_status(int week);
    vector<shared_ptr<Player>> get_players(bool is_sort, bool have_role, string role, int week_for_sort = 0);
    string get_name();
    void add_new_match(int week, int score, int ga, int gf);
    double get_sum_score(int week);
    int get_gf(int week);
    int get_ga(int week);
    int get_sum_gf(int week);
    int get_sum_ga(int week);
    int get_diff_goal(int week);
};
