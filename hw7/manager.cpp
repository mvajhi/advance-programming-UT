#include "manager.hpp"

Manager::Manager()
{
    transfer_window_status = false;
}

bool Manager::can_signup(User_login_info input)
{
    // check no one login
    if (is_user_logged() || admin.is_logged())
        return false;

    // check name
    if (users.count(input.username) != 0)
        return false;

    return true;
}

shared_ptr<User> Manager::add_new_user(User_login_info input)
{
    auto new_user = make_shared<User>(input.username, input.password);

    users.insert(make_pair(input.username, new_user));

    return new_user;
}

void Manager::check_can_login(User_login_info input)
{
    // check no one login
    if (is_user_logged() || admin.is_logged())
        throw BAD_REQUEST_MASSAGE;

    // check name
    if (users.count(input.username) == 0)
        throw NOT_FOUND_MASSAGE;

    // check password
    if (!users[input.username]->is_password_valid(input.password))
        throw PERMISSION_DENIED_MASSAGE;
}

void Manager::check_admin_can_login(User_login_info input)
{
    // check no one login
    if (is_user_logged() || admin.is_logged())
        throw BAD_REQUEST_MASSAGE;

    // check username
    if (!admin.is_valid_username(input.username))
        throw BAD_REQUEST_MASSAGE;

    // check password
    if (!admin.is_valid_password(input.password))
        throw PERMISSION_DENIED_MASSAGE;
}

void Manager::check_can_logout()
{
    // no user logged
    if (!(is_user_logged() || admin.is_logged()))
        throw PERMISSION_DENIED_MASSAGE;
}

void Manager::check_can_buy_player(string name)
{
    // check login
    if (!is_user_logged())
        throw PERMISSION_DENIED_MASSAGE;
    // check have this player
    if (!real_game_manager.does_player_exist(name))
        throw NOT_FOUND_MASSAGE;
    // check transfer open
    if (!Time::is_transfer_open())
        throw PERMISSION_DENIED_MASSAGE;
    // check player can play
    if (real_game_manager.get_player_by_name(name)
            ->can_play(Time::get_next_week()))
        throw PLAYER_CANT_PLAY_MASSAGE;
}

void Manager::check_can_sell_player(string name)
{
    // check login
    if (!is_user_logged())
        throw PERMISSION_DENIED_MASSAGE;
    // check have this player
    if (!real_game_manager.does_player_exist(name))
        throw NOT_FOUND_MASSAGE;
    // check transfer open
    if (!Time::is_transfer_open())
        throw PERMISSION_DENIED_MASSAGE;
}

void Manager::check_team_players(Team_players_input input)
{
    // have this post
    if (input.just_special_post &&
        find(POSTS.begin(), POSTS.end(), input.post) == POSTS.end())
        throw BAD_REQUEST_MASSAGE;
    // have this team
    if (!real_game_manager.does_team_exist(input.name))
        throw NOT_FOUND_MASSAGE;
}

bool Manager::is_user_logged()
{
    // !change == to !=
    return user_logged != nullptr;
}

void Manager::update_user_new_week()
{
    for (auto user : users)
        user.second->ready_for_new_week();
}

shared_ptr<Reporter> Manager::get_week_matches_report(int week)
{
    if (!Time::is_valid_week(week))
        return make_shared<Massage_reporter>(BAD_REQUEST_MASSAGE + "\n");

    auto report = real_game_manager.get_matches_report(week);
    // TODO check for not found
    return report;
}

shared_ptr<Reporter> Manager::signup(User_login_info input)
{
    if (!can_signup(input))
        return make_shared<Massage_reporter>(BAD_REQUEST_MASSAGE + "\n");

    auto new_user = add_new_user(input);

    user_logged = new_user;

    return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
}

shared_ptr<Reporter> Manager::login(User_login_info input)
{
    try
    {
        check_can_login(input);

        user_logged = users[input.username];

        return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
    }
    catch (const string &error)
    {
        return make_shared<Massage_reporter>(error + "\n");
    }
}

