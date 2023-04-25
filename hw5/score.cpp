#include "score.hpp"

Score::Score(/* args */)
{    
}

void Score::set_texture(string address, float scale)
{
    symbole.loadFromFile(address);
    m_sprite.setTexture(symbole);
    m_sprite.setScale(scale);
}

Sprite Score::get_sprite()
{
    return m_sprite;
}

Score::~Score()
{
}
