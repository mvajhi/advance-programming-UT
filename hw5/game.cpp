#include "game.hpp"
#include <fstream>
#include <bits/stdc++.h>

void Game::check_2_shape_collision(Vector2f person_pos, Vector2f object_pos, bool report[], Vector2f move_size)
{
    float x = object_pos.x;
    float y = object_pos.y;

    if (are_they_in_one_line_y(person_pos.y, y) &&
        x <= person_pos.x + move_size.x + BLOCK_SIZE && person_pos.x + move_size.x + BLOCK_SIZE < x + BLOCK_SIZE)
        report[RIGHT] = true;

    if (are_they_in_one_line_x(person_pos.x, x) &&
        y <= person_pos.y + move_size.y + BLOCK_SIZE && person_pos.y + move_size.y + BLOCK_SIZE < y + BLOCK_SIZE)
        report[DOWN] = true;

    if (are_they_in_one_line_y(person_pos.y, y) &&
        x < person_pos.x - move_size.x && person_pos.x - move_size.x <= x + BLOCK_SIZE)
        report[LEFT] = true;

    if (are_they_in_one_line_x(person_pos.x, x) &&
        y - BLOCK_SIZE < person_pos.y - move_size.y - BLOCK_SIZE && person_pos.y - move_size.y - BLOCK_SIZE <= y)
        report[UP] = true;
}

bool Game::are_they_in_one_line_y(float person_y, float obj_y)
{
    return person_y <= obj_y && obj_y < person_y + BLOCK_SIZE;
}

bool Game::are_they_in_one_line_x(float person_x, float obj_x)
{
    return person_x - BLOCK_SIZE <= obj_x && obj_x < person_x + BLOCK_SIZE;
}

void Game::check_vertical_collision(FloatRect floor, float dy)
{
    bool report[4] = {false, false, false, false};

    check_2_shape_collision(the_player.get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 3));
    if (report[DOWN])
    {
        the_player.reset_velocity_y();
        the_player.set_position(the_player.get_position().x,
                                the_player.get_position().y - dy);
    }

    check_2_shape_collision(the_player.get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 0));
    if (report[UP])
    {
        the_player.reset_velocity_y();
        the_player.set_position(the_player.get_position().x,
                                the_player.get_position().y - dy);
    }
}

void Game::check_horizontal_collision(FloatRect floor, float dx)
{
    bool report[4] = {false, false, false, false};

    check_2_shape_collision(the_player.get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 0));
    if (report[RIGHT])
    {
        the_player.reset_velocity_x();
        the_player.set_position(the_player.get_position().x - dx - EPSILON,
                                the_player.get_position().y);
    }

    check_2_shape_collision(the_player.get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 0));
    if (report[LEFT])
    {
        the_player.reset_velocity_x();
        the_player.set_position(the_player.get_position().x - dx + EPSILON,
                                the_player.get_position().y);
    }
}

bool Game::can_jump()
{
    vector<FloatRect> floors = the_game_board.get_floors_bound();
    for (auto floor : floors)
    {
        bool report[4] = {false, false, false, false};

        check_2_shape_collision(the_player.get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 20));

        if (report[DOWN])
            return true;
    }
    return false;
}

void Game::collision_player_and_boys()
{
    vector<FloatRect> boys = the_game_board.get_boys_bound();
    for (size_t i = 0; i < boys.size(); i++)
        if (boys[i].intersects(the_player.get_global_bound()))
            the_game_board.free_boy(i);
}

void Game::update_collisions()
{
    collision_player_and_floors();
    collision_boys_and_floors();
    collision_player_and_scores();
    collision_player_and_boys();
}

void Game::collision_player_and_floors()
{
    vector<FloatRect> floors = the_game_board.get_floors_bound();
    for (auto floor : floors)
    {
        float dx = the_player.get_position().x - the_player.get_pre_position().x;
        float dy = the_player.get_position().y - the_player.get_pre_position().y;
        check_horizontal_collision(floor, dx);
        check_vertical_collision(floor, dy);
    }
}

