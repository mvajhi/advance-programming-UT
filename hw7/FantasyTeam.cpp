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

void FantasyTeam::sell_player(string name)
{
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

double FantasyTeam::get_score(int week_num)
{
    double result = 0;
    for (auto role : players)
        for (auto player : players[role.first])
            result += player->get_score(week_num);
    return result;
}

map<string, vector<shared_ptr<Player>>> FantasyTeam::get_players()
{
    return players;
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
