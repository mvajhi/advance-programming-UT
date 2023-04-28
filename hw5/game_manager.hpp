#pragma once
#include "window.hpp"
#include "game_board.hpp"
#include "define.hpp"
// #include "turtle.hpp"
// #include "person.hpp"
class Game_manager
{
private:
        window the_window;
        Game_board the_game_board;
        bool is_in_menu;
        RectangleShape button;

        // Turtle player;

        vector<Sprite> get_updated_window();
        vector<string> read_map_file(string address_file);
        void proccess_new_block(Vector2i position, char value);
        void proccess_text_map(vector<string> text_map);
        void update_menu();
        void handel_menu_event(Event event);

public:
        Game_manager(/* args */);
        void update();
        void read_level1();
        void handel_event(Event event);
        void proccess_events();
        ~Game_manager();
};
