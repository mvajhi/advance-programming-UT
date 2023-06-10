#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <fstream>
#include <functional>
#include <cmath>
#include "time.hpp"

using namespace std;

typedef string Name;

// enum
enum Role
{
    gk,
    lb,
    cb,
    rb,
    mf,
    lw,
    cf,
    rw
};

// struct
struct Player_info
{
    string name;
    int price;
    string post;
};

struct Team_data
{
    string team_name;
    vector<Player_info> gk;
    vector<Player_info> df;
    vector<Player_info> mf;
    vector<Player_info> fw;
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

struct Important_match_info
{
    bool win_status;
    int team_ga;
    int team_gf;
};

struct Player_status
{
    bool is_played;
    int row_score;
    double score;
    bool red_card;
    int yellow_card;
    bool injured;
    bool clean_sheet;
    int goal;
    int assist;
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

struct Match_detail
{
    pair<int, int> teams_goal;
    map<Name, Player_status> players_status;
    pair<map<Name, Role>, map<Name, Role>> players_teams;
    pair<Name, Name> teams_name;
    vector<Name> goals;
    vector<Name> goals_assist;
    vector<Name> own_goal;
};

struct Week_state
{
    vector<Match_detail> weeks_games;
};

struct User_ranking_data
{
    double point;
    string name;
};

struct Key_change
{
    vector<string> goals;
    vector<string> assists;
};

struct Match_info
{
    vector<string> team_names;
    vector<string> team_results;
    vector<string> injured_players;
    vector<string> yellow_card_players;
    vector<string> red_card_players;
    Key_change goals_and_assists;
    vector<string> team1_players;
    vector<string> team2_players;
};

struct Fantasy_team_data
{
    string team_name;
    string gk, df1, df2, mf, fw;
    double total_score;
    // TODO
    int total_cost;
    bool is_full;
    bool have_captain;
    string captain_name;
};

struct Fantasy_input
{
    bool have_name;
    string name;
};

struct Match_report_data
{
    pair<Name, int> team1;
    pair<Name, int> team2;
};

// status massage
const string SUCCESS_MASSAGE = "OK";
const string EMPTY_MASSAGE = "Empty";
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
const string TEAM_LIST_COMMAND = "GET league_standings";
const string SIGNUP_COMMAND = "POST signup ? team_name";
const string USERS_RANKING_COMMAND = "GET users_ranking";
const string BEST_TEAM_COMMAND = "GET team_of_the_week ?";
const string BUY_PLAYER_COMMAND = "POST buy_player ? name";
const string SELL_PLAYER_COMMAND = "POST sell_player ? name";
const string SET_CAPTAIN_COMMAND = "POST set_captain ? name";
const string MATCH_REPORT_COMMAND = "GET matches_result_league";
const string REGISTER_ADMIN_COMMAND = "POST register_admin ? username";
const string OPEN_TRANSFER_WINDOW_COMMAND = "POST open_transfer_window";
const string CLOSE_TRANSFER_WINDOW_COMMAND = "POST close_transfer_window";

// key word in command
const string PASSWORD_COMMAND = "password";
const string WEEK_NUM_COMMAND = "week_num";
const string SORT_BY_SCORE_COMMAND = "rank";
const string OWN_GOAL_COMMAND = "OWN_GOAL";

// commands size
const int POST_COMMAND_SIZE = 2;
const int LOGIN_COMMAND_SIZE = 7;
const int CAPTAIN_COMMAND_SIZE = 5;
const int TRANSFER_COMMAND_SIZE = 5;
const int GET_SQUAD_COMMAND_SIZE = 5;
const int TEAM_LIST_COMMAND_SIZE = 2;
const int MATCHES_COMMAND_MIN_SIZE = 3;
const int MATCHES_COMMAND_MAX_SIZE = 5;
const int TEAM_PLAYERS_COMMAND_SIZE = 5;
const int BEST_TEAM_COMMAND_MIN_SIZE = 3;
const int BEST_TEAM_COMMAND_MAX_SIZE = 5;
const int REGISTER_ADMIN_COMMAND_SIZE = 7;
const int TEAM_PLAYERS_COMMAND_MAX_SIZE = 7;

// commands index
const int USERNAME_INDEX = 4;
const int PASSWORD_INDEX = 6;
const int WEEK_NUM_INDEX = 3;
const int CAPTAIN_NAME_INDEX = 4;
const int POST_COMMAND_INDEX = 5;
const int TEAM_NAME_COMMAND_INDEX = 4;

// file
const char ROLE_SEPARATOR = ',';
const char TEAM_SEPARATOR = ':';
const char PLAYER_SEPARATOR = ';';
const char TEAM_NAME_SEPARATOR = '_';
const char PRICE_SEPARATOR = ':';
const char GOALS_ASSISTS_SEPARATOR = ':';

// file index
const int GK_INDEX = 1;
const int DF_INDEX = 2;
const int MF_INDEX = 3;
const int FW_INDEX = 4;
const int GOAL_INDEX = 0;
const int FIRST_WEEK = 1;
const int FINAL_WEEK = 19;
const int NAME_INDEX = 0;
const int PRICE_INDEX = 1;
const int TEAM1_INDEX = 0;
const int TEAM2_INDEX = 1;
const int RESULT_INDEX = 1;
const int ASSISTS_INDEX = 1;
const int RED_CARD_INDEX = 4;
const int PLAYERS_NUMBER = 11;
const int TEAM_NAME_INDEX = 0;
const int YELLOW_CARD_INDEX = 3;
const int SCORE_POINT_INDEX = 1;
const int GOALS_ASSIST_INDEX = 5;
const int TEAM1_PLAYERS_INDEX = 6;
const int TEAM2_PLAYERS_INDEX = 7;
const int INJURED_PLAYER_INDEX = 2;

const int GK_NUMBER = 0;
const int LB_NUMBER = 1;
const int CB1_NUMBER = 2;
const int CB2_NUMBER = 3;
const int RB_NUMBER = 4;
const int MF1_NUMBER = 5;
const int MF2_NUMBER = 6;
const int MF3_NUMBER = 7;
const int LW_NUMBER = 8;
const int CF_NUMBER = 9;
const int RW_NUMBER = 10;

// files address
const string CSV_FORMAT = ".csv";
const string DATA_ADDRESS = "./data";
const string LEAGUE_ADDRESS = DATA_ADDRESS + "/premier_league.csv";
const string WEEK_ADDRESS = DATA_ADDRESS + "/weeks_stats" + "/week_";

// posts
const string GK = "gk";
const string CB = "cb";
const string LB = "lb";
const string RB = "rb";
const string LW = "lw";
const string RW = "rw";
const string DF = "df";
const string MF = "mf";
const string FW = "fw";
const string CF = "cf";
const vector<string> POSTS = {GK, DF, MF, FW};
const vector<Role> ORIGINAL_POSTS = {gk, lb, cb, cb, rb,
                                     mf, mf, mf, lw, cf, rw};

// real game role
const int WIN_SCORE = 3;
const int DRAW_SCORE = 1;
const int LOSE_SCORE = 0;
const int MAX_YELLOW_CARD = 3;
const int INITIAL_PLAYER_SCORE = 0;
const int NUM_WEEK_DONT_PLAY_FOR_INJURED = 3;
const int NUM_WEEK_DONT_PLAY_FOR_RED_CARD = 1;

const int WIN_PLAYER_SCORE = 5;
const int DRAW_PLAYER_SCORE = 1;
const int LOSE_PLAYER_SCORE = -1;

const int OWN_GOAL_SCORE = -3;

const int DEFAULT_GK_SCORE = 3;
const int NO_GOAL_GK_SCORE = 5;
const int GOAL_GK_SCORE = -1;

const int DEFAULT_MF_SCORE = 0;
const int NO_GOAL_MF_SCORE = 1;
const int MF_PLAYER_GOAL_SCORE = 3;
const int MF_PLAYER_ASSIST_SCORE = 2;
const int GA_MF_SCORE = -1;

const int DEFAULT_FW_SCORE = 0;
const int FW_PLAYER_ASSIST_SCORE = 1;
const int NO_GOAL_FW_SCORE = -1;
const int FW_PLAYER_GOAL_SCORE = 3;

const int DEFAULT_DF_SCORE = 1;
const int NO_GOAL_DF_SCORE = 2;
const int DF_PLAYER_GOAL_SCORE = 4;
const int DF_PLAYER_ASSIST_SCORE = 3;
const int DF_GA_IN_SIDE_SCORE = -1;

// fantasy game role
const int TEAM_SIZE = 5;
const int NOT_FULL = 20;
const int MAX_BUY_COUNT = 2;
const int MAX_SELL_COUNT = 2;

// allowed size of each post index
const int GK_ALLOWED_SIZE = 1;
const int DF_ALLOWED_SIZE = 2;
const int MF_ALLOWED_SIZE = 1;
const int FW_ALLOWED_SIZE = 1;

// admins information
const string ADMIN_NAME = "admin";
const string ADMIN_PASSWORD = "123456";

// budget
const int DEFAULT_BUDGET = 2500;