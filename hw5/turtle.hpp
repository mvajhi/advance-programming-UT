#include "person.hpp"
#include "define.hpp"

class Turtle : public Person
{

public:
    void move(Collision_report colisions);
    Turtle(int health_, Vector2f position_, float jump_high_, int score_, Vector2f speed_, string image_addr);
    Events get_events();
    void set_events(Events events_);
    void handel_input(int order);
    
private:
    Events events;
    int score;
};
