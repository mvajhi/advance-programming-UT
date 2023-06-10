#include "player.hpp"

bool Player::have_red_card(Player_status status)
{
    return status.red_card;
}

bool Player::is_injured(Player_status status)
{
    return status.injured;
}

bool Player::check_pre_weeks_status(
    int week, size_t pre_weeks_check, bool (*have_this_state)(Player_status))
{
    for (size_t i = 0; i < pre_weeks_check; i++)
        if (weeks_games.count(week - i - 1) == 0)
            continue;
        else if ((*have_this_state)(weeks_games[week - i - 1]))
            return true;

    return false;
}

bool Player::is_played(int week)
{
    return weeks_games.count(week) != 0 && weeks_games[week].is_played;
}

void Player::update_card_status(Player_status &status)
{

    sum_yellow_card += status.yellow_card;

    if (status.red_card == true)
        sum_yellow_card = 0;

    if (sum_yellow_card == MAX_YELLOW_CARD)
    {
        sum_yellow_card = 0;
        status.red_card = true;
    }
}

Player::Player(Player_info info)
{
    name = info.name;
    role = info.post;
    price = info.price;
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
    return !(check_pre_weeks_status(
                 week, NUM_WEEK_DONT_PLAY_FOR_RED_CARD, have_red_card) ||
             check_pre_weeks_status(
                 week, NUM_WEEK_DONT_PLAY_FOR_INJURED, is_injured));
}

string Player::get_role()
{
    return role;
}

string Player::get_name()
{
    return name;
}

double Player::get_avg_score(int week)
{
    double sum = 0;
    double count = 0;

    for (int i = 1; i <= week; i++)
        if (is_played(i))
        {
            sum += get_score(i);
            count++;
        }

    if (count == 0)
        return 0.0;

    return sum / count;
}

void Player::add_new_match(Player_status status, int week)
{
    update_card_status(status);

    weeks_games.insert(make_pair(week, status));
}

int Player::get_price() {return price;}
