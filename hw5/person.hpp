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
    Person(int health_, Vector2f position_, Vector2f speed_, float jump_high_, string image_addr=ADDR_PLAYER);
    void move(int order);
    void restart_clock(){elapsed_time = start_clock.restart()};
    Time get_elapsed(){return elapsed_time;}

    
    Sprite get_shape();

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
};