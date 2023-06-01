#include "FantasyTeam.hpp"

bool FantasyTeam::have_this_player(string name)
{
    for (auto player : players)
        if (player.first == name)
            return true;

    return false;
}

void FantasyTeam::remove_player(string name)
{
    for (auto &role : players)
        for (size_t player = 0; player < players[role.first].size(); player++)
            if (players[role.first][player]->get_name() == name)
            {
                players[role.first].erase(players[role.first].begin() + player);
                return;
            }
}

void FantasyTeam::add_player(shared_ptr<Player> target_player)
{
    players[target_player->get_role()].push_back(target_player);
    return;
}

double FantasyTeam::get_score(int week_num)
{
    double result = 0;
    for (auto role : players)
        for (auto player : players[role.first])
            result += player->get_score(week_num);
    return result;
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
