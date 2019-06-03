#include "Pole_szachowe.h"

const sf::Color Pole_szachowe::kolor_c(233, 107, 57);
const sf::Color Pole_szachowe::kolor_b(255, 220, 185);
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
		this->setFillColor(kolor_c);
	}
	else
	{
		this->setFillColor(kolor_b);
	}
}

void Pole_szachowe::set_trigg()
{
	flagi.trig = true;
	this->koloruj();
}

void Pole_szachowe::unset_trigg()
{
	flagi.trig = false;
	this->koloruj();
}

bool Pole_szachowe::get_trigg()
{
	return flagi.trig;
}

void Pole_szachowe::set_path()
{
	flagi.path = true;
	this->koloruj();
}

void Pole_szachowe::unset_path()
{
	flagi.path = false;
	this->koloruj();
}

void Pole_szachowe::koloruj()
{
	if (flagi.false_all())
	{
		//std:://cout << "kolor_bazowy";
		if (kolor == CZARNY)
		{
			this->setFillColor(kolor_c);
		}
		else
		{
			this->setFillColor(kolor_b);
		}
	}
	else if (flagi.trig == true)
	{
		//std:://cout << "kolor_trigg";
		this->setFillColor(kolor_trigg);
	}
	else if (flagi.path == true) {
		//std:://cout << "kolor_path";
		this->setFillColor(kolor_path);
	}
}

Pole_szachowe::Flags::Flags(): trig(false), path(false)
{
}

bool Pole_szachowe::Flags::false_all()
{
	return trig == false && path == false;
}
