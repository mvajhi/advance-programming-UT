#include "game_board.hpp"

game_board::game_board(/* args */)
{
        t_floor.loadFromFile(ADDR_FLOOR);
        floor.setTexture(t_floor);
        floor.setPosition(100, 100);
}

void game_board::read_board_game(string address_file)
{
        ifstream board_file(address_file);
        string line;
        vector<string> output;
        while (getline(board_file, line))
                output.push_back(line);
        board = output;
}

void game_board::draw_board(RenderWindow &window)
{
        window.draw(floor);
}

game_board::~game_board()
{
}
