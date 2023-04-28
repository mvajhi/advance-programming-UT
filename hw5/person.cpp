#include "person.hpp"
#include <chrono>
#include <ctime>

// auto end = std::chrono::system_clock::now();

Sprite Person::get_shape()
{
    return person_shape;
}
Person::Person(int health_, Vector2f position_, float jump_high_, Vector2f speed_, string image_addr)
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
void Person::update()
{
    if (move_value.x != 0 || move_value.y != 0)
        cout << move_value.x << "\n" << move_value.y << "\n\n";
    // cout <<person_shape.getPosition().x + move_value.x << "\n" << person_shape.getPosition().y + move_value.y << "\n\n\n";
    person_shape.setPosition(person_shape.getPosition().x + move_value.x, person_shape.getPosition().y - move_value.y);
    move_value = Vector2f(0, 0);
}

void Person::set_pos(Vector2i pos)
{
    person_shape.setPosition((Vector2f)pos);
}