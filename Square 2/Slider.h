#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
class Slider
{
	public: 
		Slider(sf::RenderWindow &_window, sf::Vector2f size, sf::Vector2f position, int maxValue);
		void setPosition(sf::Vector2f position);
		void Display();
		sf::Vector2f getPosition();
		int getValue();
	private:
		sf::RenderWindow *window;
		sf::RectangleShape Outline;
		sf::RectangleShape Slide;
		void IsMouseOnSlider();
};