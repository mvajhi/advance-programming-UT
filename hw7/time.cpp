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
    // TODO check can go
    week++;
}
