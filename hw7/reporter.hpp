#pragma once

#include "define.hpp"

class Match;

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