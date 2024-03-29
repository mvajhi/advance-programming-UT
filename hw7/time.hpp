#pragma once

#include "define.hpp"

class Time
{
private:
    static int week;
    static bool transfer;

    // change
    static void go_next_week();
    static void open_transfer();
    static void close_transfer();

    friend class Admin;

public:
    // output
    static int get_week();
    static int get_next_week();

    // check
    static bool is_transfer_open();
    static bool is_valid_week(int input_week);
};