#include "FantasyTeam.hpp"

map<string, size_t> MAX_PLAYER_IN_ROLE =
    {
        {GK, 1},
        {DF, 2},
        {MF, 1},
        {FW, 1}};

bool FantasyTeam::have_this_player(string name)
{
    for (auto player : players)
        if (player.first == name)
            return true;

    return false;
}

bool FantasyTeam::is_team_full()
{
    int counter = 0;
    counter += players[GK].size();
    counter += players[DF].size();
    counter += players[MF].size();
    counter += players[FW].size();
    return counter == TEAM_SIZE;
}
int FantasyTeam::find_player_price(string name)
{
    for (auto &role : players)
        for (size_t player = 0; player < players[role.first].size(); player++)
            if (players[role.first][player]->get_name() == name)
            {
                return players[role.first][player]->get_price();
            }
    throw NOT_FOUND_MASSAGE;
}

void FantasyTeam::set_captain(string name)
{
    check_can_set_captain(name);

    have_captain = true;
    captain_name = name;
}

void FantasyTeam::sell_player(string name)
{
    if (name == captain_name)
        have_captain = false;

    for (auto &role : players)
        for (size_t player = 0; player < players[role.first].size(); player++)
            if (players[role.first][player]->get_name() == name)
            {
                players[role.first].erase(players[role.first].begin() + player);
                return;
            }

    throw NOT_FOUND_MASSAGE;
}

void FantasyTeam::buy_player(shared_ptr<Player> target_player)
{
    check_can_buy(target_player);

    players[target_player->get_role()].push_back(target_player);
}

void FantasyTeam::check_can_buy(shared_ptr<Player> player)
{
    // check post is not fill
    if (players[player->get_role()].size() >=
        MAX_PLAYER_IN_ROLE[player->get_role()])
        throw BAD_REQUEST_MASSAGE;
}

void FantasyTeam::check_can_set_captain(string name)
{
    // check have this player
    if (find_player(name) == nullptr)
        throw NOT_FOUND_MASSAGE;
}

shared_ptr<Player> FantasyTeam::find_player(string name)
{
    shared_ptr<Player> player;

    for (auto &role : players)
        for (size_t player = 0; player < players[role.first].size(); player++)
            if (players[role.first][player]->get_name() == name)
                return players[role.first][player];

    return nullptr;
}

double FantasyTeam::calculate_captain_score(int week)
{
    if (!find_player(captain_name)->is_played(week))
        return 0;

    double row_score = find_player(captain_name)->get_row_score(week);

    return A(row_score * CAPTAIN_COEFFICIENT);
}

FantasyTeam::FantasyTeam()
{
    have_captain = false;
}

double FantasyTeam::get_score(int week_num)
{
    double result = 0;

    if (!is_team_full())
        return 0;

    for (auto role : players)
        for (auto player : players[role.first])
            result += player->get_score(week_num);

    if (have_captain)
    {
        result -= find_player(captain_name)->get_score(week_num);
        result += calculate_captain_score(week_num);
    }

    return result;
}

map<string, vector<shared_ptr<Player>>> FantasyTeam::get_players()
{
    return players;
}

bool FantasyTeam::get_captain_status()
{
    return have_captain;
}

string FantasyTeam::get_captain_name()
{
    return captain_name;
}

int FantasyTeam::get_cost()
{
    int cost = 0;

    for (auto players_in_post : players)
        for (auto player : players_in_post.second)
            cost += player->get_price();

    return cost;
}

bool FantasyTeam::can_add_player(string post)
{
    if (post == GK)
    {
        if (players[GK].size() == GK_ALLOWED_SIZE)
            return false;
        return true;
    }
    else if (post == DF)
    {
        if (players[DF].size() == DF_ALLOWED_SIZE)
            return false;
        return true;
    }
    else if (post == MF)
    {
        if (players[MF].size() == MF_ALLOWED_SIZE)
            return false;
        return true;
    }
    else if (post == FW)
    {
        if (players[FW].size() == FW_ALLOWED_SIZE)
            return false;
        return true;
    }

    return true;
}

int FantasyTeam::get_player_price(shared_ptr<Player> target_player)
{
    return target_player->get_price();
}