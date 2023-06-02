#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <fstream>
#include <functional>
#include "time.hpp"

using namespace std;

struct Team_data
{
    string team_name;
    vector<string> gk;
    vector<string> df;
    vector<string> mf;
    vector<string> fw;
};

struct League_data
{
    map<string, shared_ptr<Team_data>> teams;
};

struct User_login_info
{
    string username;
    string password;
};

struct Player_status
{
    bool is_played;
    double score;
    bool red_card;
    int yellow_card;
    bool injured;
};

struct Game_input
{
    map<string, Player_status> players_status;
    pair<string, int> team1;
    pair<string, int> team2;
};

struct Team_status
{
    int score;
    int ga;
    int gf;
};

struct Team_players_input
{
    string name;
    bool just_special_post;
    string post;
    bool is_sort_with_rank;
    int week;
};

struct Week_state
{
    vector<Game_input> weeks_games;
};

struct User_ranking_data
{
    double point;
    string name;
};

struct Match_info
{
    vector<string> team_names;
    vector<string> team_results;
    vector<string> injured_players;
    vector<string> yellow_card_players;
    vector<string> red_card_players;
    vector<string> score_players;
};

struct Fantasy_team_data
{
    string team_name;
    string gk,df1,df2,mf,fw;
    double total_score;
};

// status massage
const string SUCCESS_MASSAGE = "OK";
const string NOT_FOUND_MASSAGE = "Not Found";
const string BAD_REQUEST_MASSAGE = "Bad Request";
const string PERMISSION_DENIED_MASSAGE = "Permission Denied";
const string PLAYER_CANT_PLAY_MASSAGE = "This player is not available for next week";

// commands
const string LOGOUT_COMMAND = "POST logout";
const string GET_SQUAD_COMMAND = "GET squad ?";
const string PASS_WEEK_COMMAND = "POST pass_week";
const string TEAM_PLAYERS_COMMAND = "GET players ?";
const string LOGIN_COMMAND = "POST login ? team_name";
const string TEAM_LIST_COMMAND = "GET league_standing";
const string SIGNUP_COMMAND = "POST signup ? team_name";
const string USERS_RANKING_COMMAND = "GET users_ranking";
const string BEST_TEAM_COMMAND = "GET team_of_the_week ?";
const string BUY_PLAYER_COMMAND = "POST buy_player ? name";
const string SELL_PLAYER_COMMAND = "POST sell_player ? name";
const string REGISTER_ADMIN_COMMAND = "POST register_admin ? username";
const string OPEN_TRANSFER_WINDOW_COMMAND = "POST open_transfer_window";
const string CLOSE_TRANSFER_WINDOW_COMMAND = "POST close_transfer_window";

// key word in command
const string PASSWORD_COMMAND = "password";
const string WEEK_NUM_COMMAND = "week_num";
const string SORT_BY_SCORE_COMMAND = "rank";

// commands size
const int POST_COMMAND_SIZE = 2;
const int LOGIN_COMMAND_SIZE = 7;
const int TRANSFER_COMMAND_SIZE = 5;
const int GET_SQUAD_COMMAND_SIZE = 5;
const int TEAM_LIST_COMMAND_SIZE = 2;
const int TEAM_PLAYERS_COMMAND_SIZE = 5;
const int BEST_TEAM_COMMAND_MIN_SIZE = 3;
const int BEST_TEAM_COMMAND_MAX_SIZE = 5;
const int REGISTER_ADMIN_COMMAND_SIZE = 7;
const int TEAM_PLAYERS_COMMAND_MAX_SIZE = 7;

// commands index
const int USERNAME_INDEX = 4;
const int PASSWORD_INDEX = 6;
const int WEEK_NUM_INDEX = 3;
const int POST_COMMAND_INDEX = 5;
const int TEAM_NAME_COMMAND_INDEX = 4;

// file
const char ROLE_SEPARATOR = ',';
const char TEAM_SEPARATOR = ':';
const char PLAYER_SEPARATOR = ';';
const char TEAM_NAME_SEPARATOR = '_';

// file index
const int GK_INDEX = 1;
const int DF_INDEX = 2;
const int MF_INDEX = 3;
const int FW_INDEX = 4;
const int FIRST_WEEK = 1;
const int FINAL_WEEK = 19;
const int TEAM1_INDEX = 0;
const int TEAM2_INDEX = 1;
const int RESULT_INDEX = 1;
const int SCORES_INDEX = 5;
const int RED_CARD_INDEX = 4;
const int TEAM_NAME_INDEX = 0;
const int YELLOW_CARD_INDEX = 3;
const int SCORE_POINT_INDEX = 1;
const int INJURED_PLAYER_INDEX = 2;

// files address
const string CSV_FORMAT = ".csv";
const string DATA_ADDRESS = "./data";
const string LEAGUE_ADDRESS = DATA_ADDRESS + "/premier_league.csv";
const string WEEK_ADDRESS = DATA_ADDRESS + "/weeks_stats" + "/week_";

// posts
const string GK = "gk";
const string DF = "df";
const string MF = "mf";
const string FW = "fw";
const vector<string> POSTS = {GK, DF, MF, FW};

// real game role
const int WIN_SCORE = 3;
const int DRAW_SCORE = 1;
const int LOSE_SCORE = 0;
const int MAX_YELLOW_CARD = 3;
const int NUM_WEEK_DONT_PLAY_FOR_INJURED = 3;
const int NUM_WEEK_DONT_PLAY_FOR_RED_CARD = 1;

// fantasy game role
const int MAX_BUY_COUNT = 2;
const int MAX_SELL_COUNT = 2;
const int TEAM_SIZE = 5;
const int NOT_FULL = 20;

// allowed size of each post index
const int GK_ALLOWED_SIZE = 1;
const int DF_ALLOWED_SIZE = 2;
const int MF_ALLOWED_SIZE = 1;
const int FW_ALLOWED_SIZE = 1;

// admins information
const string ADMIN_NAME = "admin";
const string ADMIN_PASSWORD = "123456";