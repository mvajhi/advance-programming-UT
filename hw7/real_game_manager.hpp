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

    void add_new_player(string name, string role);
    void add_new_players(map<string, string> name_with_role);
    map<string, string> convert_team_players_to_map(shared_ptr<Team_data> data);
    void add_new_team(shared_ptr<Team_data> team_data);
    vector<shared_ptr<Player>> get_link_players(vector<string> players_name);
    map<string, vector<shared_ptr<Player>>> link_players_team(shared_ptr<Team_data> team_data);

public:
    Real_game_manager();
    void add_new_game(Game_input new_game);
    void add_week(vector<Game_input> games);
    void add_league_weeks(map<int, vector<Game_input>> league_week_data);
    void import_teams(League_data input);
    shared_ptr<Match_reporter> get_matches_report(int week);
};