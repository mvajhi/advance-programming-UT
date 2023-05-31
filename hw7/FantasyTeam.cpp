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
    for (auto role : players)
        for (shared_ptr<Player> player : players[role.first])
            if (player->get_name() == name)
            {
                //players[role.first].erase();
            }
}
