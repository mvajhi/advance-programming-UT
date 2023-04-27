#include <SFML/Graphics.hpp>
#include "game_manager.hpp"
#include "define.hpp"
#include "game_board.hpp"


vector<Sprite> Game_manager::get_updated_window()
{
        vector<Sprite> updated_window;
        updated_window = the_game_board.get_board();

        return updated_window;
}

Game_manager::Game_manager(/* args */) : the_window(this),
        player(0 ,0)
{
}

void Game_manager::update()
{
        vector<Sprite> updated_window = get_updated_window();

        // TODO should change a,-200 with camera
        Vector2f camera_postion = player.get_position();
        static float a = 0;
        a += 0.3;

        the_window.update(updated_window, Vector2f(a, -200));
}

// TODO remove this function
void Game_manager::read_level1()
{
        the_game_board.set_board_game(ADDR_LEVEL_1);
}

void Game_manager::handel_event(Event event)
{
        if(event.type == Event::Closed)
        {
                // TODO end proccess
                the_window.close();
        }
}

void Game_manager::proccess_events()
{
        the_window.get_events();
}

Game_manager::~Game_manager()
{
}