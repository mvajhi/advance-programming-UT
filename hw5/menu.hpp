#pragma once
#include "define.hpp"
#include "window.hpp"
#include "button.hpp"

class Menu
{
private:
    Button start_button;
    Button exit_button;
    bool is_active;

public:
    Menu(/* args */);
    void update_menu(window &the_window);
    void handel_menu_event(Event event);
    bool is_in_menu();
    void show();
    ~Menu();
};
