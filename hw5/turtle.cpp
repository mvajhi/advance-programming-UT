#include "person.hpp"
#include "turtle.hpp"
Turtle::Turtle(int x_,int y_,int v_x_,int v_y_,int jump_high_,int health_,int score_)
    :Person(health_,x_,y_,jump_high_,v_x_,v_y_)
{
    score=score_;
}