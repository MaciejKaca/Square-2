#include "stdafx.h"
#include "Slider.h"

Slider::Slider(sf::RenderWindow &_window, sf::Vector2f size, sf::Vector2f position)
{
	window = &_window;
	Outline.setPosition(position);
	Slide.setPosition(position);
	Outline.setSize(size);
	Slide.setSize(size);
	Outline.setFillColor(sf::Color(255,0,255));
	Slide.setFillColor(sf::Color(255, 255, 0));
}

void Slider::Display()
{
	window->draw(Outline);
	window->draw(Slide);
}