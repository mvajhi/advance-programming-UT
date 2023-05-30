#include "player.hpp"

bool Player::have_red_card(int week)
{
    for (size_t i = 0; i < NUM_WEEK_DONT_PLAY_FOR_RED_CARD; i++)
    {
        if (weeks_games.count(week - i - 1) == 0)
            continue;
        if(weeks_games[week - i - 1].red_card == true)
            return true;
    }

    return false;
}

bool Player::is_injured(int week)
{
    for (size_t i = 0; i < NUM_WEEK_DONT_PLAY_FOR_INJURED; i++)
    {
        if (weeks_games.count(week - i - 1) == 0)
            continue;
        if(weeks_games[week - i - 1].injured == true)
            return true;
    }
    return false;
}

Player::Player(string name_, string role_)
{
    name = name_;
    role = role_;
    sum_yellow_card = 0;
}

double Player::get_score(int week)
{
    if (weeks_games.count(week) != 0)
        return weeks_games[week].score;
    return 0;
}

bool Player::can_play(int week)
{
    return !(have_red_card(week) ||
             is_injured(week));
}

string Player::get_role()
{
    return role;
}

string Player::get_name()
{
    return name;
}

void Player::add_new_match(Player_status status, int week)
{
    sum_yellow_card += status.yellow_card;

    if (status.red_card == true)
        sum_yellow_card = 0;

    if (sum_yellow_card == MAX_YELLOW_CARD)
    {
        sum_yellow_card = 0;
        status.red_card = true;
    }

    weeks_games.insert(make_pair(week, status));
}
