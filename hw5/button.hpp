#pragma once

#include "define.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

class Button
{
public:
    Button(RectangleShape shape, Text text, function<void()> on_click, Color button_color);

    vector<Drawable *> get_drawable();
    bool contains(float x, float y);
    void mouse_inside();
    void mouse_outside();
    void click();

private:
    RectangleShape shape;
    Text text;
    function<void()> on_click;
    Color button_color;
    Color hover_color;
};