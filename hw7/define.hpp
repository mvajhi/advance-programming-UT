#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <fstream>

using namespace std;

struct Team
{
    string team_name;
    vector<string> gk;
    vector<string> df;
    vector<string> mf;
    vector<string> fw;
};
struct League
{
    map<string,shared_ptr<Team> > teams;

};

struct User_login_info
{
    string username;
    string password;
};

// status massage
const string SUCCESS_MASSAGE = "OK";
const string BAD_REQUEST_MASSAGE = "Bad Request";
const string PERMISSION_DENIED_MASSAGE = "Permission Denied";
const string NOT_FOUND_MASSAGE = "Not Found";

// commands
const string SIGNUP_COMMAND = "POST signup ?";
const string LOGIN_COMMAND = "POST login ?";
const string LOGOUT_COMMAND = "POST logout";


// commands size
const int LOGIN_COMMAND_SIZE = 7;

// commands index
const int USERNAME_INDEX = 4;
const int PASSWORD_INDEX = 6;

// file
const char ROLE_SEPARATOR =',';
const char PLAYER_SEPARATOR = ';';

// file index
const int GK_INDEX = 1;
const int DF_INDEX = 2;
const int MF_INDEX = 3;
const int FW_INDEX = 4;
const int TEAM_NAME_INDEX = 0;

// files address
const string DATA_ADDRESS ="./data";
const string LEAGUE_ADDRESS = DATA_ADDRESS + "/premier_league.csv";