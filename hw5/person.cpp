#include "person.hpp"

Person::Person(int health_, Vector2f position_, Vector2f speed_, float jump_high_, string image_addr=ADDR_PLAYER)
{
    health = health_;
    speed = speed_;
    jump_high = jump_high_;

    t_person_shape.loadFromFile(ADDR_PLAYER);
    person_shape.setTexture(t_person_shape);
    person_shape.setScale(PLAYER_SCALE, PLAYER_SCALE);
    // TODO should read from file
    // person_shape.setPosition(1900, 500);
    person_shape.setPosition(position_);
}

Sprite Person::get_shape()
{
    return person_shape;
}
