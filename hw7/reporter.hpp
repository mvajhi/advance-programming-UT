#pragma once

#include "define.hpp"

class Match;
class Player;

class Reporter
{
public:
    virtual void cli_report() = 0;
};

class Massage_reporter : public Reporter
{
private:
    string massage;

public:
    Massage_reporter(string massage_);
    void cli_report();
};

class Match_reporter : public Reporter
{
private:
    vector<shared_ptr<Match>> matches;

public:
    Match_reporter(vector<shared_ptr<Match>> matches_);
    void cli_report();
};

class Best_team_reporter : public Reporter
{
private:
    map<string, vector<shared_ptr<Player>>> players;
    int week;

    string convert_player_to_cli_output(string role, int index = 0);

public:
    Best_team_reporter(map<string, vector<shared_ptr<Player>>> players_, int week_);
    void cli_report();
};

class Team_player_reporter : public Reporter
{
private:
    vector<shared_ptr<Player>> players;
    int week;

    string convert_player_to_string(shared_ptr<Player> player);

public:
    Team_player_reporter(vector<shared_ptr<Player>> players_, int week_);
    void cli_report();
};