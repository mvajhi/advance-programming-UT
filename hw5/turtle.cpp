#include "person.hpp"
#include "turtle.hpp"
#include <vector>
#include <utility>
#include <string>
Turtle::Turtle(int x_, int y_, int v_x_, int v_y_, int jump_high_, int health_, int score_)
    : Person(health_, x_, y_, jump_high_, v_x_, v_y_)
{
    score = score_;
}
vector<string> Turtle::horizontal_move(vector<string> game_board, pair<int, int> portal_coordinate, int status)
{
    int side;
    initialize(side, status);
    
        
            if(y<=JUMP_HIGH-1)
                {
                    if(encounter_floor_when_up(game_board)!=WITHOUT_ENCOUNTER_FLOOR)
                    {
                        game_board=encounter_diamon_or_star_when_go_up(encounter_floor_when_up(game_board),game_board);
                        game_board[x][y]=SPACE_SYMBOL;
                        game_board[x][y-encounter_floor_when_up(game_board)+1]=TURTLE_SYMBOL;
                        y=y-encounter_floor_when_up(game_board)+1;
                        v_x=0;
                        v_y=0;
                        return game_board;

                    }
                    else
                    {
                        game_board=encounter_diamon_or_star_when_go_up(y,game_board);
                        game_board[x][y]=SPACE_SYMBOL;
                        game_board[x][0]=TURTLE_SYMBOL;
                        y=0;
                        v_x=0;
                        v_y=0;
                        return game_board;
                    }

                }
    if ((((long unsigned int)x == game_board.size() - 1 || game_board[x + side][y] == FLOOR_MAP_SYMBOLE) && status == MOVE_RIGHT) ||
        ((x == 0 || game_board[x + side][y] == FLOOR_MAP_SYMBOLE) && status == MOVE_LEFT))
    {
        return encounter_wall(game_board, side);
    }
    else
    {
        //if(game_board[x][y+1]==SPACE_SYMBOL)
        //{
        //    if(game_board[x+side][y]==FLOOR_MAP_SYMBOLE)
        //    {
        //        for(int high_counter=1;high_counter<v_y;high_counter++)
        //        {
        //            if(game_board[x][v-y+high_counter]==FLOOR_MAP_SYMBOLE)
        //                int high=high_counter;
//
        //        }
        //    }
        //}
        if (game_board[x + side][y] == FIRST_ENEMY_SYMBOL || game_board[x + side][y] == SECOND_ENEMY_SYMBOL)
        {
            return encounter_enemy(game_board, side, portal_coordinate);
        }
        else
        {
            if (game_board[x + side][y] == STAR_SYMBOL || game_board[x + side][y] == DIAMON_SYMBOL)
            {

                if (game_board[x + side][y] == STAR_SYMBOL)
                    return encounter_star_or_diamond(game_board, side, STAR_SCORE);
                return encounter_star_or_diamond(game_board, side, DIAMOND_SCORE);
            }
            else
            {
                return without_encounter(game_board, side);
            }
        }
    }
    return game_board;
}
vector<string> Turtle::move(vector<string> game_board, pair<int, int> portal_coordinate, int status)
{
    
    if(status==MOVE_RIGHT||status==MOVE_LEFT)
        return horizontal_move(game_board,portal_coordinate,status);
    else
    {
        if(status==MOVE_UP)
        {
            if(game_board[x][y+1]==SPACE_SYMBOL)
            {
                return game_board;
            }
            else
            {
                if(y<=JUMP_HIGH-1)
                {
                    if(encounter_floor_when_up(game_board)!=WITHOUT_ENCOUNTER_FLOOR)
                    {
                        game_board=encounter_diamon_or_star_when_go_up(encounter_floor_when_up(game_board),game_board);
                        game_board[x][y]=SPACE_SYMBOL;
                        game_board[x][y-encounter_floor_when_up(game_board)+1]=TURTLE_SYMBOL;
                        y=y-encounter_floor_when_up(game_board)+1;
                        v_x=0;
                        v_y=0;
                        return game_board;

                    }
                    else
                    {
                        game_board=encounter_diamon_or_star_when_go_up(y,game_board);
                        game_board[x][y]=SPACE_SYMBOL;
                        game_board[x][0]=TURTLE_SYMBOL;
                        y=0;
                        v_x=0;
                        v_y=0;
                        return game_board;
                    }

                }
                else
                {
                    if(encounter_floor_when_up(game_board))
                    {
                        game_board[x][y]=SPACE_SYMBOL;
                        game_board=encounter_diamon_or_star_when_go_up(encounter_floor_when_up(game_board),game_board);
                        game_board[x][y-encounter_floor_when_up(game_board)+1]=TURTLE_SYMBOL;
                        y=y-encounter_floor_when_up(game_board)+1;
                        v_x=0;
                        v_y=0;
                        return game_board;
                    }
                    else
                    {
                        game_board[x][y]=SPACE_SYMBOL;
                        game_board=encounter_diamon_or_star_when_go_up(JUMP_HIGH,game_board);
                        game_board[x][y-JUMP_HIGH]=TURTLE_SYMBOL;
                        y=y-JUMP_HIGH;
                        v_x=0;
                        v_y=0;
                        return game_board;   
                    }

                }
            }
        }
    }
    
}
vector<string> Turtle::encounter_wall(vector<string> game_board, int side)
{
    v_x = 0;
    return game_board;
}
vector<string> Turtle::encounter_enemy(vector<string> game_board, int side, pair<int, int> portal_coordinate)
{
    game_board[portal_coordinate.first][portal_coordinate.second] = TURTLE_SYMBOL;
    game_board[x][y] = SPACE_SYMBOL;
    v_x = 0;
    v_y = 0;
    x = portal_coordinate.first;
    y = portal_coordinate.second;
    health--;
    return game_board;
}
vector<string> Turtle::encounter_star_or_diamond(vector<string> game_board, int side, int star_or_diamond)
{
    game_board[x][y] = SPACE_SYMBOL;
    game_board[x + side][y] = TURTLE_SYMBOL;
    x = x + side;
    score += star_or_diamond;
    return game_board;
}
vector<string> Turtle::without_encounter(vector<string> game_board, int side)
{
    game_board[x][y] = SPACE_SYMBOL;
    game_board[x + side][y] = TURTLE_SYMBOL;
    x = x + side;
    return game_board;
}
Vector2f Turtle::get_position()
{
    return person_shape.getPosition();
    return Vector2f(x, y);
}
void Turtle::initialize(int &side, int status)
{
    if (status == MOVE_LEFT)
    {
        side = LEFT;
    }
    if (status == MOVE_RIGHT)
    {
        side = RIGHT;
    }
    v_x = 1;
    v_y = 0;
}
int Turtle::encounter_floor_when_up(vector<string> game_board)
{
    for(int high=1;high<JUMP_HIGH;high++)
    {
        if(game_board[x][y-high]==FLOOR_MAP_SYMBOLE&&y-high>=0)
        {
            return high;
        }
    }
    return WITHOUT_ENCOUNTER_FLOOR;
}
vector<string> Turtle::encounter_diamon_or_star_when_go_up(int high,vector<string> game_board)
{
    for(int high_counter=1;high_counter<=high;high_counter++)
    {
        if(game_board[x][y-high_counter]==STAR_SYMBOL)
        {
            game_board[x][y-high_counter]==SPACE_SYMBOL;
            score+=STAR_SCORE;
            return game_board;
        }
        if(game_board[x][y-high_counter]==STAR_SYMBOL)
        {
            game_board[x][y-high_counter]==SPACE_SYMBOL;
            score+=DIAMOND_SCORE;
            return game_board;
        }
    }
}


