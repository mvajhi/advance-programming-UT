#include "player.hpp"

Player::Player(string name_, string role_)
{
    name = name_;
    role = role_;
}

int Player::get_score(int week)
{
    return 0;
}

bool Player::can_play(int week)
{
    return false;
}

string Player::get_role()
{
    return string();
}

string Player::get_name()
{
    return name;
}