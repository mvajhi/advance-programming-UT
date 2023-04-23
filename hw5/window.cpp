#include "window.hpp"


window::window(/* args */)
{
        m_window.create(VideoMode(900, 600), "game");
}

void window::draw(vector<Drawable *> shapes)
{
        for(auto shape : shapes)
                draw_a_shape(shape);
}

void window::update(vector<Drawable *> updated_shapes)
{
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
