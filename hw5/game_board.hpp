#pragma once
#include "define.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class game_board
{
private:
        vector<string> board;
public:
        game_board(/* args */);
        void read_board_game(string address_file);
        ~game_board();
};
