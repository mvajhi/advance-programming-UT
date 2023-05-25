#pragma once

#include "define.hpp"

class User
{
private:
    string name;
    string password;
public:
    User(string user_name, string user_pass);
    bool is_password_valid(string pass);
    string get_name();
};
