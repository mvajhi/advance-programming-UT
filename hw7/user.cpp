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
