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
    if (Time::get_next_week() > week_team_is_full)
        if (user_teams[Time::get_next_week()].buy_count >= MAX_BUY_COUNT)
            throw PERMISSION_DENIED_MASSAGE;
}

void User::update_after_buy()
{
    user_teams[Time::get_next_week()].buy_count++;
    update_team_state();
}

void User::check_can_sell()
{
    // check can trade and count not full
    if (Time::get_next_week() > week_team_is_full)
        if (user_teams[Time::get_next_week()].sell_count >= MAX_SELL_COUNT)
            throw PERMISSION_DENIED_MASSAGE;
}

void User::update_after_sell()
{
    user_teams[Time::get_next_week()].sell_count++;
    update_team_state();
}

void User::update_team_state()
{
    if (user_teams[Time::get_next_week()].buy_count -
                user_teams[Time::get_next_week()].sell_count ==
            TEAM_SIZE &&
        week_team_is_full != Time::get_next_week())
        week_team_is_full = Time::get_next_week();

    else if (week_team_is_full == Time::get_next_week())
        week_team_is_full = NOT_FULL;
}

User::User(string user_name, string user_pass)
{
    name = user_name;
    password = user_pass;
    week_team_is_full = NOT_FULL;
    week_joined = Time::get_next_week();
    transfer_budget = DEFAULT_BUDGET;
    create_weekly_teams();
}

bool User::is_password_valid(string pass)
{
    return pass == password;
}

bool User::is_joined(int week)
{
    return week >= week_joined;
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

    update_after_buy();
}

void User::sell_player(string name)
{
    check_can_sell();

    user_teams[Time::get_next_week()].team.sell_player(name);

    update_after_sell();
}

void User::ready_for_new_week()
{
    user_teams[Time::get_next_week()].team =
        user_teams[Time::get_week()].team;
}

double User::get_total_score(int week_num)
{
    double result = 0;
    for (int week = FIRST_WEEK; week <= week_num; week++)
        result += user_teams[week].team.get_score(week);
    return result;
}

void User::decrease_budget(int player_price)
{
    transfer_budget -= player_price;
}
Fantasy_team_data User::show_fantasy_team(int week_num)
{
    Fantasy_team_data target;
    target.team_name = get_name();
    target.total_score = get_total_score(week_num);
    target.is_full = user_teams[week_num].team.is_team_full();
    if (target.is_full == false)
        return target;

    map<string, vector<shared_ptr<Player>>> teams_players = get_team(week_num).get_players();
    target.gk = teams_players[GK][0]->get_name();
    target.df1 = teams_players[DF][0]->get_name();
    target.df2 = teams_players[DF][1]->get_name();
    target.mf = teams_players[MF][0]->get_name();
    target.fw = teams_players[FW][0]->get_name();
    return target;
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
}

void Admin::open_transfer_window()
{
    Time::open_transfer();
}

void Admin::close_transfer_window()
{
    Time::close_transfer();
}

