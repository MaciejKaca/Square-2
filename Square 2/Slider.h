#pragma once
#include <SFML\Graphics.hpp>
class Slider
{
	public: 
		Slider(sf::RenderWindow &_window, sf::Vector2f size, sf::Vector2f position);
		void setPosition(sf::Vector2f position);
		void Display();
		sf::Vector2f getPosition();
	private:
		sf::RenderWindow *window;
		sf::RectangleShape Outline;
		sf::RectangleShape Slide;
		void Draw();
};