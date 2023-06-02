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
    map<int, Weekly_team> user_teams;
    
    void create_weekly_teams();
    void check_can_buy();
    void update_after_buy();
    void check_can_sell();
    void update_after_sell();
    void update_team_state();

public:
    User(string user_name, string user_pass);
    bool is_password_valid(string pass);
    string get_name();
    double get_total_score(int week_num);
    FantasyTeam get_team(int week);
    void buy_player(shared_ptr<Player> player);
    void sell_player(string name);
    void ready_for_new_week();
};

class Admin
{
private:
    bool logged;
public:
    Admin();
    bool is_logged();
    bool is_valid_username(string input);
    bool is_valid_password(string input);
    void logging();
    void logout();
    void pass_week();
    void open_transfer_window();
    void close_transfer_window();
};