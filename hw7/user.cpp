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

double User::get_total_score(int week_num)
{
    double result = 0;
    for (int week = FIRST_WEEK; week <= week_num; week++)
    {
         result += user_teams[week]->get_score(week) ;
    }
    return result;
}