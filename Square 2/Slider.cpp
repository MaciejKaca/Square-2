#include "stdafx.h"
#include "Slider.h"
#include "Shapes.h"
#include <SFML\System.hpp>

Slider::Slider(sf::RenderWindow &_window, sf::Vector2f size, sf::Vector2f position, int maxValue)
{
	window = &_window;
	Outline.setSize(size);
	Slide.setSize(sf::Vector2f(size.x-(size.y- size.y*0.8), size.y*0.8));
	Outline.setPosition(position);
	Slide.setPosition(sf::Vector2f((size.x-Slide.getSize().x) / 2 + position.x, (size.y-Slide.getSize().y) / 2 + position.y));
	Outline.setFillColor(sf::Color(255,0,255));
	Slide.setFillColor(sf::Color(255, 255, 0));
}

void Slider::IsMouseOnSlider()
{
	if (Shapes::isMouseOnObject(Slide.getGlobalBounds(), *window))
	{
		Slide.setFillColor(sf::Color(0, 255, 0));
	}
	else
	{
		Slide.setFillColor(sf::Color(0, 0, 0));
	}
}

void Slider::Display()
{
	IsMouseOnSlider();
	window->draw(Outline);
	window->draw(Slide);
}