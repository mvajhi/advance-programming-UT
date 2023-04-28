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
void Person::move(int order)
{
    // float elapsed_time;
    // auto start = std::chrono::system_clock::now();
    if (order == MOVE_RIGHT)
    {
        // auto end = std::chrono::system_clock::now();
        // std::chrono::duration<double> elapsed_seconds = end-start;
        //
        // elapsed_time=elapsed_seconds.count();
        // cout << elapsed_time;

        t_person_shape.loadFromFile(ADDR_PLAYER_FLIP);
        person_shape.setTexture(t_person_shape);
        person_shape.setScale(PLAYER_SCALE, PLAYER_SCALE);

        person_shape.setPosition(person_shape.getPosition().x + speed.x, person_shape.getPosition().y);
    }
    if (order == MOVE_LEFT)
    {
        t_person_shape.loadFromFile(ADDR_PLAYER);
        person_shape.setTexture(t_person_shape);
        person_shape.setScale(PLAYER_SCALE, PLAYER_SCALE);

        person_shape.setPosition(person_shape.getPosition().x - speed.x, person_shape.getPosition().y);
    }
}

void Person::set_pos(Vector2i pos)
{
    person_shape.setPosition((Vector2f)pos);
}