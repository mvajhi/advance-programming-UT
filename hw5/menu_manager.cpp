#include "menu_manager.hpp"
#include "game.hpp"

Menu_manager::Menu_manager(Game *the_game, RenderWindow &the_window)
    : window(the_window)
{
    game = the_game;

    font.loadFromFile(ADDR_FONT);
    backgroundTexture.loadFromFile(BACKGROUND_IMG);
    available_page = START_MENU;

    first = true;
    reset = false;
    create();
}

Menu_manager::~Menu_manager()
{
    delete (start_menu);
    delete (level_menu);
}

void Menu_manager::show_menu(int page = DEFAULT_PAGE, int score_)
{
    score = score_;
    available_page = page;

    window.setView(View(Vector2f(WINDOW_W / 2, WINDOW_H / 2),
                        Vector2f(WINDOW_W, WINDOW_H)));

    create();

    while (window.isOpen())
    {
        if (available_page == SHOW_GAME)
            break;

        Menu *page = find_avail_page();

        handel_events(page);

        window.clear();

        page->draw();

        window.display();
    }
}

Menu *Menu_manager::find_avail_page()
{
    switch (available_page)
    {
    case START_MENU:
        return start_menu;
        break;
    case LEVEL_MENU:
        return level_menu;
        break;
    case PAUSE_MENU:
        return pause_menu;
        break;
    case WIN_MENU:
        return win_menu;
        break;

    default:
        break;
    }
    return nullptr;
}

void Menu_manager::handel_events(Menu *page)
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
        }
        else if (event.type == Event::MouseButtonPressed && page == win_menu)
        {
            available_page = LEVEL_MENU;
        }
        else
        {
            page->handle_event(event);
        }
    }
}

void Menu_manager::initialize_level_menu()
{

    string &path = level_path;

    int &avail_menu = available_page;
    level_menu->add_button("level 1", [&path, &avail_menu]()
                           { cout << "level 1" << endl;
                            path = MAP_L1;
                           avail_menu = SHOW_GAME; });

    level_menu->add_button("level 2", [&path, &avail_menu]()
                           { cout << "level 2" << endl;
                            path = MAP_L2;
                           avail_menu = SHOW_GAME; });

    level_menu->add_button("return", [&avail_menu]()
                           { avail_menu = START_MENU; });
}

void Menu_manager::initialize_start_menu()
{
    int &avail_menu = available_page;
    start_menu->add_button("Start", [&avail_menu]()
                           { avail_menu = LEVEL_MENU; });

    auto &the_window = window;
    start_menu->add_button("Exit", [&the_window]()
                           { the_window.close(); });
}

void Menu_manager::initialize_pause_menu()
{
    int &avail_menu = available_page;
    bool &the_reset = reset;
    pause_menu->add_button("Continue", [&the_reset, &avail_menu]()
                           { cout << "Continue" << endl;
                            the_reset = false;
                            avail_menu = SHOW_GAME; });
    // TODO reset level
    pause_menu->add_button("return", [&the_reset, &avail_menu]()
                           { cout << "back" << endl;
                           the_reset = true;
                           avail_menu = LEVEL_MENU; });
}

void Menu_manager::initialize_win_menu()
{
    int &avail_menu = available_page;
    win_menu->add_button("score: " + to_string(score), [&avail_menu]()
                         { avail_menu = LEVEL_MENU; });
}

void Menu_manager::create()
{
    if (!first)
    {
        delete (start_menu);
        delete (level_menu);
        delete (pause_menu);
        delete (win_menu);
    }

    start_menu = new Menu(window, font, MENU_POS, backgroundTexture);
    level_menu = new Menu(window, font, MENU_POS, backgroundTexture);
    pause_menu = new Menu(window, font, MENU_POS, backgroundTexture);
    win_menu = new Menu(window, font, MENU_POS, backgroundTexture);

    initialize_level_menu();
    initialize_start_menu();
    initialize_pause_menu();
    initialize_win_menu();

    first = false;
}
