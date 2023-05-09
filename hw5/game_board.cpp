#include "game_board.hpp"

Game_board::Game_board()
    : boy_turtle(BOY_IMG)
{
        initialize_floor();
        initialize_diamond();
        initialize_star();
        initialize_portal();
}

void Game_board::pre_update()
{
        for (size_t i = 0; i < boys.size(); i++)
                boys[i].save_pre_position();
}

void Game_board::update()
{
        update_boy_move();
        update_collision();
}

void Game_board::update_boy_move()
{
        for (size_t i = 0; i < boys.size(); i++)
                boys[i].update();
}

void Game_board::update_collision()
{
        collision_boys_and_portal();
}

void Game_board::collision_boys_and_portal()
{
        for (size_t i = 0; i < boys.size(); i++)
                if (boys[i].get_global_bound().intersects(portal.getGlobalBounds()))
                {
                        boys.erase(boys.begin() + i);
                        i--;
                }
}

void Game_board::initialize_floor()
{
        t_floor.loadFromFile(FLOOR_IMG);
        floor.setTexture(t_floor);
        floor.setScale(FLOOR_SCALE, FLOOR_SCALE);
}

void Game_board::initialize_diamond()
{
        t_diamond.loadFromFile(DIAMOND_IMG);
        diamond.setTexture(t_diamond);
        diamond.setScale(DIAMOND_SCALE, DIAMOND_SCALE);
}

void Game_board::initialize_star()
{
        t_star.loadFromFile(STAR_IMG);
        star.setTexture(t_star);
        star.setScale(STAR_SCALE, STAR_SCALE);
}

void Game_board::initialize_portal()
{
        t_portal.loadFromFile(PORTAL_IMG);
        portal.setTexture(t_portal);
        portal.setScale(PORTAL_SCALE, PORTAL_SCALE);
}

void Game_board::initialize_boy()
{
}

void Game_board::add_new_floor(Vector2f position)
{
        Sprite tmp_floor = floor;
        tmp_floor.setPosition(position.x, position.y);
        floors.push_back(tmp_floor);
}
void Game_board::add_new_diamond(Vector2f position)
{
        Sprite tmp_diamond = diamond;
        tmp_diamond.setPosition(position.x, position.y);
        diamonds.push_back(tmp_diamond);
}
void Game_board::add_new_star(Vector2f position)
{
        Sprite tmp_star = star;
        tmp_star.setPosition(position.x, position.y);
        stars.push_back(tmp_star);
}
void Game_board::add_new_boy_turtle(Vector2f position)
{
        Boy tmp_boy_turtle = boy_turtle;
        tmp_boy_turtle.set_spawn(position.x, position.y);
        boys.push_back(tmp_boy_turtle);
}
void Game_board::set_portal(Vector2f position)
{
        portal.setPosition(position);
}

void Game_board::reset_map()
{
        floors.clear();
        boys.clear();
        diamonds.clear();
        stars.clear();
}

vector<FloatRect> Game_board::get_floors_bound()
{
        vector<FloatRect> board;
        for (size_t i = 0; i < floors.size(); i++)
                board.push_back(floors[i].getGlobalBounds());

        return board;
}
vector<FloatRect> Game_board::get_stars_bound()
{
        vector<FloatRect> stars_;
        for (size_t i = 0; i < stars.size(); i++)
                stars_.push_back(stars[i].getGlobalBounds());

        return stars_;
}
vector<FloatRect> Game_board::get_diamonds_bound()
{
        vector<FloatRect> diamonds_;
        for (size_t i = 0; i < diamonds.size(); i++)
                diamonds_.push_back(diamonds[i].getGlobalBounds());

        return diamonds_;
}
vector<FloatRect> Game_board::get_boys_bound()
{
        vector<FloatRect> boy_turtles_;
        for (size_t i = 0; i < boys.size(); i++)
                boy_turtles_.push_back(boys[i].get_global_bound());

        return boy_turtles_;
}
vector<Sprite> Game_board::get_board()
{
        vector<Sprite> output;
        output.reserve(floors.size() + diamonds.size() + stars.size());
        output.insert(output.end(), floors.begin(), floors.end());
        output.insert(output.end(), diamonds.begin(), diamonds.end());
        output.insert(output.end(), stars.begin(), stars.end());
        for (size_t i = 0; i < boys.size(); i++)
                output.push_back(boys[i].get_sprite());

        output.push_back(portal);

        return output;
}

vector<Boy> &Game_board::get_boys()
{
        return boys;
}

void Game_board::remove_diamond(int pos)
{
        diamonds.erase(diamonds.begin() + pos);
}

void Game_board::remove_star(int pos)
{
        stars.erase(stars.begin() + pos);
}

void Game_board::free_boy(int pos)
{
        boys[pos].set_free();
}

bool Game_board::is_all_boy_in_portal()
{
        return boys.size() == 0;
}
