#include <SFML/Graphics.hpp>
#include "game_manager.hpp"
#include "define.hpp"
#include "game_board.hpp"
#include <cmath>
#include <map>

vector<Sprite> Game_manager::get_updated_window()
{
        vector<Sprite> updated_window;
        updated_window = the_game_board.get_board();
        updated_window.push_back(player.get_shape());

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
        position = convert_text_to_pixle_pos(position);

        if (value == FLOOR_MAP_SYMBOLE)
                the_game_board.add_new_floor(position);
        // TODO
        else if (value == PLAYER_MAP_SYMBOLE)
                player.set_pos(position);
        // else if (value == PLAYER_MAP_SYMBOLE)
        // TODO
}

void Game_manager::proccess_text_map(vector<string> text_map)
{
        for (size_t y = 0; y < text_map.size(); y++)
                for (size_t x = 0; x < text_map[y].length(); x++)
                        proccess_new_block(Vector2i(x, y), text_map[y][x]);
}

Vector2i Game_manager::convert_text_to_pixle_pos(Vector2i position)
{
        return Vector2i(position.x * BLOCK_SIZE, position.y * BLOCK_SIZE);
}

Game_manager::Game_manager(/* args */) : the_window(this),
                                         player(1, Vector2f(1500, 500), 5, 0, Vector2f(20, 0), ADDR_PLAYER)
{
}

void Game_manager::update()
{
        if (the_menu.is_in_menu())
        {
                the_menu.update_menu(the_window);
                return;
        }

        vector<Sprite> updated_window = get_updated_window();

        // TODO should change a,-200 with camera
        Vector2f camera_postion = player.get_position();
        static float a = 150;
        a += 0.3;

        // the_window.update(updated_window, Vector2f(a, 600) /*camera_postion*/);
        the_window.update(updated_window, camera_postion);
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
        else if (the_menu.is_in_menu())
                the_menu.handel_menu_event(event);
        else if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::W)
                {
                        player.move(MOVE_UP);

                        cout << "W" << endl;
                }
                else if (event.key.code == Keyboard::A)
                {
                        player.move(MOVE_LEFT);
                        cout << "A" << endl;
                }
                else if (event.key.code == Keyboard::D)
                {
                        player.move(MOVE_RIGHT);
                        cout << "D" << endl;
                }
                else if (event.key.code == Keyboard::Escape)
                        the_menu.show();
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

void Game_manager::make_and_send_report()
{
        bool report[4] = {false, false, false, false};

        vector<Vector2f> floors = the_game_board.get_floor_positions();

        for (auto i : floors)
        {
                int collision = check_collision(player.get_position(), i, player.get_move_size());

                if (collision != NO_COLLISION)
                        report[collision] = true;
        }

        player.set_report(report);
}

Game_manager::~Game_manager()
{
}

int Game_manager::check_collision(Vector2f person_pos, Vector2f object_pos, Vector2f move_size)
{
        float x = object_pos.x;
        float y = object_pos.y;

        if (person_pos.y <= y && y < person_pos.y + BLOCK_SIZE &&
            x <= person_pos.x + move_size.x + BLOCK_SIZE && person_pos.x + move_size.x + BLOCK_SIZE < x + BLOCK_SIZE)
        {
                // cout << "right\n";
                // report[RIGHT] = tre;
                return RIGHT;
        }

        if (person_pos.x <= x && x < person_pos.x + BLOCK_SIZE && y <= person_pos.y + move_size.y + BLOCK_SIZE && person_pos.y + move_size.y + BLOCK_SIZE < y + BLOCK_SIZE)
        {
                // cout << "down\n";
                // report[DOWN] = true;
                return DOWN;
        }

        if (person_pos.y <= y && y < person_pos.y + BLOCK_SIZE &&
            x < person_pos.x - move_size.x && person_pos.x - move_size.x <= x + BLOCK_SIZE)
        {
                // cout << "left\n";
                // report[LEFT] = true;
                return LEFT;
        }

        if (person_pos.x <= x && x < person_pos.x + BLOCK_SIZE &&
            y - BLOCK_SIZE < person_pos.y - move_size.y - BLOCK_SIZE && person_pos.y - move_size.y - BLOCK_SIZE <= y)
        {
                // cout << "up\n";
                // report[UP] = true;
                // new_report.floor.push_back(up);
                // cout << "pos: " << player_pos.y + move_size.y << endl;
                // cout << "move size: " << move_size.y << endl;
                // cout << "\\\\\\\\\\\\\\\\\ny+b: " << y + BLOCK_SIZE << "\ny + 2b" << y + 2 * BLOCK_SIZE << "\\\\\\\\\\\n";
                // cout << "\\\\\\\\\\\\\\\\\\\\\nmy pos:\n\tx: " << player_pos.x << "\n\ty: " << player_pos.y << "\n\\\\\\\\\\\\\\\\\\\\\n";
                // cout << "\\\\\\\\\\\\\\\\\\\\\nup pos:\n\tx: " << x << "\n\ty: " << y << "\n\\\\\\\\\\\\\\\\\\\\\n";
                return UP;
        }

        return NO_COLLISION;
}

bool Game_manager::is_in_menus()
{
        return the_menu.is_in_menu();
}
