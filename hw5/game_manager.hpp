#pragma once
#include "define.hpp"
#include "game_board.hpp"

class game_manager
{
private:
        game_board the_game_board;
public:
        game_manager(/* args */);
        void draw(RenderWindow &window);
        ~game_manager();
};

