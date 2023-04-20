#include "game_board.hpp"

game_board::game_board(/* args */)
{
    vetcor<vector<char>> read_board_game(string file_address)
    {
        
        ifstream board_file(file_address);
        string line;
        int row_conter=0;
        vetcor<vector<char>> output;
        while(getline(board_file,line))
        {
            output.push_back({});

        
            for(int char_counter=0;char_counter<line.size();char_counter++)
            {
                output[row_counter].push_back(line[char_counter]);
            }
            row_counter++;

        }
        board_file.close();
        return output;

    }

}

game_board::~game_board()
{
}
