#pragma once

#include <SFML/Graphics.hpp>
#include "Gracz.h"
#include "Plansza.h"

class Gracz_Ludzki : public Gracz
{
public:

	Gracz_Ludzki();


	//WYB_PIONA
	//RUCH_PIONA
	enum Faza_ruchu
	{
		WYB_PIONA,
		RUCH_PIONA
	};

	Faza_ruchu faza; //okreœla fazê ruchu gracza

	sf::Vector2u last_trigg; //przechowuje wspolrzedne ostatniego aktywnego pola
	sf::Vector2u wsp_piona; //przechowuje wspolrzedne wybranego piona


	///Wykonanie ruchu pionkiem
	virtual void ruch(unsigned char, sf::Vector2u );

	///Obsluga gracza
	virtual void tic(sf::Event&, sf::RenderWindow&);
	
	void trigg(sf::Keyboard::Key);

};

