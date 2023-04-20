#include "game_board.hpp"

game_board::game_board(/* args */)
{
    vetcor<vector<char>> read_board_game(string address_file)
    {
        
        ifstream board_file(address_file);
        string line;
        int row_conter=0;
        vetcor<vector<char>> output;
        while(getline(board_file,line))
        {
            output.push_back({});

        
            for(int char_counter=0;char_counter<line.size();char_counter++)
            {
                output.push_back(line[char_counter]) 
            }

        }
    }

}

game_board::~game_board()
{
}
