#pragma once
#include "define.hpp"

class Score
{
private:
    Texture symbole;
    Sprite m_sprite;
    int value;

public:
    Score(/* args */);
    void set_texture(string address, float scale);
    Sprite get_sprite();
    ~Score();
};
