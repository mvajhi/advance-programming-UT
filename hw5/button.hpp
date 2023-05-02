#pragma once
#include "define.hpp"

class Button
{
private:
    RectangleShape button;
    Font font;
    Text text;

public:
    Button(string text_content, Vector2f position);
    void set_position(Vector2f position);
    Vector2f get_position();
    vector<Drawable *> get_shape();
    bool is_into(Vector2f position);

    ~Button();
};
