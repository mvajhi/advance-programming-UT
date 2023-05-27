#include "manager.hpp"

Manager::Manager()
{
}

bool Manager::can_signup(User_login_info input)
{
    // check no one login
    if (user_logged != nullptr)
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
    if (user_logged != nullptr)
        throw BAD_REQUEST_MASSAGE;

    // check name
    if (users.count(input.username) == 0)
        throw NOT_FOUND_MASSAGE;

    // check password
    if (!users[input.username]->is_password_valid(input.password))
        throw PERMISSION_DENIED_MASSAGE;
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

shared_ptr<Reporter> Manager::logout()
{
    user_logged = nullptr;

    return make_shared<Massage_reporter>(SUCCESS_MASSAGE + "\n");
}

void Manager::import_real_teams(League_data input)
{
    real_game_manager.import_teams(input);
}
