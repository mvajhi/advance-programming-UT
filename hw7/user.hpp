#pragma once

#include "define.hpp"
#include "FantasyTeam.hpp"
#include "reporter.hpp"

class User
{
private:
    string name;
    string password;
    map<int, shared_ptr<FantasyTeam>> user_teams;

public:
    User(string user_name, string user_pass);
    bool is_password_valid(string pass);
    string get_name();
    double get_total_score(int week_num);
    shared_ptr<FantasyTeam> get_team(int week);
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