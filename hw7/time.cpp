#include "time.hpp"

int Time::week = 0;
bool Time::transfer = true;

int Time::get_week()
{
    return week;
}

int Time::get_next_week()
{
    return week + 1;
}

bool Time::is_transfer_open()
{
    return transfer;
}

bool Time::is_valid_week(int input_week)
{
    return input_week <= week;
}

void Time::close_transfer()
{
    transfer = false;
}

void Time::open_transfer()
{
    transfer = true;
}

void Time::go_next_week()
{
    week++;
}
