#pragma once
#include "element.h"
#include <vector>

class Pion : public element
{
public:

	Pion();
	~Pion();

	//Wspó³rzêdne na planszy
	sf::Vector2u pozycja_na_planszy;
	
	//Pola do mozliwego ruchu;
	vector<sf::Vector2u> pola_ruchu;

	//ID piona
	unsigned char ID;

	//W³aœciciel Piona
	//	0 = czarny
	//	1 = bialy
	unsigned char wlasciciel;

	
	//Pole przechowywujêce wartoœæ ID dla kolejencyh pionków
	//Zmienna pomocnicza
	static unsigned char ID_P;


	///przypisanie nowych wspolrzednych
	void move(sf::Vector2u& wspolrzedne);

	///zakutalizuj mozliwosci ruchu
	void update();

	///
	void spr_zajetosc_sasiadow(sf::Vector2u, vector<sf::Vector2u>&, sf::Vector2u last = sf::Vector2u(10, 10));
};
 
