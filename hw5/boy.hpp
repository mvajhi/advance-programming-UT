#pragma once

#include "define.hpp"

class Boy
{
private:
    Sprite sprite;
    Texture texture;

    bool is_free;
    bool is_go_left;
    Vector2f spawn_point;

    // initilaize
    void initilaize_sprite(string texture_file_addr);
    void initilaize_anime();
    void initilaize_move();

    // anime
    IntRect move_frame;
    Clock animation_clock;
    IntRect IDL_frame;
    int anime_state;
    int last_anime_state;
    bool have_move;

    void update_animation();
    void update_left_animation();
    void update_right_animation();
    void update_IDL_animation();
    void update_anime_state();

    // move
    Vector2f pre_position;
    Vector2f velocity;
    float velocity_min;
    float velocity_max;
    float acceleration;
    float drag;
    float gravity;

    void update_move();
    void move(Vector2f dir);

public:
    Boy(string texture_file_addr);
    void update();
    void set_spawn(float x, float y);

    // outputs
    Sprite get_sprite();
    Vector2f get_position();

    // move
    void move_handel();

    // collision
    FloatRect get_global_bound();
    void reset_velocity_y();
    void reset_velocity_x();
    void set_position(float x, float y);
    void move(float x, float y);
    void save_pre_position();
    Vector2f get_pre_position();
    Vector2f get_velocity();

    void set_free();
    void go_left();
    void go_right();
};