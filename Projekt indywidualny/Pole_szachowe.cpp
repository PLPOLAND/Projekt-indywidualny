#include "Pole_szachowe.h"



Pole_szachowe::Pole_szachowe() : sf::RectangleShape(sf::Vector2f(SZEROKOSC, WYSOKOSC))
{

}


Pole_szachowe::~Pole_szachowe()
{

}

void Pole_szachowe::update()
{
	PozycjaIkony = this->getPosition();
	//PozycjaIkony.x += 20.F;
	//PozycjaIkony.y += 20.F;
}
