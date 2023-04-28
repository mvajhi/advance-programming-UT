#include "game_board.hpp"

Game_board::Game_board(/* args */)
{
        t_floor.loadFromFile(ADDR_FLOOR);
        floor.setTexture(t_floor);
        floor.setScale(FLOOR_SCALE, FLOOR_SCALE);
}

void Game_board::add_new_floor(Vector2i position)
{
        Sprite tmp_floor = floor;
        tmp_floor.setPosition(position.x, position.y);
        map.push_back(tmp_floor);
}

void Game_board::reset_map()
{
        map.clear();
}

vector<Vector2f> Game_board::get_floor_positions()
{
        vector<Vector2f> floor_pos;

        for (auto i : map)
                floor_pos.push_back(i.getPosition());

        return floor_pos;
}

Game_board::~Game_board()
{
}

vector<Sprite> Game_board::get_board()
{
        vector<Sprite> board;
        for (size_t i = 0; i < map.size(); i++)
                board.push_back(map[i]);

        return board;
}
