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
		// TODO handle events
		// Event event;
		// while (window.pollEvent(event))
		// {
		// 	if (event.type == Event::Closed)
		// 		window.close();
		// }

		the_game.update();
	}

	return 0;
}