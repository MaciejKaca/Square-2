#pragma once
#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
class Shapes
{
	public:
		static bool isMouseOnObject(sf::FloatRect boundingBox, sf::RenderWindow &window);
};

bool Shapes::isMouseOnObject(sf::FloatRect boundingBox, sf::RenderWindow &window)
{
	sf::Vector2f mouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	if (boundingBox.contains(mouse))
	{
		return true;
	}
	else
	{
		return false;
	}
}