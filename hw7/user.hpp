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
    int week_joined;
    map<int, Weekly_team> user_teams;
    
    void create_weekly_teams();
    void check_can_buy();

public:
    User(string user_name, string user_pass);
    bool is_password_valid(string pass);
    string get_name();
    double get_total_score(int week_num);
    FantasyTeam get_team(int week);
    void buy_player(shared_ptr<Player> player);
    void sell_player(string name);
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