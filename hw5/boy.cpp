#include "boy.hpp"
#include <cmath>

void Boy::update_move()
{
    velocity.x = velocity.x * drag;

    if (abs(velocity.x) < velocity_min)
        velocity.x = 0;

    velocity.y += gravity;

    sprite.move(velocity);
}

void Boy::move(Vector2f dir)
{
    if (dir.x != 0)
        velocity.x = dir.x * acceleration;

    if (dir.y != 0)
        velocity.y = dir.y * acceleration;

    if (abs(velocity.x) > velocity_max || (abs(velocity.y) > 0 && dir.x != 0))
        velocity.x = velocity_max * (signbit(velocity.x) ? -1 : 1);

    if (velocity.y > velocity_max)
        velocity.y = velocity_max * (signbit(velocity.y) ? -1 : 1);
}

Boy::Boy(string texture_file_addr)
{
    initilaize_sprite(texture_file_addr);
    initilaize_anime();
    initilaize_move();
}

void Boy::move_handel()
{
    // TODO
    if (is_go_left)
    {
        move(Vector2f(-1, 0));
        anime_state = LEFT;
    }
    else
    {
        move(Vector2f(1, 0));
        anime_state = RIGHT;
    }

    have_move = true;
}

void Boy::update()
{
    if (is_free)
        move_handel();

    update_animation();

    update_move();
}

void Boy::initilaize_sprite(string texture_file_addr)
{
    texture.loadFromFile(texture_file_addr);
    sprite.setTexture(texture);
    sprite.setTextureRect(move_frame);
    sprite.setScale(BOY_SCALE_X, BOY_SCALE_Y);
}

void Boy::initilaize_anime()
{
    is_free = false;
    IDL_frame = IntRect(0, 0, IMG_BOY_SIZE_W, IMG_BOY_SIZE_H);
    move_frame = IntRect(0, 0, IMG_BOY_SIZE_W, IMG_BOY_SIZE_H);
    animation_clock.restart();
    anime_state = IDL;
}

void Boy::initilaize_move()
{
    is_go_left = true;
    velocity = Vector2f(0, 0);
    velocity_max = DEFAULT_VELOCITY_MAX;
    velocity_min = DEFAULT_VELOCITY_MIN;
    acceleration = DEFAULT_ACCELERATION;
    drag = DEFAULT_DRAG;
    gravity = DEFAULT_GRAVITY;
}

void Boy::update_animation()
{
    if (anime_state == IDL)
        update_IDL_animation();

    else if (anime_state == LEFT)
        update_left_animation();

    else if (anime_state == RIGHT)
        update_right_animation();

    update_anime_state();
}

void Boy::update_left_animation()
{
    if (animation_clock.getElapsedTime().asSeconds() >= ANIME_PLAYER_SPEED)
    {
        move_frame.left += IMG_BOY_SIZE_W;
        if (move_frame.left >= IMG_BOY_SIZE_W * 6)
        {
            move_frame.left = 0;
            move_frame.top += IMG_BOY_SIZE_H;
        }
        if (move_frame.top == IMG_BOY_SIZE_H * 2 &&
            move_frame.left >= IMG_BOY_SIZE_W * 3)
        {
            move_frame.left = 0;
            move_frame.top = 0;
        }

        animation_clock.restart();
    }
}

void Boy::update_right_animation()
{
    if (animation_clock.getElapsedTime().asSeconds() >= ANIME_PLAYER_SPEED)
    {
        move_frame.left += IMG_BOY_SIZE_W;
        if (move_frame.left >= IMG_BOY_SIZE_W * 6)
        {
            move_frame.left = 0;
            move_frame.top += IMG_BOY_SIZE_H;
        }
        if (move_frame.top < IMG_BOY_SIZE_H * 3 ||
            (move_frame.top == IMG_BOY_SIZE_H * 5 &&
             move_frame.left == IMG_BOY_SIZE_W * 4))
        {
            move_frame.left = 0;
            move_frame.top = IMG_BOY_SIZE_H * 3;
        }

        animation_clock.restart();
    }
}

void Boy::update_IDL_animation()
{
    if (!is_free)
        move_frame = IntRect(IMG_BOY_SIZE_W * 4, IMG_BOY_SIZE_H * 2,
                             IMG_BOY_SIZE_W, IMG_BOY_SIZE_H);
}

void Boy::update_anime_state()
{
    sprite.setTextureRect(move_frame);

    last_anime_state = anime_state;

    if (have_move)
        have_move = false;
    else
        anime_state = IDL;
}

Sprite Boy::get_sprite()
{
    return sprite;
}

Vector2f Boy::get_position()
{
    return sprite.getPosition();
}

void Boy::set_spawn(float x, float y)
{
    // 5 for avoid sticking to the ground and distance from the ground
    sprite.setPosition(x, y - 5);
    spawn_point = Vector2f(x, y - 5);
}

void Boy::save_pre_position()
{
    pre_position = sprite.getPosition();
}

Vector2f Boy::get_pre_position()
{
    return pre_position;
}

Vector2f Boy::get_velocity()
{
    return velocity;
}

void Boy::set_free()
{
    is_free = true;
}

void Boy::go_left()
{
        move_frame = IntRect(0, 0, IMG_BOY_SIZE_W, IMG_BOY_SIZE_H);
    is_go_left = true;
}

void Boy::go_right()
{
        move_frame = IntRect(0, 0, IMG_BOY_SIZE_W, IMG_BOY_SIZE_H);
    is_go_left = false;
}

FloatRect Boy::get_global_bound()
{
    return sprite.getGlobalBounds();
}

void Boy::reset_velocity_y()
{
    velocity.y = 0;
}

void Boy::reset_velocity_x()
{
    velocity.x = 0;
}

void Boy::set_position(float x, float y)
{
    sprite.setPosition(x, y);
}

void Boy::move(float x, float y)
{
    sprite.move(x, y);
}