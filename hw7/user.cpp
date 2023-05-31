#include "user.hpp"
User::User(string name_,string password_)
{
    name = name_;
    password = password_;
}
NormalUser::NormalUser(string user_name, string user_pass)
{
    name = user_name;
    password = user_pass;
}

bool NormalUser::is_password_valid(string pass)
{
    return pass == password;
}

string NormalUser::get_name()
{
    return name;
}

shared_ptr<FantasyTeam> NormalUser::get_team(int week)
{
    return user_teams[week];
}

double NormalUser::get_total_score(int week_num)
{
    double result = 0;
    for (int week = FIRST_WEEK; week <= week_num; week++)
    {
         result += user_teams[week]->get_score(week) ;
    }
    return result;
}

void NormalUser::sell_player(string name)
{

}

void NormalUser::buy_player(string name)
{

}

Admin::Admin() : User("admin","123456")
{

}