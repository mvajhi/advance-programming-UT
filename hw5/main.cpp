#include <iostream>
#include <SFML/Graphics.hpp>
#include "game_manager.hpp"

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 600), "SFML works!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}