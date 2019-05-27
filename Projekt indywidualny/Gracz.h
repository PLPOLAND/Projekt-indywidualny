#pragma once
#include <SFML/Graphics.hpp>

class Gracz
{
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

	static unsigned char ID_G;



	//virtual void ruch(unsigned char id_p, sf::Vector2u wsp) = 0;
	virtual void tic(sf::Event&, sf::RenderWindow&) = 0;

};

