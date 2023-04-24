#pragma once
#include "define.hpp"

class window
{
private:
        RenderWindow m_window;

        void draw_a_shape(Drawable *shape);
        void draw(vector<Drawable *> shapes);
        void set_view(vector<Drawable *> shapes, Vector2f position);

public:
        window(/* args */);
        //!!WANING should send copy of shape
        void update(vector<Drawable *> updated_shapes, Vector2f position);
        ~window();
};
