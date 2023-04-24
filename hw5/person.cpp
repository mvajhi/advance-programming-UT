#include "person.hpp"

Person::Person(int health_, int x_, int y_, int jump_high_, int v_x_, int v_y_)
{
    v_x = v_x_;
    v_y = v_y_;
    x = x_;
    y = y_;
    jump_high = jump_high_;
    health = health_;
}
