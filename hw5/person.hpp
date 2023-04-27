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
    Person(int health_, int x_, int y_, int jump_high_ = JUMP_HIGH, int v_x_ = 0, int v_y_ = 0);
    virtual vector<string> move(vector<string> game_board, pair<int, int> portal_coordinate, int status) = 0;
    Sprite get_shape();

protected:
    // @mohammadamintavanai change xy with vector2f
    // TODO @mohammadamintavanai fix names
    // Vector2f v_point;
    // Vector2f position;
    Texture t_person_shape;
    Sprite person_shape;
    int v_x;
    int v_y;
    int x;
    int y;
    int jump_high;
    int health;
};