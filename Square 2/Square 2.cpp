// Square 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Slider.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	Slider slider(window, sf::Vector2f(300, 200), sf::Vector2f(20, 20), 100);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		slider.Display();
		window.display();
	}

	return 0;
}