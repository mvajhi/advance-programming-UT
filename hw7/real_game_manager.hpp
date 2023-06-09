#pragma once

#include "define.hpp"
#include "player.hpp"
#include "team.hpp"
#include "match.hpp"

class Real_game_manager
{
private:
    map<string, shared_ptr<Player>> players;
    map<string, shared_ptr<Team>> teams;
    map<int, vector<shared_ptr<Match>>> weeks_matches;

    // add
    void add_new_player(string name, string role);
    void add_new_game(Match_detail new_game, int week);
    void add_week(vector<Match_detail> games, int week);
    void add_new_match(Match_detail new_game, int week);
    void add_new_team(shared_ptr<Team_data> team_data);
    void add_new_players(map<string, string> name_with_role);

    // get
    vector<shared_ptr<Player>> get_all_players_in_post(string post);
    vector<shared_ptr<Player>> get_link_players(vector<string> players_name);

    // update
    void update_teams(Match_detail new_game, int week);
    void update_players(Match_detail new_game, int week);

    // other
    map<string, string> convert_team_players_to_map(
        shared_ptr<Team_data> data);
    map<string, vector<shared_ptr<Player>>> link_players_team(
        shared_ptr<Team_data> team_data);

public:
    Real_game_manager();

    // import
    void import_teams(League_data input);
    void import_league_weeks(map<int, vector<Match_detail>> league_week_data);

    // output
    shared_ptr<Player> get_player_by_name(string name);
    shared_ptr<Match_reporter> get_matches_report(int week);
    shared_ptr<Team_list_reporter> get_team_list_report(int week);
    vector<shared_ptr<Player>> get_best_players_in_post(
        int week, string post, int count);
    shared_ptr<Team_player_reporter> get_team_player_report(
        Team_players_input input);

    // check
    bool does_team_exist(string name);
    bool does_player_exist(string name);
};
