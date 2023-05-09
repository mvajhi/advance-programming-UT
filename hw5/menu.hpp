#pragma once

#include "define.hpp"
#include "button.hpp"
#include <functional>

class Menu
{
public:
    Menu(RenderWindow &window, Font &font, Vector2f position, Texture &backgroundTexture);

    void add_button(string text, function<void()> on_click, Color button_color = BUTTON_COLOR, int characterSize = MENU_FONT_SIZE);
    void draw();
    void handle_event(Event &event);

private:
    RenderWindow &m_window;
    Font &m_font;
    Vector2f &m_position;
    Color m_button_color;
    unsigned int m_character_size;
    vector<Button> m_buttons;
    int m_hovered_button_index = NO_INDEX;
    Sprite m_background;

    void handle_mouse_moved(int x, int y);
    void handle_mouse_button_pressed(int x, int y);
};