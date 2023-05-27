#pragma once

#include "define.hpp"
#include "player.hpp"
#include "team.hpp"
#include "match.hpp"

class Real_game_manager
{
private:
    vector<shared_ptr<Player>> players;
    vector<shared_ptr<Team>> teams;
    map<int, vector<shared_ptr<Match>>> weeks_games;

public:
    Real_game_manager();
    void add_new_game(Game_input new_game);
    void add_week(vector<Game_input> games);
    void add_league(map<int, vector<Game_input>> league_week_data);
};
