#include "Menu_List.h"
#include <iostream>

using namespace std;



Menu_List::Menu_List(float width, float height, int text_size, float top, float left) : width(width), height(height), text_size(text_size), top(top), left(left), active(0)
{
	activate = true;
}

Menu_List::~Menu_List()
{

}

void Menu_List::dodajPrzycisk(string t)
{
	this->push_back(new Przycisk(sf::Vector2f(width, height), sf::Vector2f(left, top), text_size, t));
	top += height + 1;
}

Przycisk* Menu_List::getPrzycisk(int i)
{
	if (i < this->size())
	{
		return this->at(i);
	}
	else
	{
		return nullptr;
	}
}

void Menu_List::draw(sf::RenderWindow & window)
{

	if (this->size() > 0)
	{
		auto pred = [&](Przycisk* przyc) { przyc->draw(window); };

		for_each(this->begin(), this->end(), pred);
	}
}

void Menu_List::setActive(int i)
{
	this->at(i)->setActive();
	active = i;
}

void Menu_List::unsetActive(int i)
{
	this->at(i)->setUnActive();
	
}

void Menu_List::tic(sf::Event & _event, sf::RenderWindow & window)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			
		cout << "UP";
		if (active - 1 >= 0)
		{
			this->unsetActive(active);
			this->setActive(--active);
		}
			
		while (_event.type != sf::Event::KeyReleased)
		{
			window.pollEvent(_event);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		cout << "DOWN";
		if (active + 1 < this->size())
		{
			this->unsetActive(active);
			this->setActive(++active);
		}

		while (_event.type != sf::Event::KeyReleased)
		{
			window.pollEvent(_event);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		this->activate = false;
		this->at(active)->run();
		while (_event.type != sf::Event::KeyReleased)
		{
			window.pollEvent(_event);
		}
	}
}
