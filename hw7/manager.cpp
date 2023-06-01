#include "manager.hpp"

Manager::Manager()
{
    auto new_admin = make_shared<Admin>();
    admins.insert(make_pair(new_admin->get_name(),new_admin));
    week_number = 1;
    transfer_window_status = false;
}

bool Manager::can_signup(User_login_info input)
{
    // check no one login
    if (!is_user_logged())
        return false;

    // check name
    if (users.count(input.username) != 0)
        return false;

    return true;
}

shared_ptr<NormalUser> Manager::add_new_user(User_login_info input)
{
    auto new_user = make_shared<NormalUser>(input.username, input.password);

    users.insert(make_pair(input.username, new_user));

    return new_user;
}

void Manager::check_can_login(User_login_info input)
{
    // check no one login
    if (!is_user_logged())
        throw BAD_REQUEST_MASSAGE;

    // check name
    if (users.count(input.username) == 0)
        throw NOT_FOUND_MASSAGE;

    // check password
    if (!users[input.username]->is_password_valid(input.password))
        throw PERMISSION_DENIED_MASSAGE;
}

void Manager::check_can_logout()
{
    // no user logged
    if (is_user_logged())
        throw PERMISSION_DENIED_MASSAGE;
}

bool Manager::is_user_logged()
{
    return user_logged == nullptr && admin_logged == nullptr;
}

shared_ptr<Reporter> Manager::get_week_matches_report(int week)
{
    // TODO check week
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

void Manager::check_admin_can_login(User_login_info input)
{
    if (!is_user_logged())
        throw BAD_REQUEST_MASSAGE;
    if(input.username != ADMIN_NAME || input.password!= ADMIN_PASSWORD)
        throw BAD_REQUEST_MASSAGE;
}

shared_ptr<Reporter> Manager::register_admin(User_login_info input)
{
    try
    {
        check_admin_can_login(input);

        admin_logged = admins[input.username];

        return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");

    }
    catch(const string& error)
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
        admin_logged = nullptr;

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

    best_team.insert(make_pair(GK, real_game_manager.get_best_players_in_post(week, GK, 1)));
    best_team.insert(make_pair(DF, real_game_manager.get_best_players_in_post(week, DF, 2)));
    best_team.insert(make_pair(MF, real_game_manager.get_best_players_in_post(week, MF, 1)));
    best_team.insert(make_pair(FW, real_game_manager.get_best_players_in_post(week, FW, 1)));

    return make_shared<Best_team_reporter>(best_team, week);
}

shared_ptr<Reporter> Manager::get_team_players(Team_players_input input)
{
    try
    {
        // TODO rm
        // cout << "name: " << input.name << endl;
        // cout << "sort: " << input.is_sort_with_rank << endl;
        // cout << "have post: " << input.just_special_post << endl;
        // cout << "post: " << input.post << endl;
        // cout << "\\\\\\\\\\\\\\\\\\\\\\\\\n";

        // TODO
        // check_team_players(input);

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

int Manager::get_week()
{
    // TODO
    return 1;
}

void Manager::import_real_teams(League_data input)
{
    real_game_manager.import_teams(input);
}

void Manager::import_real_weeks(map<int, std::vector<Game_input>> input)
{
    real_game_manager.add_league_weeks(input);
}
bool compare_users(User_ranking_data a, User_ranking_data b)
{
    if ((a.point < b.point) || ((a.point == b.point) && (a.name[0] < b.name[0])))
        return 1;
    else
        return 0;
}
shared_ptr<Reporter> Manager::get_users_ranking()
{
    User_ranking_data user_date;
    vector<User_ranking_data> collection;
    for(auto user: users)
    {
        user_date.name = user.first;
        user_date.point = user.second->get_total_score(get_week());
        collection.push_back(user_date);
    }
    sort(collection.begin(), collection.end(), compare_users);
    return make_shared<Massage_reporter>("TODO\n");
}

shared_ptr<Reporter> Manager::open_transfer_window()
{
    if((admin_logged!= nullptr) && transfer_window_status == false)
    {
        transfer_window_status =true ;
        return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
    }
    else if (transfer_window_status == false)
        return make_shared<Massage_reporter>(PERMISSION_DENIED_MASSAGE + "\n");
    else if (transfer_window_status == true)
        return make_shared<Massage_reporter>(BAD_REQUEST_MASSAGE + "\n");

}

shared_ptr<Reporter> Manager::pass_week()
{
    if(admin_logged!= nullptr)
    {
        week_number++;
        return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
    }
    else
        return make_shared<Massage_reporter>(PERMISSION_DENIED_MASSAGE + "\n");

}

shared_ptr<Reporter> Manager::close_transfer_window()
{
    if((admin_logged!= nullptr) && transfer_window_status == true)
    {
        transfer_window_status= false;
        return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
    }
    else if (transfer_window_status == false)
        return make_shared<Massage_reporter>(BAD_REQUEST_MASSAGE + "\n");
    else
        return make_shared<Massage_reporter>(PERMISSION_DENIED_MASSAGE + "\n");

}