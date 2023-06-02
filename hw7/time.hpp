#pragma once

#include "define.hpp"

class Time
{
private:
    static int week;
    static bool transfer;

    static void close_transfer();
    static void open_transfer();
    static void go_next_week();

    friend class Admin;

public:
    static int get_week();
    static int get_next_week();
    static bool is_transfer_open();
    static bool is_valid_week(int input_week);
};