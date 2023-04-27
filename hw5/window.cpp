#include "window.hpp"
#include "game_manager.hpp"
#include "define.hpp"

window::window(Game_manager *manager_pointer)
{
        manager = manager_pointer;
        m_window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "game");
}

void window::draw(vector<Sprite> shapes)
{
        for (auto shape : shapes)
                draw_a_shape(shape);
}

void window::set_view(vector<Sprite> &shapes, Vector2f position)
{
        Vector2f move_size = Vector2f(WINDOW_WIDTH * VIEW_RATIO_WIDTH,
                                      WINDOW_HEIGHT * VIEW_RATIO_HEIGHT) -
                             position;
        for (size_t i = 0; i < shapes.size(); i++)
        {
                Vector2f shpae_pos = shapes[i].getPosition();
                shapes[i].setPosition(shpae_pos + move_size);
        }
}

void window::update(vector<Sprite> updated_shapes, Vector2f position)
{
        set_view(updated_shapes, position);
        m_window.clear(Color(BACKGROUND_COLOR));
        draw(updated_shapes);
        m_window.display();
}

void window::get_events()
{
        Event event;
        while (m_window.pollEvent(event))
                manager->handel_event(event);
}

void window::close()
{
        m_window.close();
        // TODO REMOVE THIS
        exit(0);
}

void window::draw_a_shape(Sprite shape)
{
        m_window.draw(shape);
}

window::~window()
{
}