void Game::collision_boys_and_floors()
{
    for (size_t i = 0; i < the_game_board.get_boys().size(); i++)
    {
        vector<FloatRect> floors = the_game_board.get_floors_bound();
        for (auto floor : floors)
        {
            float dx = the_game_board.get_boys()[i].get_position().x - the_game_board.get_boys()[i].get_pre_position().x;
            float dy = the_game_board.get_boys()[i].get_position().y - the_game_board.get_boys()[i].get_pre_position().y;

            bool report[4] = {false, false, false, false};

            check_2_shape_collision(the_game_board.get_boys()[i].get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 3));
            if (report[DOWN])
            {
                the_game_board.get_boys()[i].reset_velocity_y();
                the_game_board.get_boys()[i].set_position(the_game_board.get_boys()[i].get_position().x,
                                                          the_game_board.get_boys()[i].get_position().y - dy);
            }

            check_2_shape_collision(the_game_board.get_boys()[i].get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 0));
            if (report[RIGHT])
            {
                the_game_board.get_boys()[i].go_left();
                the_game_board.get_boys()[i].reset_velocity_x();
                the_game_board.get_boys()[i].set_position(the_game_board.get_boys()[i].get_position().x - dx - EPSILON,
                                                          the_game_board.get_boys()[i].get_position().y);
            }

            check_2_shape_collision(the_game_board.get_boys()[i].get_position(), Vector2f(floor.left, floor.top), report, Vector2f(0, 0));
            if (report[LEFT])
            {
                the_game_board.get_boys()[i].go_right();
                the_game_board.get_boys()[i].reset_velocity_x();
                the_game_board.get_boys()[i].set_position(the_game_board.get_boys()[i].get_position().x - dx + EPSILON,
                                                          the_game_board.get_boys()[i].get_position().y);
            }
        }
    }
}

void Game::collision_player_and_scores()
{
    vector<FloatRect> diamonds = the_game_board.get_diamonds_bound();
    vector<FloatRect> stars = the_game_board.get_stars_bound();
    FloatRect player_bound = the_player.get_global_bound();

    for (size_t i = 0; i < diamonds.size(); i++)
        if (diamonds[i].intersects(player_bound))
        {
            the_player.add_score(DIAMOND_SCORE);
            the_game_board.remove_diamond(i);
            return;
        }

    for (size_t i = 0; i < stars.size(); i++)
        if (stars[i].intersects(player_bound))
        {
            the_player.add_score(STAR_SCORE);
            the_game_board.remove_star(i);
            return;
        }
}

void Game::proccess_win()
{
    menu_manager.show_menu(WIN_MENU, the_player.get_score());
    reset();
}

int Game::get_score()
{
    cout << the_player.get_score() <<endl;
    return the_player.get_score();
}

Game::Game() : the_window(WINDOW_W, WINDOW_H, "game", this),
               the_player(PLAYER_IMG),
               menu_manager(this, the_window.get_window())
{
    t_pause.loadFromFile(PAUSE_IMG);
    pause.setTexture(t_pause);
    pause.setScale(PAUSE_SCALE, PAUSE_SCALE);

    menu_manager.show_menu(START_MENU);
    initilaize_font();
}

RenderWindow &Game::get_window()
{
    return the_window.get_window();
}

void Game::update()
{
    the_window.get_events();
    the_player.update();
    the_game_board.update();
    update_collisions();
    update_UI();
}

void Game::render()
{
    vector<Sprite> sprites = the_game_board.get_board();
    sprites.push_back(the_player.get_sprite());
    vector<Drawable *> output = sprites_to_drawables_ptr(sprites);
    output.push_back(&score);
    output.push_back(&health);
    output.push_back(&pause);

    the_window.render(output, the_player.get_position());
}

void Game::handel_event(Event event)
{
    if (event.type == Event::Closed)
        the_window.close();
    else if (event.type == Event::KeyPressed)
        handel_keyboard_event(event);
    else if (event.type == Event::MouseButtonPressed)
        handel_mouse_event(event);
}

