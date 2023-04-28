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
void Turtle::move(Collision_report colisions)
{
    if(person_shape.getPosition().y < 500)
    {
        speed.y-=GRAVITY;
        move_value.y = speed.y;
    }
    else if (person_shape.getPosition().y > 500)
    {
        speed.y = 0;
    }
    else
    {
        move_value.y = speed.y;
    }
    // else
    // {
    //     if(colisions.floor==up&&events.up==true)
    //     {
    //         if()
    //     }
    // }
}
Events Turtle::get_events(){return events;}
void Turtle::set_events(Events events_){events=events_;}

void Turtle::handel_input(int order)
{
    if(order==MOVE_UP && person_shape.getPosition().y == 500)
    {
        speed.y = 1000;
    }  
    
}

// void Person::move(int order)
// {
//     if (order == MOVE_RIGHT)
//     {

//         t_person_shape.loadFromFile(ADDR_PLAYER_FLIP);
//         person_shape.setTexture(t_person_shape);
//         person_shape.setScale(PLAYER_SCALE, PLAYER_SCALE);

//         person_shape.setPosition(person_shape.getPosition().x + speed.x, person_shape.getPosition().y);
//     }
//     if (order == MOVE_LEFT)
//     {
//         t_person_shape.loadFromFile(ADDR_PLAYER);
//         person_shape.setTexture(t_person_shape);
//         person_shape.setScale(PLAYER_SCALE, PLAYER_SCALE);

//         person_shape.setPosition(person_shape.getPosition().x - speed.x, person_shape.getPosition().y);
//     }
// }
