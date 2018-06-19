#include "stdafx.h"
#include "Slider.h"
#include "Shapes.h"

Slider::Slider(sf::RenderWindow &_window, sf::Vector2f size, sf::Vector2f position, int maxValue)
{
	_setValue = new sf::Thread(&Slider::setValue, this);
	isThreadActive = false;
	window = &_window;
	Outline.setSize(size);
	Slide.setSize(sf::Vector2f(size.x-(size.y- size.y*0.8), size.y*0.8));
	Outline.setPosition(position);
	Slide.setPosition(sf::Vector2f((size.x-Slide.getSize().x) / 2 + position.x, (size.y-Slide.getSize().y) / 2 + position.y));
	Outline.setFillColor(sf::Color(255,0,255));
}

void Slider::setValue()
{
	isThreadActive = true;
	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Slide.setSize(sf::Vector2f(sf::Mouse::getPosition(*window).x - Slide.getPosition().x, Slide.getSize().y));
	}
	isThreadActive = false;
}

void Slider::IsMouseOnSlider()
{
	if(isThreadActive == false)
	if (Shapes::isMouseOnObject(Slide.getGlobalBounds(), *window))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Slide.setFillColor(sf::Color(255, 255, 255));
			_setValue->launch();
		}
		else
		{
			Slide.setFillColor(sf::Color(50, 50, 50));
		}
	}
	else
	{
		Slide.setFillColor(sf::Color(100, 100, 100));
	}

}

void Slider::Display()
{
	IsMouseOnSlider();
	window->draw(Outline);
	window->draw(Slide);
}
