#pragma once
#include "define.hpp"

class game_board
{
private:
        vector<string> text_map;
        Texture t_floor;
        Sprite floor;
        vector<Sprite> map;

        vector<string> read_map_file(string address_file);
        vector<Sprite> set_map();

public:
        game_board(/* args */);
        void set_board_game(string address_file);
        ~game_board();
        vector<Drawable *> get_board();
};
