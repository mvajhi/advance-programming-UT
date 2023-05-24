#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>

using namespace std;
const char ROLE_SEPARATOR =',';
const char PLAYER_SEPARATOR = ';';
const int GK_INDEX = 1;
const int DF_INDEX = 2;
const int MF_INDEX = 3;
const int FW_INDEX = 4;
const int TEAM_NAME_INDEX = 0;
const string LEAGUE_ADDRESS ="./data/premier_league.csv";
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

