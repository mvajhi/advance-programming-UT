#pragma once

#include "define.hpp"

class Match;
class Player;
class Team;

class Reporter
{
public:
    virtual void get_cli_report() = 0;
};

class Massage_reporter : public Reporter
{
private:
    string massage;

public:
    Massage_reporter(string massage_);
    void get_cli_report();
};

class Match_reporter : public Reporter
{
private:
    vector<Match_report_data> matches;

public:
    Match_reporter(vector<shared_ptr<Match>> matches_);
    void get_cli_report();
};

class Best_team_reporter : public Reporter
{
private:
    map<string, vector<shared_ptr<Player>>> players;
    int week;

    string convert_player_to_cli_output(string role, int index = 0);

public:
    Best_team_reporter(map<string, vector<shared_ptr<Player>>> players_,
                       int week_);
    void get_cli_report();
};

class Team_player_reporter : public Reporter
{
private:
    vector<shared_ptr<Player>> players;
    int week;

    string convert_player_to_string(shared_ptr<Player> player);

public:
    Team_player_reporter(vector<shared_ptr<Player>> players_, int week_);
    void get_cli_report();
};

class Team_list_reporter : public Reporter
{
private:
    vector<shared_ptr<Team>> teams;
    int week;

    string convert_team_to_string(shared_ptr<Team> team);

public:
    Team_list_reporter(vector<shared_ptr<Team>> teams_, int week_);
    void get_cli_report();
};

class User_ranks_report : public Reporter
{
private:
    vector<User_ranking_data> collection;

    string convert_collection_to_string(User_ranking_data user);

public:
    User_ranks_report(vector<User_ranking_data> collection_);
    void get_cli_report();
};

class FantasyTeamReporter : public Reporter
{
private:
    Fantasy_team_data target_team;

    void sort_defender();
    vector<string> create_team_player_output();
    void add_captain_in_output(vector<string> &output);

public:
    FantasyTeamReporter(Fantasy_team_data target_team_);
    void get_cli_report();
};