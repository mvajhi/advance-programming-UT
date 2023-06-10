#pragma once

#include "define.hpp"
#include "FantasyTeam.hpp"
#include "reporter.hpp"

struct Weekly_team
{
    FantasyTeam team;
    int sell_count;
    int buy_count;
};

class User
{
private:
    string name;
    string password;
    int week_team_is_full;
    int week_joined;
    int transfer_budget;
    map<int, Weekly_team> user_teams;

    // check
    void check_can_buy(shared_ptr<Player> target_player);
    void check_can_sell();

    // update
    void update_after_buy();
    void update_after_sell();
    void update_team_state();

    // transform
    void decrease_budget(int player_price);
    void increase_budget(int player_price);

    // other
    void create_weekly_teams();

public:
    User(string user_name, string user_pass);

    // output
    string get_name();
    FantasyTeam get_team(int week);
    double get_total_score(int week_num);
    Fantasy_team_data show_fantasy_team(int week_num);

    // check
    bool is_joined(int week);
    bool is_password_valid(string pass);

    // transform
    void sell_player(string name);
    void buy_player(shared_ptr<Player> player);

    // other
    void ready_for_new_week();
    void set_captain(string name);
};

class Admin
{
private:
    bool logged;

public:
    Admin();

    // check
    bool is_logged();
    bool is_valid_username(string input);
    bool is_valid_password(string input);

    // SSO
    void logout();
    void logging();

    // time control
    void pass_week();
    void open_transfer_window();
    void close_transfer_window();
};