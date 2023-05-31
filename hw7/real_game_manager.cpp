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

void Real_game_manager::add_new_match(Game_input new_game, int week)
{
    if (weeks_matches.count(week) == 0)
        weeks_matches.insert(make_pair(week, vector<shared_ptr<Match>>()));

    weeks_matches[week].push_back(make_shared<Match>(teams[new_game.team1.first], new_game.team1.second, teams[new_game.team2.first], new_game.team2.second));
}

void Real_game_manager::update_teams(Game_input new_game, int week)
{
    int team1_goal = new_game.team1.second;
    int team2_goal = new_game.team2.second;
    int score1, score2;

    if (team1_goal > team2_goal)
    {
        score1 = WIN_SCORE;
        score2 = LOSE_SCORE;
    }
    else if (team1_goal < team2_goal)
    {
        score2 = WIN_SCORE;
        score1 = LOSE_SCORE;
    }
    else
    {
        score1 = DRAW_SCORE;
        score2 = DRAW_SCORE;
    }

    teams[new_game.team1.first]->add_new_match(week, score1, team2_goal, team1_goal);
    teams[new_game.team2.first]->add_new_match(week, score2, team1_goal, team2_goal);
}

void Real_game_manager::update_players(Game_input new_game, int week)
{
    for (auto i : new_game.players_status)
        players[i.first]->add_new_match(i.second, week);
}

vector<shared_ptr<Player>> Real_game_manager::get_all_players_in_post(string post)
{
    vector<shared_ptr<Player>> output;

    for (auto player : players)
        if (player.second->get_role() == post)
            output.push_back(player.second);

    return output;
}

Real_game_manager::Real_game_manager()
{
}

void Real_game_manager::add_new_game(Game_input new_game, int week)
{
    update_players(new_game, week);
    update_teams(new_game, week);
    add_new_match(new_game, week);
}

void Real_game_manager::add_week(vector<Game_input> games, int week)
{
    for (auto i : games)
        add_new_game(i, week);
}

void Real_game_manager::add_league_weeks(map<int, vector<Game_input>> league_week_data)
{
    for (auto i : league_week_data)
        add_week(i.second, i.first);
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

vector<shared_ptr<Player>> Real_game_manager::get_best_players_in_post(int week, string post, int count)
{
    vector<shared_ptr<Player>> all_players = get_all_players_in_post(post);

    sort(all_players.begin(), all_players.end(), [week](shared_ptr<Player> p1, shared_ptr<Player> p2) { //! possible bug in sort by name
        if (p1->get_score(week) == p2->get_score(week))
            return p1->get_name().compare(p2->get_name()) < 0;
        else
            return p1->get_score(week) > p2->get_score(week);
    });

    return vector<shared_ptr<Player>>(all_players.begin(), all_players.begin() + count);
}
