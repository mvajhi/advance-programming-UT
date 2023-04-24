#pragma once
#include <string>
#include <vector>
#include <utility>
#include "define.hpp"

class Person
{

public:
    Person(int health_, int x_, int y_, int jump_high_ = JUMP_HIGH, int v_x_ = 0, int v_y_ = 0);
    virtual vector<string> move(vector<string> game_board, pair<int, int> portal_coordinate, int status) = 0;

protected:
    int v_x;
    int v_y;
    int x;
    int y;
    int jump_high;
    int health;
};