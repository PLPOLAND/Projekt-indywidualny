#pragma once
#include "element.h"

class Pion : public element
{
public:

	Pion();
	~Pion();

	//Wsp�rz�dne na planszy
	unsigned char pozycja_na_planszy[2];

	//ID piona
	unsigned char ID;

	//W�a�ciciel Piona
	//	0 = czarny
	//	1 = bialy
	unsigned char wlasciciel;

	
	//Pole przechowywuj�ce warto�� ID dla kolejencyh pionk�w
	//Zmienna pomocnicza
	static unsigned char ID_P;

	void move(sf::Vector2u& wspolrzedne);
};
 
