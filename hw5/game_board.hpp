#pragma once
#include "define.hpp"

class game_board
{
private:
        vector<string> board;
        Texture t_floor;
        Sprite floor;
public:
        game_board(/* args */);
        void read_board_game(string address_file);
        void draw_board(RenderWindow &window);
        ~game_board();
};
