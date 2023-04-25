#pragma once
#include "define.hpp"

class Game_board
{
private:
        vector<string> text_map;
        Texture t_floor;
        Sprite floor;
        vector<Sprite> map;

        vector<string> read_map_file(string address_file);
        vector<Sprite> set_map();

public:
        Game_board(/* args */);
        void set_board_game(string address_file);
        ~Game_board();
        vector<Sprite> get_board();
};
