#include "user.hpp"

void User::create_weekly_teams()
{
    Weekly_team tmp_week;
    tmp_week.buy_count = 0;
    tmp_week.sell_count = 0;

    for (size_t i = 0; i <= FINAL_WEEK; i++)
        user_teams.insert(make_pair(i, tmp_week));
}

void User::check_can_buy(shared_ptr<Player> target_player)
{
    // check can trade and count not full
    if (Time::get_next_week() > week_team_is_full)
        if (user_teams[Time::get_next_week()].buy_count >= MAX_BUY_COUNT)
            throw PERMISSION_DENIED_MASSAGE;
    // check have money
    if (transfer_budget < target_player->get_price())
        throw BAD_REQUEST_MASSAGE;
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
    if (week_team_is_full == NOT_FULL)
        if (user_teams[Time::get_next_week()].team.is_team_full())
            week_team_is_full = Time::get_next_week();

    if (week_team_is_full == Time::get_next_week())
        if (!user_teams[Time::get_next_week()].team.is_team_full())
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
    return week >= week_joined && week >= week_team_is_full;
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
    check_can_buy(player);

    user_teams[Time::get_next_week()].team.buy_player(player);
    decrease_budget(player->get_price());

    update_after_buy();
}

void User::sell_player(string name)
{
    check_can_sell();

    int player_price = user_teams[Time::get_next_week()]
                           .team.find_player_price(name);
    increase_budget(player_price);

    user_teams[Time::get_next_week()].team.sell_player(name);

    update_after_sell();
}

void User::ready_for_new_week()
{
    user_teams[Time::get_next_week()].team =
        user_teams[Time::get_week()].team;
}

void User::set_captain(string name)
{
    user_teams[Time::get_next_week()].team.set_captain(name);
}

double User::get_total_score(int week_num)
{
    double result = 0;
    for (int week = week_team_is_full; week <= week_num; week++)
        result += user_teams[week].team.get_score(week);
    return result;
}

void User::decrease_budget(int player_price)
{
    transfer_budget -= player_price;
}

void User::increase_budget(int player_price)
{
    transfer_budget += player_price;
}

Fantasy_team_data User::show_fantasy_team(int week_num)
{
    Fantasy_team_data target;
    target.team_name = get_name();
    target.total_score = get_total_score(week_num);
    target.is_full = user_teams[week_num].team.is_team_full();
    if (target.is_full == false)
        return target;

    map<string, vector<shared_ptr<Player>>> teams_players =
        get_team(week_num).get_players();
    target.gk = teams_players[GK][0]->get_name();
    target.df1 = teams_players[DF][0]->get_name();
    target.df2 = teams_players[DF][1]->get_name();
    target.mf = teams_players[MF][0]->get_name();
    target.fw = teams_players[FW][0]->get_name();

    target.have_captain = get_team(week_num).get_captain_status();
    if (target.have_captain)
        target.captain_name = get_team(week_num).get_captain_name();

    target.total_cost = get_team(week_num).get_cost();

    return target;
}

int User::get_budget()
{
    return transfer_budget;
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
