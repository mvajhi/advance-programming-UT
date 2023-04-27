#include "person.hpp"

Person::Person(int health_, int x_, int y_, int jump_high_, int v_x_, int v_y_)
{
    // v_point = (v_x_, v_y_);
    // position = (x_, y_);
    v_x = v_x_;
    v_y = v_y_;
    x = x_;
    y = y_;
    jump_high = jump_high_;
    health = health_;

    t_person_shape.loadFromFile(ADDR_PLAYER);
    person_shape.setTexture(t_person_shape);
    person_shape.setScale(PLAYER_SCALE, PLAYER_SCALE);
    person_shape.setPosition(1900, 500);
}

Sprite Person::get_shape()
{
    return person_shape;
}
