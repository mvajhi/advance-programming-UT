#include "button.hpp"

Button::Button(RectangleShape shape, Text text, function<void()> on_click, Color button_color)
    : shape(shape), text(text), on_click(on_click), button_color(button_color), hover_color(BUTTON_HOVER_COLOR)
{
}

vector<Drawable *> Button::get_drawable()
{
    vector<Drawable *> output;
    output.push_back(&shape);
    output.push_back(&text);
    return output;
}

bool Button::contains(float x, float y)
{
    return shape.getGlobalBounds().contains(x, y);
}

void Button::mouse_inside()
{
    shape.setFillColor(hover_color);
}

void Button::mouse_outside()
{
    shape.setFillColor(button_color);
}

void Button::click()
{
    on_click();
}
