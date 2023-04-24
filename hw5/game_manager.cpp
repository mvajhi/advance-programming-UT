#include <SFML/Graphics.hpp>
#include "game_manager.hpp"
#include "define.hpp"
#include "game_board.hpp"

vector<Drawable *> game_manager::get_updated_window()
{
        vector<Drawable *> updated_window;
        updated_window = the_game_board.get_board();

        return updated_window;
}

game_manager::game_manager(/* args */) : the_window()
{
}

void game_manager::update()
{
        vector<Drawable *> updated_window = get_updated_window();
        the_window.update(updated_window, Vector2f(0, 0));
}

// TODO remove this function
void game_manager::read_level1()
{
        the_game_board.set_board_game(ADDR_LEVEL_1);
}

game_manager::~game_manager()
{
}