shared_ptr<Reporter> Manager::logout()
{
    try
    {
        check_can_logout();

        user_logged = nullptr;
        admin.logout();

        return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
    }
    catch (const string &error)
    {
        return make_shared<Massage_reporter>(error + "\n");
    }
}

shared_ptr<Reporter> Manager::register_admin(User_login_info input)
{
    try
    {
        check_admin_can_login(input);

        admin.logging();

        return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
    }
    catch (const string &error)
    {
        return make_shared<Massage_reporter>(error + "\n");
    }
}

shared_ptr<Reporter> Manager::get_best_team(int week)
{
    map<string, vector<shared_ptr<Player>>> best_team;

    best_team.insert(make_pair(GK,
                               real_game_manager
                                   .get_best_players_in_post(week, GK, 1)));
    best_team.insert(make_pair(DF,
                               real_game_manager
                                   .get_best_players_in_post(week, DF, 2)));
    best_team.insert(make_pair(MF,
                               real_game_manager
                                   .get_best_players_in_post(week, MF, 1)));
    best_team.insert(make_pair(FW,
                               real_game_manager
                                   .get_best_players_in_post(week, FW, 1)));

    return make_shared<Best_team_reporter>(best_team, week);
}

shared_ptr<Reporter> Manager::get_team_players(Team_players_input input)
{
    try
    {
        check_team_players(input);

        return real_game_manager.get_team_player_report(input);
    }
    catch (const string &error)
    {
        return make_shared<Massage_reporter>(error + "\n");
    }
}

shared_ptr<Reporter> Manager::get_team_list(int week)
{
    return real_game_manager.get_team_list_report(week);
}

void Manager::import_real_teams(League_data input)
{
    real_game_manager.import_teams(input);
}

void Manager::import_real_weeks(map<int, std::vector<Game_input>> input)
{
    real_game_manager.add_league_weeks(input);
}

shared_ptr<Reporter> Manager::buy_player(string name)
{
    try
    {
        check_can_buy_player(name);

        user_logged->buy_player(real_game_manager.get_player_by_name(name));

        return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
    }
    catch (const string &error)
    {
        return make_shared<Massage_reporter>(error + "\n");
    }
}

shared_ptr<Reporter> Manager::sell_player(string name)
{
    try
    {
        check_can_sell_player(name);

        user_logged->sell_player(name);

        return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
    }
    catch (const string &error)
    {
        return make_shared<Massage_reporter>(error + "\n");
    }
}

bool compare_users(User_ranking_data a, User_ranking_data b)
{
    if ((a.point < b.point) ||
        ((a.point == b.point) &&
         (a.name[0] < b.name[0])))
        return 1;
    else
        return 0;
}

shared_ptr<Reporter> Manager::get_users_ranking()
{
    User_ranking_data user_date;
    vector<User_ranking_data> collection;

    for (auto user : users)
    {
        user_date.name = user.first;
        user_date.point = user.second->get_total_score(Time::get_week());
        collection.push_back(user_date);
    }

    sort(collection.begin(), collection.end(), compare_users);

    return make_shared<User_ranks_report>(collection);
}

shared_ptr<Reporter> Manager::pass_week()
{
    if (!admin.is_logged())
        return make_shared<Massage_reporter>(PERMISSION_DENIED_MASSAGE + "\n");

    admin.pass_week();
    update_user_new_week();

    return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
}

shared_ptr<Reporter> Manager::open_transfer_window()
{
    if (!admin.is_logged())
        return make_shared<Massage_reporter>(PERMISSION_DENIED_MASSAGE + "\n");

    admin.open_transfer_window();

    return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
}

shared_ptr<Reporter> Manager::close_transfer_window()
{
    if (!admin.is_logged())
        return make_shared<Massage_reporter>(PERMISSION_DENIED_MASSAGE + "\n");

    admin.open_transfer_window();

    return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
}
