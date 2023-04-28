#pragma once
#include "define.hpp"

class Game_manager;

class window
{
private:
        RenderWindow m_window;
        Game_manager *manager;

        void draw_a_shape(Sprite shape);
        void draw(vector<Sprite> shapes);
        void set_view(vector<Sprite> &shapes, Vector2f position);

public:
        window(Game_manager *manager_pointer);
        void update(vector<Sprite> updated_shapes, Vector2f position);
        void update(vector<Drawable *> updated_shapes);
        void get_events();
        void close();
        RenderWindow *get_window();
        ~window();
};
