#pragma once
#include "element.h"

class Pion : public element
{
public:

	Pion();
	~Pion();

	//Wspó³rzêdne na planszy
	unsigned char pozycja_na_planszy[2];

	//ID piona
	unsigned char ID;

	//W³aœciciel Piona
	//	0 = czarny
	//	1 = bialy
	unsigned char wlasciciel;

	
	//Pole przechowywujêce wartoœæ ID dla kolejencyh pionków
	//Zmienna pomocnicza
	static unsigned char ID_P;

	void move(sf::Vector2u& wspolrzedne);
};
 
