#include "window.hpp"
#include "game.hpp"

window::window(int page_width, int page_hight, string page_name, Game *game)
    : the_window(VideoMode(page_width, page_hight), page_name, Style::Close | Style::Titlebar)
{
    the_game = game;
    the_window.setFramerateLimit(MAX_FRAME);
}

RenderWindow &window::get_window()
{
    return the_window;
}

void window::get_events()
{
    Event event;
    while (the_window.pollEvent(event))
        the_game->handel_event(event);
}

void window::close()
{
    the_window.close();
}

void window::render(vector<Drawable *> output, Vector2f camera_position)
{
    camera_position = Vector2f(camera_position.x, camera_position.y);

    the_window.clear(GAME_BACK_COLOR);

    for (auto i : output)
        the_window.draw(*i);
    the_window.setView(View(camera_position, Vector2f(WINDOW_W, WINDOW_H)));

    the_window.display();
}
