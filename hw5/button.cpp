#include "button.hpp"

Button::Button(string text_content, Vector2f position) : button(Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT)), text(text_content, font, MENU_FONT_SIZE)
{
    button.setOrigin(button.getPosition().x + button.getSize().x / 2.0f, button.getPosition().y + button.getSize().y / 2.0f);
    button.setFillColor(BUTTON_COLOR);
    button.setPosition(position);

    font.loadFromFile(ADDR_FONT);
    text.setFillColor(BUTTON_TEXT_COLOR);
    FloatRect text_rect = text.getLocalBounds();
    text.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
    text.setPosition(button.getPosition().x, button.getPosition().y);
}

void Button::set_position(Vector2f position)
{
    button.setPosition(position);
    text.setPosition(button.getPosition().x, button.getPosition().y);
}

Vector2f Button::get_position()
{
    return button.getPosition();
}

vector<Drawable *> Button::get_shape()
{
    vector<Drawable *> buffer;
    buffer.push_back(&button);
    buffer.push_back(&text);
    return buffer;
}

bool Button::is_into(Vector2f position)
{
    return button.getGlobalBounds().contains(position.x, position.y);
}

Button::~Button()
{
}
