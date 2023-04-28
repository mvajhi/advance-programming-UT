#include <SFML/Graphics.hpp>
#include "game_manager.hpp"
#include "define.hpp"
#include "game_board.hpp"

vector<Sprite> Game_manager::get_updated_window()
{
        vector<Sprite> updated_window;
        updated_window = the_game_board.get_board();
        // updated_window.push_back(player.get_shape());

        return updated_window;
}

vector<string> Game_manager::read_map_file(string address_file)
{
        ifstream board_file(address_file);
        string line;
        vector<string> output;
        while (getline(board_file, line))
                output.push_back(line);
        return output;
}

void Game_manager::proccess_new_block(Vector2i position, char value)
{
        if (value == FLOOR_MAP_SYMBOLE)
                the_game_board.add_new_floor(position);
        // TODO
        // else if (value == PLAYER_MAP_SYMBOLE)
        // TODO player.setpos(pos);
        // else if (value == PLAYER_MAP_SYMBOLE)
        // TODO
}

void Game_manager::proccess_text_map(vector<string> text_map)
{
        for (size_t y = 0; y < text_map.size(); y++)
                for (size_t x = 0; x < text_map[y].length(); x++)
                        proccess_new_block(Vector2i(x, y), text_map[y][x]);
}

Game_manager::Game_manager(/* args */) : the_window(this)
//  player(10, -200)
{
}

void Game_manager::update()
{
        vector<Sprite> updated_window = get_updated_window();

        // TODO should change a,-200 with camera
        // Vector2f camera_postion = player.get_position();
        static float a = 150;
        a += 0.3;

        the_window.update(updated_window, Vector2f(a, 600) /*camera_postion*/);
        // the_window.update(updated_window, camera_postion);
}

// TODO remove this function
void Game_manager::read_level1()
{
        vector<string> text_map = read_map_file(ADDR_LEVEL_1);

        proccess_text_map(text_map);
}

void Game_manager::handel_event(Event event)
{
        if (event.type == Event::Closed)
                the_window.close();
        else if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::W)
                        // TODO
                        cout << "W" << endl;
                else if (event.key.code == Keyboard::A)
                        // TODO
                        cout << "A" << endl;
                else if (event.key.code == Keyboard::D)
                        // TODO
                        cout << "D" << endl;
                else
                        cout << "invalid key\n";
        else
        {
        }
}

void Game_manager::proccess_events()
{
        the_window.get_events();
}

Game_manager::~Game_manager()
{
}