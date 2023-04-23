#pragma once
#include "define.hpp"

class game_board
{
private:
        vector<string> board;
        Texture t_floor;
        Sprite floor;
        vector<vector<Sprite>> window_board;

public:
        game_board(/* args */);
        void read_board_game(string address_file);
        ~game_board();
        vector<Drawable *> get_board(Vector2f position);
};
