#include "person.hpp"
#include "turtle.hpp"
#include <vector>
#include <utility>
#include <string>
Turtle::Turtle(int health_, Vector2f position_, float jump_high_, int score_=0, Vector2f speed_={100.0,0.0}, string image_addr=ADDR_PLAYER)
    : Person(health_,position_, jump_high_, speed_, image_addr)
{
    score = score_;
}
void Turtle::update(Collision_report colisions)
{
    if(colisions.floor==without_collision)
    {
        speed.y-=GRAVITY;
        if(speed.y<0)
        {
            while(true)
            {
                
            }
        }
        move(MOVE_UP);

    }
    else
    {
        if(colisions.floor==up&&events.up==true)
        {
            if()
        }
    }
}
Events Turtle::get_events(){return events;}
void Turtle::set_events(Events events_){events=events_;}

