#pragma once

#include "define.hpp"

class Time
{
private:
    static int week;
    static bool transfer;
public:
    static int get_week();
    static bool is_transfer_open();
    static void close_transfer();
    static void open_transfer();
    static void go_next_week();
};