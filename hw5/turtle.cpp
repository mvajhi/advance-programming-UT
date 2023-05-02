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

Vector2f Turtle::get_move_size()
{
    return speed;
}
