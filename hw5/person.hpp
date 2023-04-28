#pragma once
#include <string>
#include <vector>
#include <utility>
#include "define.hpp"

class Person
{

public:
    // TODO @mohammadamintavanai fix name x_, y_ ,...
    // TODO @mohammadamintavanai some variable should change to float like speed
    Person(int health_, Vector2f position_, float jump_high_, Vector2f speed_, string image_addr);
    void move(int order);
    void set_pos(Vector2i pos);
    Sprite get_shape();
    Vector2f get_position(){return person_shape.getPosition();}
protected:
    // @mohammadamintavanai change xy with vector2f
    // TODO @mohammadamintavanai fix names
    Texture t_person_shape;
    Sprite person_shape;
    sf::Clock start_clock;
    sf::Time elapsed_time;
    Vector2f speed;
    float jump_high;
    int health;
    sf::Clock m_clock;
	float m_elapsed;
};