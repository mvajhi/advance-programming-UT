#include <SFML/Graphics.hpp>
#include "game_manager.hpp"
#include "define.hpp"
#include "game_board.hpp"

vector<Drawable *> game_manager::get_updated_window()
{
        vector<Drawable *> updated_window;
        Vector2f pos(0,0);
        updated_window = the_game_board.get_board(pos);

        return updated_window;
}

game_manager::game_manager(/* args */) : the_window()
{
}

void game_manager::update()
{
        vector<Drawable *> updated_window = get_updated_window();
        the_window.update(updated_window);
}

game_manager::~game_manager()
{
}