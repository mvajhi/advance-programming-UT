#include "window.hpp"

Window::Window(/* args */)
{
        m_window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "game");
}

void Window::draw(vector<Sprite> shapes)
{
        for (auto shape : shapes)
                draw_a_shape(shape);
}

void Window::set_view(vector<Sprite> &shapes, Vector2f position)
{
        Vector2f move_size = - Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2) - position;
        for (size_t i = 0; i < shapes.size(); i++)
        {
                Vector2f shpae_pos = shapes[i].getPosition();
                shapes[i].setPosition(shpae_pos + move_size);
        }
}

void Window::update(vector<Sprite> updated_shapes, Vector2f position)
{
        set_view(updated_shapes, position);
        m_window.clear(Color(BACKGROUND_COLOR));
        draw(updated_shapes);
        m_window.display();
}

void Window::draw_a_shape(Sprite shape)
{
        m_window.draw(shape);
}

Window::~Window()
{
}
