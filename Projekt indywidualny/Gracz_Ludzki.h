#pragma once

#include "Gracz.h"
#include "Plansza.h"
class Gracz_Ludzki : public Gracz
{
public:

	Gracz_Ludzki() : Gracz() {};
	~Gracz_Ludzki();

	virtual void ruch(unsigned char id_p, sf::Vector2u wsp);
	virtual void tic();
	

};

