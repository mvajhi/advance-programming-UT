#pragma once

#include "define.hpp"

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