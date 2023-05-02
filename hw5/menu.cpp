#include "menu.hpp"

Menu::Menu(/* args */) : start_button("Start!!", Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + BUTTON_HEIGHT)),
                         exit_button("exit", Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 4 * BUTTON_HEIGHT))
{
    is_active = true;
}

Menu::~Menu()
{
}

void Menu::update_menu(window &the_window)
{
    vector<Drawable *> buffer;
    vector<Drawable *> start_button_shape = start_button.get_shape();
    vector<Drawable *> exit_button_shape = exit_button.get_shape();
    buffer.insert(buffer.end(), start_button_shape.begin(), start_button_shape.end());
    buffer.insert(buffer.end(), exit_button_shape.begin(), exit_button_shape.end());
    the_window.update(buffer);
}

void Menu::handel_menu_event(Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
        if (start_button.is_into(Vector2f(event.mouseButton.x, event.mouseButton.y)))
            is_active = false;
        else if (exit_button.is_into(Vector2f(event.mouseButton.x, event.mouseButton.y)))
            exit(0);
}

bool Menu::is_in_menu()
{
    return is_active;
}
