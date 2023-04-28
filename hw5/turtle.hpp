#include "person.hpp"
#include "define.hpp"

class Turtle : public Person
{

public:
    
    Turtle(int health_, Vector2f position_, float jump_high_, int score_, Vector2f speed_, string image_addr);
    Vector2f get_move_size();
    
private:
    int score;
};
