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
    virtual vector<string> move(vector<string> game_board, pair<int, int> portal_coordinate, int status) = 0;
    Sprite get_shape();

protected:
    // @mohammadamintavanai change xy with vector2f
    // TODO @mohammadamintavanai fix names
    Texture t_person_shape;
    Sprite person_shape;
    Vector2f speed;
    float jump_high;
    int health;
};