void Game::handel_keyboard_event(Event event)
{
    if (event.key.code == Keyboard::Escape)
        the_window.close();
    else if (event.key.code == Keyboard::D)
        the_player.move_handel(RIGHT);
    else if (event.key.code == Keyboard::A)
        the_player.move_handel(LEFT);
    else if (event.key.code == Keyboard::W)
        if (can_jump())
            the_player.move_handel(UP);
}

void Game::handel_mouse_event(Event event)
{
    Vector2f mouse_pos = (Vector2f)Mouse::getPosition(the_window.get_window());
    mouse_pos += the_player.get_position() - Vector2f(WINDOW_W / 2, WINDOW_H / 2);

    if (pause.getGlobalBounds().contains(mouse_pos))
    {
        cout << "pause\n";

        menu_manager.show_menu(PAUSE_MENU);
        if (menu_manager.reset)
            reset();
    }
}

void Game::pre_update()
{
    if(the_game_board.is_all_boy_in_portal())
    {
        proccess_win();
    }
    the_player.save_pre_position();
    the_game_board.pre_update();
}

void Game::read_level()
{
    vector<string> text_map = read_map_file(menu_manager.level_path);

    proccess_text_map(text_map);
}

void Game::show_menu()
{
    menu_manager.show_menu(START_MENU);
}

void Game::reset()
{
    the_game_board.reset_map();
    the_player.reset();
    read_level();
}

vector<string> Game::read_map_file(string address_file)
{
    ifstream board_file(address_file);
    string line;
    vector<string> output;
    while (getline(board_file, line))
        output.push_back(line);
    return output;
}

void Game::proccess_new_block(Vector2f position, char value)
{
    position = convert_text_to_pixle_pos(position);

    if (value == FLOOR_MAP_SYMBOLE)
        the_game_board.add_new_floor(position);
    else if (value == DIAMOND_SYMBOL)
        the_game_board.add_new_diamond(position);
    else if (value == STAR_SYMBOL)
        the_game_board.add_new_star(position);
    else if (value == BOY_TURTLE_SYMBOL)
        the_game_board.add_new_boy_turtle(position);
    else if (value == PLAYER_MAP_SYMBOLE)
    {
        the_player.set_spawn(position.x, position.y);
        the_game_board.set_portal(position);
    }
}

void Game::proccess_text_map(vector<string> text_map)
{
    for (size_t y = 0; y < text_map.size(); y++)
        for (size_t x = 0; x < text_map[y].length(); x++)
            proccess_new_block(Vector2f(x, y), text_map[y][x]);
}

Vector2f Game::convert_text_to_pixle_pos(Vector2f position)
{
    return Vector2f(position.x * BLOCK_SIZE, position.y * BLOCK_SIZE);
}

vector<Drawable *> Game::sprites_to_drawables_ptr(vector<Sprite> &sprites)
{
    vector<Drawable *> output;
    for (size_t i = 0; i < sprites.size(); i++)
        output.push_back(&sprites[i]);
    return output;
}
string Game::show_score()
{
    int score_val = the_player.get_score();
    return "score : " + to_string(score_val);
}
string Game::show_health()
{
    int health_val = the_player.get_health();
    return "health : " + to_string(health_val);
}
void Game::update_UI()
{
    score.setString(show_score());
    score.setOrigin(score.getGlobalBounds().width / 2, score.getGlobalBounds().height / 2);
    score.setPosition(the_player.get_position() + SCORE_UI_POS);

    health.setString(show_health());
    health.setOrigin(health.getGlobalBounds().width / 2, health.getGlobalBounds().height / 2);
    health.setPosition(the_player.get_position() + HEALTH_UI_POS);

    pause.setPosition(the_player.get_position() + Vector2f(-WINDOW_W / 2 + BLOCK_SIZE / 2,
                                                           -WINDOW_H / 2 + BLOCK_SIZE / 4));
}

void Game::initilaize_font()
{
    font.loadFromFile(ADDR_FONT_2);

    score.setFont(font);
    score.setCharacterSize(FONT_SIZE);
    score.setFillColor(FONT_COLOR);

    health.setFont(font);
    health.setCharacterSize(FONT_SIZE);
    health.setFillColor(FONT_COLOR);
}
