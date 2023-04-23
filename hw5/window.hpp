#pragma once
#include "define.hpp"

class window
{
private:
        RenderWindow m_window;

        void draw_a_shape(Drawable *shape);
        void draw(vector<Drawable*> shapes);
public:
        window(/* args */);
        void update(vector<Drawable*> updated_shapes);
        ~window();
};

