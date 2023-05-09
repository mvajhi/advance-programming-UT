#include "player.hpp"
#include <cmath>

void Player::update_move()
{
    velocity.x = velocity.x * drag;

    if (abs(velocity.x) < velocity_min)
        velocity.x = 0;

    velocity.y += gravity;

    sprite.move(velocity);
}

void Player::move(Vector2f dir)
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

void Player::add_score(int value)
{
    score += value;
}

void Player::decrese_health(int value)
{
    health -= value;
}

bool Player::is_dead()
{
    return health <= 0;
}

Player::Player(string texture_file_addr)
{
    initilaize_sprite(texture_file_addr);
    initilaize_anime();
    initilaize_move();
    initilaize_health_and_score();
}

void Player::move_handel(int direct)
{
    switch (direct)
    {
    case RIGHT:
        move(Vector2f(1, 0));
        anime_state = RIGHT;
        break;
    case LEFT:
        move(Vector2f(-1, 0));
        anime_state = LEFT;
        break;
    case UP:
        move(Vector2f(0, -6));
        anime_state = UP;
        break;

    default:
        break;
    }
    have_move = true;
}

void Player::update()
{
    update_animation();

    update_move();
}

void Player::initilaize_sprite(string texture_file_addr)
{
    texture.loadFromFile(texture_file_addr);
    sprite.setTexture(texture);
    sprite.setTextureRect(move_frame);
    sprite.setScale(PLAYER_SCALE_X, PLAYER_SCALE_Y);
}

void Player::initilaize_anime()
{
    IDL_frame = IntRect(0, IMG_PLAYER_SIZE_H * 7, IMG_PLAYER_SIZE_W, IMG_PLAYER_SIZE_H);
    move_frame = IntRect(0, IMG_PLAYER_SIZE_H * 7, IMG_PLAYER_SIZE, IMG_PLAYER_SIZE);
    animation_clock.restart();
    anime_state = IDL;
}

void Player::initilaize_move()
{
    velocity = Vector2f(0, 0);
    velocity_max = DEFAULT_VELOCITY_MAX;
    velocity_min = DEFAULT_VELOCITY_MIN;
    acceleration = DEFAULT_ACCELERATION;
    drag = DEFAULT_DRAG;
    gravity = DEFAULT_GRAVITY;
}

void Player::initilaize_health_and_score()
{
    score = DEFAULT_SCORE;
    health = DEFAULT_HELTH;
}

void Player::update_animation()
{
    if (anime_state == IDL)
        update_IDL_animation();

    else if (anime_state == LEFT)
        update_left_animation();

    else if (anime_state == RIGHT)
        update_right_animation();

    update_anime_state();
}

void Player::update_left_animation()
{
    if (animation_clock.getElapsedTime().asSeconds() >= ANIME_PLAYER_SPEED)
    {
        move_frame.left += IMG_PLAYER_SIZE_W;
        if (move_frame.left >= IMG_PLAYER_SIZE_W * 5)
        {
            move_frame.left = 0;
            move_frame.top += IMG_PLAYER_SIZE;
        }
        if (move_frame.top == IMG_PLAYER_SIZE_H * 3 &&
            move_frame.left >= IMG_PLAYER_SIZE_W * 1)
            move_frame.top = 0;

        animation_clock.restart();
    }
}

void Player::update_right_animation()
{
    if (animation_clock.getElapsedTime().asSeconds() >= ANIME_PLAYER_SPEED)
    {
        move_frame.left += IMG_PLAYER_SIZE_W;
        if (move_frame.left >= IMG_PLAYER_SIZE_W * 5)
        {
            move_frame.left = 0;
            move_frame.top += IMG_PLAYER_SIZE;
        }
        if (move_frame.top < IMG_PLAYER_SIZE_H * 4 ||
            (move_frame.top == IMG_PLAYER_SIZE_H * 7 &&
             move_frame.left == IMG_PLAYER_SIZE_W * 1))
            move_frame.top = IMG_PLAYER_SIZE_H * 4;

        animation_clock.restart();
    }
}

void Player::update_IDL_animation()
{
    if (last_anime_state == LEFT)
        move_frame = IntRect(0, PLAYER_IDL_LEFT,
                             IMG_PLAYER_SIZE_W, IMG_PLAYER_SIZE_H);
    else if (last_anime_state == RIGHT)
        move_frame = IntRect(0, PLAYER_IDL_RIGHT,
                             IMG_PLAYER_SIZE_W, IMG_PLAYER_SIZE_H);
}

void Player::update_anime_state()
{
    sprite.setTextureRect(move_frame);

    last_anime_state = anime_state;

    if (have_move)
        have_move = false;
    else
        anime_state = IDL;
}

Sprite Player::get_sprite()
{
    return sprite;
}

Vector2f Player::get_position()
{
    return sprite.getPosition();
}

void Player::set_spawn(float x, float y)
{
    // 5 for avoid sticking to the ground and distance from the ground
    sprite.setPosition(x, y - 5);
    spawn_point = Vector2f(x, y - 5);
}

void Player::reset()
{
    score = DEFAULT_SCORE;
    health = DEFAULT_HELTH;
}

void Player::save_pre_position()
{
    pre_position = sprite.getPosition();
}

Vector2f Player::get_pre_position()
{
    return pre_position;
}

Vector2f Player::get_velocity()
{
    return velocity;
}

FloatRect Player::get_global_bound()
{
    return sprite.getGlobalBounds();
}

void Player::reset_velocity_y()
{
    velocity.y = 0;
}

void Player::reset_velocity_x()
{
    velocity.x = 0;
}

void Player::set_position(float x, float y)
{
    sprite.setPosition(x, y);
}

void Player::move(float x, float y)
{
    sprite.move(x, y);
}
int Player::get_score()
{
    return score;
}
int Player::get_health()
{
    return health;
}
