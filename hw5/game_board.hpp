#pragma once
#include "define.hpp"
#include "boy.hpp"

class Game_board
{
private:
        //floors
        vector<string> text_map;
        Texture t_floor;
        Texture t_portal;
        Sprite floor;
        Sprite portal;
        vector<Sprite> floors;

        //scores
        Texture t_diamond;
        Sprite diamond;
        vector<Sprite> diamonds;
        Texture t_star;
        Sprite star;
        vector<Sprite> stars;

        //boys
        Boy boy_turtle;
        vector<Boy> boys;
        void update_boy_move();

        //collision
        void update_collision();
        void collision_boys_and_portal();

public:
        Game_board();

        void pre_update();
        void update();

        //initialize
        void initialize_floor();
        void initialize_diamond();
        void initialize_star();
        void initialize_portal();
        void initialize_boy();
        void add_new_floor(Vector2f position);
        void add_new_diamond(Vector2f position);
        void add_new_star(Vector2f position);
        void add_new_boy_turtle(Vector2f possition);
        void set_portal(Vector2f position);
        void reset_map();

        //outputs
        vector<FloatRect> get_floors_bound();
        vector<FloatRect> get_stars_bound();
        vector<FloatRect> get_diamonds_bound();
        vector<FloatRect> get_boys_bound();
        vector<Sprite> get_board();
        vector<Boy> &get_boys();

        // scores
        void remove_diamond(int pos);
        void remove_star(int pos);
        void free_boy(int pos);
        bool is_all_boy_in_portal();

};
