#pragma once
#include "define.hpp"
#include "game_board.hpp"
#include "window.hpp"
#include "turtle.hpp"

class game_manager
{
private:
        game_board the_game_board;
        window the_window;
        Turtle player;

        vector<Sprite> get_updated_window();

public:
        game_manager(/* args */);
        void update();
        void read_level1();
        ~game_manager();
};
