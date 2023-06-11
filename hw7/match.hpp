#pragma once

#include "define.hpp"
#include "team.hpp"
#include "reporter.hpp"

class Match
{
private:
    vector<Name> goals;
    vector<Name> own_goal;
    vector<Name> goals_assist;
    pair<int, int> teams_goal;
    pair<Name, Name> teams_name;
    map<Name, Player_status> players_status;
    pair<map<Name, Role>, map<Name, Role>> players_teams;

    map<Role, function<int(Name)>> score_algorithm;

    // map creator
    void create_function_map();
    void create_gk_function();
    void create_df_function();
    void create_mf_function();
    void create_fw_function();

    // geterr
    int get_ga(Name player);
    int get_own_goal(Name player);
    int get_player_goal(Name player);
    int get_player_assist(Name player);
    int get_team_result_score(Name player);
    map<Name, Role> get_opponent_team(Name player);
    int get_goal_in_posts(vector<Role> roles, map<Name, Role> players);

    // proccess score
    int calculate_score_row(pair<Name, Role> player);
    int calculate_common_score(Name player);

    // update status
    void update_players_status();
    void update_player_status(pair<Name, Role> player);
    void set_score(pair<Name, Role> player);
    void set_goal(Name player);
    void set_assist(Name player);
    void set_clean_sheet(Name player);

    // other
    void initialize_data(Match_detail input);

public:
    Match(Match_detail input);

    // output
    Match_report_data get_match_data();
    map<Name, Player_status> get_players_status();
};