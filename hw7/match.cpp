#include "match.hpp"

// TODO move or change player func to match class

map<Role, vector<Role>> impressive_posts =
    {
        make_pair<Role, vector<Role>>(lb, {rw, rb}),
        make_pair<Role, vector<Role>>(cb, {cf, cb}),
        make_pair<Role, vector<Role>>(rb, {lw, lb})};

void Match::create_gk_function()
{
    score_algorithm.insert(make_pair(gk, [this](Name name)
                                     {
        int score = DEFAULT_GK_SCORE;

        score += calculate_common_score(name);

        int ga = get_ga(name);
        if (ga == 0)
            score += NO_GOAL_GK_SCORE;
        else
            score += GOAL_GK_SCORE * ga;
        
        return score; }));
}

void Match::create_df_function()
{
    for (Role role : {lb, cb, rb})
        score_algorithm.insert(make_pair(role, [this, role](Name name)
                                         {
            int score = DEFAULT_DF_SCORE;

            score += calculate_common_score(name);

            if (get_ga(name) == 0)
                score += NO_GOAL_DF_SCORE;
            
            score += get_player_goal(name) * DF_PLAYER_GOAL_SCORE;
        
            score += get_player_assist(name) * DF_PLAYER_ASSIST_SCORE;

            score += get_goal_in_posts(impressive_posts[role],
                                        get_opponent_team(name)) 
                        * DF_GA_IN_SIDE_SCORE;
        
            return score; }));
}

void Match::create_mf_function()
{

    score_algorithm.insert(make_pair(mf, [this](Name name)
                                     {
        int score = DEFAULT_MF_SCORE;

        score += calculate_common_score(name);

        int ga = get_ga(name);

        if (ga == 0)
            score += NO_GOAL_MF_SCORE;

        
        score += get_player_goal(name) * MF_PLAYER_GOAL_SCORE;

        score += get_player_assist(name) * MF_PLAYER_ASSIST_SCORE;

        score += get_goal_in_posts({mf}, get_opponent_team(name))
         * GA_MF_SCORE;

        return score; }));
}

void Match::create_fw_function()
{
    for (Role role : {lw, cf, rw})
        score_algorithm.insert(make_pair(role, [this](Name name) -> int
                                         {
        int score = DEFAULT_FW_SCORE;

        score += calculate_common_score(name);

        int goal = get_player_goal(name);

        if (goal == 0)
            score += NO_GOAL_FW_SCORE;
        else
            score += goal * FW_PLAYER_GOAL_SCORE;

        score += get_player_assist(name) * FW_PLAYER_ASSIST_SCORE;

        return score; }));
}

int Match::get_ga(Name player)
{
    return players_teams.first.count(player) == 0
               ? teams_goal.first
               : teams_goal.second;
}

int Match::get_own_goal(Name player)
{
    return count(own_goal.begin(), own_goal.end(), player);
}

int Match::get_player_goal(Name player)
{
    return count(goals.begin(), goals.end(), player);
}

int Match::get_player_assist(Name player)
{
    return count(goals_assist.begin(), goals_assist.end(), player);
}

int Match::get_team_result_score(Name player)
{
    if (teams_goal.first == teams_goal.second)
        return DRAW_PLAYER_SCORE;

    bool result;

    if (players_teams.first.count(player) != 0)
        result = teams_goal.first > teams_goal.second;
    else
        result = teams_goal.first < teams_goal.second;

    return result ? WIN_PLAYER_SCORE : LOSE_PLAYER_SCORE;
}

int Match::get_goal_in_posts(vector<Role> roles, map<Name, Role> players)
{
    return count_if(goals.begin(), goals.end(), [&](Name name)
                    { return find(roles.begin(),
                                  roles.end(),
                                  players[name]) !=
                             roles.end(); });
}

map<Name, Role> Match::get_opponent_team(Name player)
{
    return players_teams.first.count(player) == 0 ? players_teams.first
                                                  : players_teams.second;
}

int Match::calculate_score_row(pair<Name, Role> player)
{
    return score_algorithm[player.second](player.first);
}

double Match::calculate_Ax_score(int row_score)
{
    return 1.0 / (1.0 + exp(-(double)row_score / 6.0)) * 10;
}

int Match::calculate_common_score(Name player)
{
    int score = 0;

    score += get_own_goal(player) * OWN_GOAL_SCORE;
    score += get_team_result_score(player);

    return score;
}

void Match::update_players_status()
{
    for (auto player : players_teams.first)
        update_player_status(player);
    for (auto player : players_teams.second)
        update_player_status(player);
}

void Match::update_player_status(pair<Name, Role> player)
{
    set_score(player);
    set_goal(player.first);
    set_assist(player.first);
    set_clean_sheet(player.first);
}

void Match::set_score(pair<Name, Role> player)
{
    int row_score = calculate_score_row(player);
    players_status[player.first].row_score = row_score;
    players_status[player.first].score = calculate_Ax_score(row_score);

    // TODO rm
    // cout << "name: " << player.first << "\trow score: " << row_score
    //      << "\tscore: " << players_status[player.first].score << endl;
}

void Match::set_goal(Name player)
{
    players_status[player].goal = get_player_goal(player);
}

void Match::set_assist(Name player)
{
    players_status[player].assist = get_player_assist(player);
}

void Match::set_clean_sheet(Name player)
{
    players_status[player].clean_sheet = get_ga(player) == 0;
}

void Match::initialize_data(Match_detail input)
{
    goals = input.goals;
    goals_assist = input.goals_assist;
    own_goal = input.own_goal;
    players_status = input.players_status;
    players_teams = input.players_teams;
    teams_goal = input.teams_goal;
    teams_name = input.teams_name;
}

Match::Match(Match_detail input)
{
    initialize_data(input);
    create_function_map();
    update_players_status();
}

void Match::create_function_map()
{
    create_gk_function();
    create_df_function();
    create_mf_function();
    create_fw_function();
}

Match_report_data Match::get_match_data()
{
    Match_report_data output;

    output.team1 = make_pair(teams_name.first, teams_goal.first);
    output.team2 = make_pair(teams_name.second, teams_goal.second);

    return output;
}

map<Name, Player_status> Match::get_players_status()
{
    return players_status;
}
