#include "game_board.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

game_board::game_board(/* args */)
{
}

void game_board::read_board_game(string address_file)
{
        ifstream board_file(address_file);
        string line;
        vector<string> output;
        while (getline(board_file, line))
                output.push_back(line);
        board = output;
}

game_board::~game_board()
{
}
