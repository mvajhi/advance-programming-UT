#include "user.hpp"

User::User(string user_name, string user_pass)
{
    name = user_name;
    password = user_pass;
}

bool User::is_password_valid(string pass)
{
    return pass == password;
}

string User::get_name()
{
    return name;
}

shared_ptr<FantasyTeam> User::get_team(int week)
{
    return user_teams[week];
}

void User::buy_player(shared_ptr<Player> player)
{
    
}

void User::sell_player(string name)
{
}

double User::get_total_score(int week_num)
{
    double result = 0;
    for (int week = FIRST_WEEK; week <= week_num; week++)
        result += user_teams[week]->get_score(week);
    return result;
}

Admin::Admin()
{
    logged = false;
}

bool Admin::is_logged()
{
    return logged;
}

bool Admin::is_valid_username(string input)
{
    return input == ADMIN_NAME;
}

bool Admin::is_valid_password(string input)
{
    return input == ADMIN_PASSWORD;
}

void Admin::logging()
{
    logged = true;
}

void Admin::logout()
{
    logged = false;
}

void Admin::pass_week()
{
    Time::go_next_week();
    // ! is ok?
    open_transfer_window();
}

void Admin::open_transfer_window()
{
    Time::open_transfer();
}

void Admin::close_transfer_window()
{
    Time::close_transfer();
}
