#pragma once

#include "define.hpp"
#include "FantasyTeam.hpp"
class User
{
private:
    string name;
    string password;
    map<int , FantasyTeam*> user_teams;
    map<int , Transfer_State> transfers_state;

public:
    User(string user_name, string user_pass);
    bool is_password_valid(string pass);
    string get_name();
    double get_total_score(int week_num);
    FantasyTeam* get_team(int week);
    void buy_player(string name);
    void sell_player(string name);
};
