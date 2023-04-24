#include "window.hpp"

window::window(/* args */)
{
        m_window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "game");
}

void window::draw(vector<Drawable *> shapes)
{
        for (auto shape : shapes)
                draw_a_shape(shape);
}

void window::set_view(vector<Drawable *> shapes, Vector2f position)
{
        //TODO change pos
}

//!!WANING should send copy of shape
void window::update(vector<Drawable *> updated_shapes, Vector2f position)
{
        // TODO should return board with position
        set_view(updated_shapes, position);
        m_window.clear();
        draw(updated_shapes);
        m_window.display();
}

void window::draw_a_shape(Drawable *shape)
{
        m_window.draw(*shape);
}

window::~window()
{
}
