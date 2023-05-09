#include "menu.hpp"

Menu::Menu(RenderWindow &window, Font &font, Vector2f position, Texture &backgroundTexture)
    : m_window(window), m_font(font), m_position(position), m_button_color(BUTTON_COLOR), m_character_size(32), m_background(backgroundTexture)
{
}

void Menu::add_button(string text, function<void()> on_click, Color button_color, int characterSize)
{
    Vector2f buttonSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    Vector2f buttonPosition(FIRST_BUTTON_POSITION +
                            Vector2f(0, m_buttons.size() * buttonSize.y) +
                            Vector2f(m_buttons.size() * BUTTON_SEPRATE.x,
                                     m_buttons.size() * BUTTON_SEPRATE.y));
    RectangleShape buttonShape(buttonSize);
    buttonShape.setPosition(buttonPosition);
    buttonShape.setFillColor(button_color);

    Text buttonText(text, m_font, characterSize);
    buttonText.setPosition(buttonPosition + 0.5f * buttonSize - 0.5f * Vector2f(buttonText.getLocalBounds().width, buttonText.getLocalBounds().height));
    buttonText.setFillColor(BUTTON_TEXT_COLOR);

    m_buttons.push_back(Button(buttonShape, buttonText, on_click, button_color));
}

void Menu::draw()
{
    m_window.draw(m_background);
    for (auto button : m_buttons)
    {
        vector<Drawable *> output = button.get_drawable();
        for (Drawable *i : output)
            m_window.draw(*i);
    }
}

void Menu::handle_event(Event &event)
{
    if (event.type == Event::MouseMoved)
        handle_mouse_moved(event.mouseMove.x, event.mouseMove.y);
    else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        handle_mouse_button_pressed(event.mouseButton.x, event.mouseButton.y);
}

void Menu::handle_mouse_moved(int x, int y)
{
    int hovered_button_index = NO_INDEX;
    for (size_t i = 0; i < m_buttons.size(); ++i)
        if (m_buttons[i].contains(x, y))
        {
            hovered_button_index = (int)i;
            break;
        }

    if (hovered_button_index != m_hovered_button_index)
    {
        if (m_hovered_button_index != NO_INDEX)
            m_buttons[m_hovered_button_index].mouse_outside();

        if (hovered_button_index != NO_INDEX)
            m_buttons[hovered_button_index].mouse_inside();

        m_hovered_button_index = hovered_button_index;
    }
}

void Menu::handle_mouse_button_pressed(int x, int y)
{
    if (m_hovered_button_index != NO_INDEX)
        m_buttons[m_hovered_button_index].click();
}