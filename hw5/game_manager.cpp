#include <SFML/Graphics.hpp>
#include "game_manager.hpp"
#include "define.hpp"
#include "game_board.hpp"


game_manager::game_manager(/* args */)
{
}

void game_manager::draw(RenderWindow &window)
{
         the_game_board.draw_board(window);
}

game_manager::~game_manager()
{
}