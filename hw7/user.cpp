#include "user.hpp"

void User::create_weekly_teams()
{
    Weekly_team tmp_week;
    tmp_week.buy_count = 0;
    tmp_week.sell_count = 0;

    for (size_t i = 0; i <= FINAL_WEEK; i++)
        user_teams.insert(make_pair(i, tmp_week));
}

void User::check_can_buy()
{
    // check can trade and count not full
    if (Time::get_next_week() != week_joined &&
        user_teams[Time::get_next_week()].buy_count >= MAX_BUY_COUNT)
        throw PERMISSION_DENIED_MASSAGE;
}

User::User(string user_name, string user_pass)
{
    name = user_name;
    password = user_pass;
    week_joined = Time::get_next_week();

    create_weekly_teams();
}

bool User::is_password_valid(string pass)
{
    return pass == password;
}

string User::get_name()
{
    return name;
}

FantasyTeam User::get_team(int week)
{
    return user_teams[week].team;
}

void User::buy_player(shared_ptr<Player> player)
{
    check_can_buy();

    user_teams[Time::get_next_week()].team.buy_player(player);
    
    user_teams[Time::get_next_week()].buy_count++;
}

void User::sell_player(string name)
{
}

double User::get_total_score(int week_num)
{
    double result = 0;
    for (int week = FIRST_WEEK; week <= week_num; week++)
        result += user_teams[week].team.get_score(week);
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
