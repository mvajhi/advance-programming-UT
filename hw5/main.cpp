#include <iostream>
#include <SFML/Graphics.hpp>
#include "game_manager.hpp"

using namespace std;
using namespace sf;

int main()
{
	game_manager the_game;
	// RenderWindow window(sf::VideoMode(900, 600), "game");

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