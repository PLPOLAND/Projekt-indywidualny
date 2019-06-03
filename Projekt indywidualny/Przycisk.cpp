#include "Przycisk.h"
#include <iostream>


Przycisk::Przycisk(sf::Vector2f rozm, sf::Vector2f wspo, int rozm_tex, string text_, bool endi): sf::RectangleShape(), text(), isActive(false), end(endi)
{

	this->setSize(rozm);
	this->setPosition(wspo);
	this->setFillColor(sf::Color(50, 50, 50));
	font.loadFromFile("Zasoby/Verdana.ttf");
	text.setString(text_);
	text.setFont(font);
	text.setCharacterSize(rozm_tex);
	text.setFillColor(sf::Color(255,255, 255));

	
	
	//cout << this->getSize().y << endl
		/*<< text.getGlobalBounds().height << endl
		<< this->getGlobalBounds().top + (this->getSize().y - text.getGlobalBounds().height) / 2 << endl
		<< text.getGlobalBounds().top << endl
		<<endl
		<< text.getLocalBounds().width + text.getLocalBounds().left << endl
		<< text.getLocalBounds().width << endl
		<< text.getLocalBounds().left << endl;*/

	float tmp_x = this->getPosition().x + (this->getSize().x / 2) - ((text.getLocalBounds().width + text.getLocalBounds().left) / 2);
	float tmp_y = this->getPosition().y + (this->getSize().y / 2) - ((text.getLocalBounds().height + text.getLocalBounds().top) / 2);
	
	text.setPosition(sf::Vector2f(tmp_x, tmp_y));

}


Przycisk::~Przycisk()
{
}

void Przycisk::setActive()
{
	isActive = true;
	setFillColor(sf::Color(255, 24, 1));
}

void Przycisk::setUnActive()
{
	isActive = false;
	setFillColor(sf::Color(50, 50, 50));
}

void Przycisk::setFunction(void (*fun)())
{
	funkcja = fun;
}



void Przycisk::run()
{
	if (funkcja!=nullptr)
	{
		funkcja();
	}
}

void Przycisk::draw(sf::RenderWindow& win)
{
	win.draw(*this);
	win.draw(text);
}
