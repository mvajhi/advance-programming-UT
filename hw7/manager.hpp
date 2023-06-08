#pragma once

#include "define.hpp"
#include "reporter.hpp"
#include "user.hpp"
#include "real_game_manager.hpp"
#include <algorithm>

class Manager
{
private:
    Admin admin;
    bool transfer_window_status;
    shared_ptr<User> user_logged;
    Real_game_manager real_game_manager;
    map<string, shared_ptr<User>> users;

    // check
    bool is_user_logged();
    void check_can_logout();
    void check_can_buy_player(string name);
    bool can_signup(User_login_info input);
    void check_can_sell_player(string name);
    void check_can_login(User_login_info input);
    void check_team_players(Team_players_input input);
    void check_admin_can_login(User_login_info input);
    void check_can_show_fantasy_team(Fantasy_input input);

    // other
    shared_ptr<User> add_new_user(User_login_info input);
    void update_user_new_week();
    shared_ptr<Reporter> set_transfer(bool mod);

public:
    Manager();

    // SSO
    shared_ptr<Reporter> signup(User_login_info input);
    shared_ptr<Reporter> login(User_login_info input);
    shared_ptr<Reporter> logout();
    shared_ptr<Reporter> register_admin(User_login_info input);

    // output
    shared_ptr<Reporter> get_users_ranking();
    shared_ptr<Reporter> get_team_list(int week);
    shared_ptr<Reporter> get_best_team(int week);
    shared_ptr<Reporter> get_week_matches_report(int week);
    shared_ptr<Reporter> get_team_players(Team_players_input input);
    shared_ptr<Reporter> get_fantasy_team(Fantasy_input target_team);

    // time control
    shared_ptr<Reporter> pass_week();
    shared_ptr<Reporter> open_transfer_window();
    shared_ptr<Reporter> close_transfer_window();

    // import
    void import_real_teams(League_data input);
    void import_real_weeks(map<int, vector<Game_input>> input);

    // transfer
    shared_ptr<Reporter> buy_player(string name);
    shared_ptr<Reporter> sell_player(string name);
};
