#pragma once

#include "define.hpp"
#include "FantasyTeam.hpp"
class User
{
protected:
    string name;
    string password;
public:
    User(string , string);
    string get_name(){ return name;}
    string get_password(){return password;}
};
class NormalUser: public User
{
private:
    map<int, shared_ptr<FantasyTeam>> user_teams;
//        map<int , Transfer_state> transfers_state;

public:
    NormalUser(string user_name, string user_pass);
    bool is_password_valid(string pass);
    string get_name();
    double get_total_score(int week_num);
    shared_ptr<FantasyTeam> get_team(int week);
     void buy_player(string name);
     void sell_player(string name);
};
class Admin: public User
{
private:
    bool is_transfer_open;
    int week_number;

public:
    Admin();

};
