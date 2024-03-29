#include "real_game_manager.hpp"

void Real_game_manager::add_new_player(Player_info info)
{
    players.insert(make_pair(
        info.name, make_shared<Player>(info)));
}

void Real_game_manager::add_new_players(map<string, Player_info> name_with_role)
{
    for (auto i : name_with_role)
        add_new_player(i.second);
}

pair<string, Player_info> Real_game_manager::convert_player_info_pair(
    Player_info info, string post)
{
    info.post = post;
    return make_pair(info.name, info);
}

map<string, Player_info> Real_game_manager::convert_team_players_to_map(
    shared_ptr<Team_data> data)
{
    map<string, Player_info> output;

    for (auto i : data->gk)
        output.insert(convert_player_info_pair(i, GK));
    for (auto i : data->df)
        output.insert(convert_player_info_pair(i, DF));
    for (auto i : data->mf)
        output.insert(convert_player_info_pair(i, MF));
    for (auto i : data->fw)
        output.insert(convert_player_info_pair(i, FW));

    return output;
}

void Real_game_manager::add_new_team(shared_ptr<Team_data> team_data)
{
    map<string, vector<shared_ptr<Player>>> players =
        link_players_team(team_data);

    teams.insert(make_pair(team_data->team_name,
                           make_shared<Team>(team_data->team_name, players)));
}

vector<shared_ptr<Player>> Real_game_manager::get_link_players(
    vector<Player_info> players_info)
{
    vector<shared_ptr<Player>> output;
    for (auto i : players_info)
        output.push_back(players[i.name]);
    return output;
}

map<string, vector<shared_ptr<Player>>> Real_game_manager::link_players_team(
    shared_ptr<Team_data> team_data)
{
    map<string, vector<shared_ptr<Player>>> output;

    output.insert(make_pair(GK, get_link_players(team_data->gk)));
    output.insert(make_pair(DF, get_link_players(team_data->df)));
    output.insert(make_pair(FW, get_link_players(team_data->fw)));
    output.insert(make_pair(MF, get_link_players(team_data->mf)));

    return output;
}

shared_ptr<Match> Real_game_manager::add_new_match(Match_detail new_game,
                                                   int week)
{
    if (weeks_matches.count(week) == 0)
        weeks_matches.insert(make_pair(week, vector<shared_ptr<Match>>()));

    shared_ptr<Match> new_match = make_shared<Match>(new_game);

    weeks_matches[week].push_back(new_match);

    return new_match;
}

void Real_game_manager::update_teams(Match_detail new_game, int week)
{
    int team1_goal = new_game.teams_goal.first;
    int team2_goal = new_game.teams_goal.second;
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

    teams[new_game.teams_name.first]->add_new_match(
        week, score1, team2_goal, team1_goal);
    teams[new_game.teams_name.second]->add_new_match(
        week, score2, team1_goal, team2_goal);
}

void Real_game_manager::update_players(Match_detail new_game, int week)
{
    for (auto i : new_game.players_status)
        players[i.first]->add_new_match(i.second, week);
}

void Real_game_manager::update_match_detail(Match_detail &data,
                                            shared_ptr<Match> match)
{
    data.players_status = match->get_players_status();
}

vector<shared_ptr<Player>> Real_game_manager::get_all_players_in_post(
    string post)
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

void Real_game_manager::add_new_game(Match_detail new_game, int week)
{
    auto new_match = add_new_match(new_game, week);
    update_match_detail(new_game, new_match);
    update_players(new_game, week);
    update_teams(new_game, week);
}

void Real_game_manager::add_week(vector<Match_detail> games, int week)
{
    for (auto i : games)
        add_new_game(i, week);
}

void Real_game_manager::import_league_weeks(
    map<int, vector<Match_detail>> league_week_data)
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

shared_ptr<Team_player_reporter> Real_game_manager::get_team_player_report(
    Team_players_input input)
{
    return make_shared<Team_player_reporter>(
        teams[input.name]->get_players(input.is_sort_with_rank,
                                       input.just_special_post,
                                       input.post, input.week),
        input.week);
}

shared_ptr<Team_list_reporter> Real_game_manager::get_team_list_report(int week)
{
    vector<shared_ptr<Team>> output;

    for (auto team : teams)
        output.push_back(team.second);

    sort(output.begin(), output.end(),
         [week](shared_ptr<Team> t1, shared_ptr<Team> t2)
         {
            if (t1->get_sum_score(week) != t2->get_sum_score(week))
                return t1->get_sum_score(week) > t2->get_sum_score(week);
            if (t1->get_diff_goal(week) != t2->get_diff_goal(week))
                return t1->get_diff_goal(week) > t2->get_diff_goal(week);
            if (t1->get_sum_gf(week) != t2->get_sum_gf(week))
                return t1->get_sum_gf(week) > t2->get_sum_gf(week);
            return t1->get_name().compare(t2->get_name()) < 0; });

    return make_shared<Team_list_reporter>(output, week);
}

vector<shared_ptr<Player>> Real_game_manager::get_best_players_in_post(
    int week, string post, int count)
{
    vector<shared_ptr<Player>> all_players = get_all_players_in_post(post);

    sort(all_players.begin(), all_players.end(),
         [week](shared_ptr<Player> p1, shared_ptr<Player> p2)
         {
             if (p1->get_score(week) == p2->get_score(week))
                 return p1->get_name().compare(p2->get_name()) < 0;
             else
                 return p1->get_score(week) > p2->get_score(week);
         });

    return vector<shared_ptr<Player>>(all_players.begin(),
                                      all_players.begin() + count);
}

shared_ptr<Player> Real_game_manager::get_player_by_name(string name)
{
    return players[name];
}

bool Real_game_manager::does_player_exist(string name)
{
    return players.count(name) != 0;
}

bool Real_game_manager::does_team_exist(string name)
{
    return teams.count(name) != 0;
}
