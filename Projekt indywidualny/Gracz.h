#pragma once
#include <SFML/Graphics.hpp>
#include "Menu_List.h"

class Gracz
{
protected:
	bool was_move;
public:		
	
	Gracz();

	enum KOLOR
	{
		BIALY,
		CZARNY
	};
	KOLOR kolor_gracza;
	bool czy_ruch;
	unsigned char ID;
	int wynik;
	static unsigned char ID_G;


	virtual void tic(sf::Event&, sf::RenderWindow&, Menu_List&) = 0;
	bool wasMove();
	void clearMove();

};

