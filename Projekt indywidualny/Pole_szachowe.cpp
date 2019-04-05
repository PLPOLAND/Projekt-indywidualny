#include "Pole_szachowe.h"

const sf::Color Pole_szachowe::kolor_cz(255, 220, 185);
const sf::Color Pole_szachowe::kolor_b(233, 107, 57);
const sf::Color Pole_szachowe::kolor_trigg(255, 40, 40);
const sf::Color Pole_szachowe::kolor_path(2, 165, 0);

Pole_szachowe::Pole_szachowe() : sf::RectangleShape(sf::Vector2f(SZEROKOSC, WYSOKOSC)), zajete(false), aktywne(false),czy_ruch(false), kolor(CZARNY)
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

void Pole_szachowe::set_kolor(Kolor_Pola k)
{
	kolor = k;

	if (kolor == CZARNY)
	{
		this->setFillColor(kolor_cz);
	}
	else
	{
		this->setFillColor(kolor_b);
	}
}

void Pole_szachowe::set_trigg()
{
	aktywne = true;
	this->setFillColor(kolor_trigg);
}

void Pole_szachowe::unset_trigg()
{
	aktywne = false;
	if (kolor == CZARNY)
	{
		this->setFillColor(kolor_cz);
	}
	else
	{
		this->setFillColor(kolor_b);
	}
}

bool Pole_szachowe::get_trigg()
{
	return aktywne;
}

void Pole_szachowe::set_path()
{
	czy_ruch = true;
	this->setFillColor(kolor_path);
}

void Pole_szachowe::unset_path()
{
	czy_ruch = false;
	if (kolor == CZARNY)
	{
		this->setFillColor(kolor_cz);
	}
	else
	{
		this->setFillColor(kolor_b);
	}
}
