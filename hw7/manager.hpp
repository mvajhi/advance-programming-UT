#pragma once

#include "define.hpp"
#include "reporter.hpp"
#include "user.hpp"
#include "real_game_manager.hpp"

class Manager
{
private:
    Real_game_manager real_game_manager;
    map<string, shared_ptr<User>> users;
    shared_ptr<User> user_logged;

    bool can_signup(User_login_info input);
    shared_ptr<User> add_new_user(User_login_info input);
    void check_can_login(User_login_info input);

public:
    Manager();

    shared_ptr<Reporter> get_week_matches_report(int week);

    // SSO
    shared_ptr<Reporter> signup(User_login_info input);
    shared_ptr<Reporter> login(User_login_info input);
    shared_ptr<Reporter> logout();

    void import_real_teams(League_data input);
};