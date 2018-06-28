#include "stdafx.h"
#include "Slider.h"
#include "Shapes.h"

Slider::Slider(sf::RenderWindow &_window, sf::Vector2f size, sf::Vector2f position, int _maxValue)
{
	_setValue = new sf::Thread(&Slider::setValue, this);
	_mouseOutOfShape = new sf::Thread(&Slider::mouseOutOfShape, this);
	isThreadActive = false;
	window = &_window;
	Outline.setSize(size);
	Slide.setSize(sf::Vector2f(size.x-(size.y- size.y*0.8), size.y*0.8));
	Outline.setPosition(position);
	Slide.setPosition(sf::Vector2f((size.x-Slide.getSize().x) / 2 + position.x, (size.y-Slide.getSize().y) / 2 + position.y));
	Outline.setFillColor(sf::Color(255,0,255));
	Shade = Slide;
	sf::Color color = Outline.getFillColor();
	Shade.setFillColor(sf::Color(std::abs(color.r-50), std::abs(color.g-50),std::abs(color.b-50)));
	maxValue = _maxValue;
}

void Slider::setValue()
{
	isThreadActive = true;
	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		int step = (Shade.getSize().x) / (maxValue - 1);
		int width = Shade.getSize().x;
		int mousePosistion = sf::Mouse::getPosition(*window).x - Slide.getPosition().x;
		Value = ceil(mousePosistion / step);

		Slide.setSize(sf::Vector2f( Value*step, Slide.getSize().y));
	}
	isThreadActive = false;
}

void Slider::mouseOutOfShape()
{
	isThreadActive = true;
	while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
	isThreadActive = false;
}

void Slider::IsMouseOnSlider()
{
	if (isThreadActive == false)
	{
		if (Shapes::isMouseOnObject(Shade.getGlobalBounds(), *window))
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
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				_mouseOutOfShape->launch();
			}
		}
	}

}

void Slider::Display()
{
	IsMouseOnSlider();
	window->draw(Outline);
	window->draw(Shade);
	window->draw(Slide);
}
