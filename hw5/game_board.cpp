#include "game_board.hpp"

game_board::game_board(/* args */)
{
        t_floor.loadFromFile(ADDR_FLOOR);
        floor.setTexture(t_floor);
        floor.setScale(FLOOR_SCALE, FLOOR_SCALE);
        floor.setPosition(BLOCK_SIZE / 2, WINDOW_HEIGHT - BLOCK_SIZE / 2);

        vector<Sprite> width_block(WINDOW_WIDTH / BLOCK_SIZE, floor);
        vector<vector<Sprite>> blocks(WINDOW_HEIGHT / BLOCK_SIZE, width_block);

        for (int i = 0; i < blocks.size(); i++)
                for (int j = 0; j < blocks[i].size(); j++)
                        blocks[i][j].setPosition(j * BLOCK_SIZE, i * BLOCK_SIZE);

        window_board = blocks;
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

game_board::~game_board()
{
}

vector<Drawable *> game_board::get_board(Vector2f position)
{
        // TODO should return board with position
        // TODO draw with file

        vector<Drawable *> board;
        for (int i = 0; i < window_board.size(); i++)
                for (int j = 0; j < window_board[i].size(); j++)
                        board.push_back(&window_board[i][j]);

        return board;
}
