#include "Pion.h"
#include <iostream>


unsigned char Pion::ID_P = 0;

Pion::Pion() : ID(ID_P++) {
	//Jeœli ID < 16 
	//pionek czarny gracz 
	//IDGracza 0
	if ((int)ID / 16 == 0)
	{
		wlasciciel = 0;
		texture->loadFromFile("pion_czarny.png");
		this->setTexture(*texture);

		pozycja_na_planszy[1] = ID % 8;
		pozycja_na_planszy[0] = ((int)ID / 8);
	}
	else
	{
		wlasciciel = 1;

		texture->loadFromFile("pion.png");
		this->setTexture(*texture);

		pozycja_na_planszy[1] = ID % 8;
		pozycja_na_planszy[0] = 4 + ((int)ID / 8);
	}

}

Pion::~Pion()
{
}

void Pion::move(sf::Vector2u & wspolrzedne)
{
	pozycja_na_planszy[0] = wspolrzedne.x;
	pozycja_na_planszy[1] = wspolrzedne.y;
	
	//cout << "Pion::Move " << (int)pozycja_na_planszy[0] << (int)pozycja_na_planszy[1] << endl;
}
