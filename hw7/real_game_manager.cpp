#include "real_game_manager.hpp"

void Real_game_manager::add_new_player(string name, string role)
{
    players.insert(make_pair(name, make_shared<Player>(name, role)));
}

void Real_game_manager::add_new_players(map<string, string> name_with_role)
{
    for (auto i : name_with_role)
        add_new_player(i.first, i.second);
}

map<string, string> Real_game_manager::convert_team_players_to_map(shared_ptr<Team_data> data)
{
    map<string, string> output;

    for (auto i : data->gk)
        output.insert(make_pair(i, GK));
    for (auto i : data->df)
        output.insert(make_pair(i, DF));
    for (auto i : data->mf)
        output.insert(make_pair(i, MF));
    for (auto i : data->fw)
        output.insert(make_pair(i, FW));

    return output;
}

void Real_game_manager::add_new_team(shared_ptr<Team_data> team_data)
{
    map<string, vector<shared_ptr<Player>>> players = link_players_team(team_data);

    teams.insert(make_pair(team_data->team_name, make_shared<Team>(team_data->team_name, players)));
}

vector<shared_ptr<Player>> Real_game_manager::get_link_players(vector<string> players_name)
{
    vector<shared_ptr<Player>> output;
    for (auto i : players_name)
        output.push_back(players[i]);
    return output;
}

map<string, vector<shared_ptr<Player>>> Real_game_manager::link_players_team(shared_ptr<Team_data> team_data)
{
    map<string, vector<shared_ptr<Player>>> output;

    output.insert(make_pair(GK, get_link_players(team_data->gk)));
    output.insert(make_pair(DF, get_link_players(team_data->df)));
    output.insert(make_pair(FW, get_link_players(team_data->fw)));
    output.insert(make_pair(MF, get_link_players(team_data->mf)));

    return output;
}

Real_game_manager::Real_game_manager()
{
}

void Real_game_manager::add_new_game(Game_input new_game)
{
}

void Real_game_manager::add_week(vector<Game_input> games)
{
}

void Real_game_manager::add_league_weeks(map<int, vector<Game_input>> league_week_data)
{
}

void Real_game_manager::import_teams(League_data input)
{
    for (auto team_data : input.teams)
    {
        add_new_players(convert_team_players_to_map(team_data.second));
        add_new_team(team_data.second);
    }
}

shared_ptr<Match_reporter> Real_game_manager::get_matches_report(int week)
{
    return make_shared<Match_reporter>(weeks_matches[week]);
}
