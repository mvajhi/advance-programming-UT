#include "person.hpp"
#include "define.hpp"

class Turtle : public Person
{
    
    public:
    vector<string> horizontal_move(vector<string> game_board,pair<int ,int> portal_coordinate,int status);
    vector<string> move(vector<string> game_board,pair<int ,int> portal_coordinate,int status);
    vector<string> encounter_wall(vector<string> game_board,int side);
    vector<string> encounter_enemy(vector<string> game_board,int side,pair<int ,int> portal_coordinate);
    vector<string> encounter_star_or_diamond(vector<string> game_board,int side,int star_or_diamond);
    vector<string> without_encounter(vector<string> game_board,int side);
    void initialize(int &side,int status);
    Turtle(int x_,int y_,int v_x_=0,int v_y_=0,int jump_high_=JUMP_HIGH,int health_=TURTLE_HEALTH,int score_=0);
    private:
    int score;
    vector<Baby_turtle *> baby_turtles;
    vector<First_enemy *> first_enemies;
    vector<Second_enemy *> second_enemies;

};

