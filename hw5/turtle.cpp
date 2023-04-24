#include "person.hpp"
#include "turtle.hpp"
#include <vector>
#include <utility>
#include <string>
Turtle::Turtle(int x_,int y_,int v_x_,int v_y_,int jump_high_,int health_,int score_)
    :Person(health_,x_,y_,jump_high_,v_x_,v_y_)
{
    score=score_;
}
vector<string> Turtle::horizontal_move(vector<string> game_board,pair<int ,int> portal_coordinate,int status)
{
    int side;
    initialize(side,status);
    if((((long unsigned int)x==game_board.size()-1||game_board[x+side][y]==FLOOR_MAP_SYMBOLE)&&status==MOVE_RIGHT)||
    ((x==0||game_board[x+side][y]==FLOOR_MAP_SYMBOLE)&&status==MOVE_LEFT))
    {
        return encounter_wall(game_board,side);
    }
    else
    {
        if(game_board[x+side][y]==FIRST_ENEMY_SYMBOL||game_board[x+side][y]==SECOND_ENEMY_SYMBOL)
        {
            return encounter_enemy(game_board,side,portal_coordinate);
        }
        else
        {
            if(game_board[x+side][y]==STAR_SYMBOL||game_board[x+side][y]==DIAMON_SYMBOL)
            {
                
                if(game_board[x+side][y]==STAR_SYMBOL)
                    return encounter_star_or_diamond(game_board,side,STAR_SCORE);
                return encounter_star_or_diamond(game_board,side,DIAMOND_SCORE);
            }
            else
            {
                return without_encounter(game_board,side);
            }
        }
    }
    return game_board;    
}
vector<string> Turtle::move(vector<string> game_board,pair<int ,int> portal_coordinate,int status)
{
    
    
        return horizontal_move(game_board,portal_coordinate,status);
    
}
vector<string> Turtle::encounter_wall(vector<string> game_board,int side)
{
    v_x=0;
    return game_board;
}
vector<string> Turtle::encounter_enemy(vector<string> game_board,int side,pair<int ,int> portal_coordinate)
{
    game_board[portal_coordinate.first][portal_coordinate.second]=TURTLE_SYMBOL;
    game_board[x][y]=SPACE_SYMBOL;
    v_x=0;
    v_y=0;
    x=portal_coordinate.first;
    y=portal_coordinate.second;
    health--;
    return game_board;
}
vector<string> Turtle::encounter_star_or_diamond(vector<string> game_board,int side,int star_or_diamond)
{
    game_board[x][y]=SPACE_SYMBOL;
    game_board[x+side][y]=TURTLE_SYMBOL;
    x=x+side;
    score+=star_or_diamond;
    return game_board;
}
vector<string> Turtle::without_encounter(vector<string> game_board,int side)
{
    game_board[x][y]=SPACE_SYMBOL;
    game_board[x+side][y]=TURTLE_SYMBOL;
    x=x+side;
    return game_board;   
}
void Turtle::initialize(int &side,int status)
{
    if(status==MOVE_LEFT)
    {
        side=LEFT;
    }
    if(status==MOVE_RIGHT)
    {
        side=RIGHT;
    }
    v_x=1;
    v_y=0;
}


