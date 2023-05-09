#include "person.hpp"
#include "define.hpp"
#include <chrono>
#include <ctime>

// auto end = std::chrono::system_clock::now();

Sprite Person::get_shape()
{
    fall();
    return person_shape;
}
void Person::set_report(bool new_report[])
{
    for (int i = 0; i < 4; i++)
        report_floor[i] = new_report[i];
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
    if (order == MOVE_RIGHT && report_floor[RIGHT] == false)
    {
        t_person_shape.loadFromFile(ADDR_PLAYER_FLIP);
        person_shape.setTexture(t_person_shape);
        person_shape.setScale(PLAYER_SCALE, PLAYER_SCALE);

        person_shape.setPosition(person_shape.getPosition().x + speed.x, person_shape.getPosition().y);
    }
    if (order == MOVE_LEFT && report_floor[LEFT] == false)
    {
        t_person_shape.loadFromFile(ADDR_PLAYER);
        person_shape.setTexture(t_person_shape);
        person_shape.setScale(PLAYER_SCALE, PLAYER_SCALE);

        person_shape.setPosition(person_shape.getPosition().x - speed.x, person_shape.getPosition().y);
    }
    if(order==MOVE_UP)
    {
        speed.y+=300;
        person_shape.setPosition(person_shape.getPosition().x,person_shape.getPosition().y-speed.y);
    }
}

void Person::set_pos(Vector2i pos)
{
    person_shape.setPosition((Vector2f)pos);
}
void Person::fall()
{
    if (!report_floor[DOWN])
    {
        speed.y+=GRAVITY;
        set_pos({person_shape.getPosition().x, person_shape.getPosition().y +speed.y });
    }

    else
    {
        speed.y = 0;
        // set_pos({person_shape.getPosition().x, 800});
    }
}
void Person::jump()
{
    if(report_floor[DOWN]) 
    {
        speed.y=100;

    }
    else
    {
        fall();
    }
}