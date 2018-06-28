#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <thread>         

class Slider
{
	public: 
		Slider(sf::RenderWindow &_window, sf::Vector2f size, sf::Vector2f position, int _maxValue);
		void setPosition(sf::Vector2f position);
		void Display();
		sf::Vector2f getPosition();
		int getValue();
	private:
		sf::RenderWindow *window;
		sf::RectangleShape Outline;
		sf::RectangleShape Slide;
		sf::RectangleShape Shade;
		sf::Thread *_setValue;
		sf::Thread *_mouseOutOfShape;
		void setValue();
		void mouseOutOfShape();
		void IsMouseOnSlider();
		bool isThreadActive;
		int maxValue;
		int Value;
};