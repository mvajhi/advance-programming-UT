#pragma once
#include "define.hpp"

class Game_board
{
private:
        vector<string> text_map;
        Texture t_floor;
        Sprite floor;
        vector<Sprite> map;

public:
        Game_board(/* args */);
        void add_new_floor(Vector2i position);
        void reset_map();
        vector<Vector2f> get_floor_positions();
        ~Game_board();
        vector<Sprite> get_board();
};
