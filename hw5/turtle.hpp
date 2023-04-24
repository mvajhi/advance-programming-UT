#include "person.hpp"
#include "define.hpp"

class Turtle : public Person
{
    
    public:
    Turtle(int x_,int y_,int v_x_=0,int v_y_=0,int jump_high_=JUMP_HIGH,int health_=TURTLE_HEALTH,int score_=0);
    private:
    int score;

};

