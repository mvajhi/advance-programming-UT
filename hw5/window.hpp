#pragma once
#include "define.hpp"

class Window
{
private:
        RenderWindow m_window;

        void draw_a_shape(Sprite shape);
        void draw(vector<Sprite> shapes);
        void set_view(vector<Sprite> &shapes, Vector2f position);

public:
        Window(/* args */);
        void update(vector<Sprite> updated_shapes, Vector2f position);
        ~Window();
};
