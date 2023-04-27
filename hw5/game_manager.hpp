#pragma once
#include "define.hpp"
#include "game_board.hpp"
#include "window.hpp"
#include "turtle.hpp"

class Game_manager
{
private:
        Game_board the_game_board;
        window the_window;
        Turtle player;

        vector<Sprite> get_updated_window();

public:
        Game_manager(/* args */);
        void update();
        void read_level1();
        void handel_event(Event event);
        void proccess_events();
        ~Game_manager();
};
