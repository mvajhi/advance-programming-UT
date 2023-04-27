#include <iostream>
#include <SFML/Graphics.hpp>
#include "game_manager.hpp"

using namespace std;
using namespace sf;

int main()
{
	Game_manager the_game;
	the_game.read_level1();

	while (true)
	{
		the_game.proccess_events();

		the_game.update();
	}

	return 0;
}