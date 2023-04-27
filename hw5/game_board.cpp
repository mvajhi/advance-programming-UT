#include "game_board.hpp"

vector<string> Game_board::read_map_file(string address_file)
{
        ifstream board_file(address_file);
        string line;
        vector<string> output;
        while (getline(board_file, line))
                output.push_back(line);
        return output;
}

vector<Sprite> Game_board::set_map()
{
        vector<Sprite> new_map;
        Sprite tmp_floor = floor;

        for (size_t y = 0; y < text_map.size(); y++)
                for (size_t x = 0; x < text_map[y].length(); x++)
                        if (text_map[y][x] == FLOOR_MAP_SYMBOLE)
                        {
                                tmp_floor.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
                                new_map.push_back(tmp_floor);
                        }
        return new_map;
}

Game_board::Game_board(/* args */)
{
        t_floor.loadFromFile(ADDR_FLOOR);
        floor.setTexture(t_floor);
        floor.setScale(FLOOR_SCALE, FLOOR_SCALE);
}

void Game_board::set_board_game(string address_file)
{
        text_map = read_map_file(address_file);
        map = set_map();
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
