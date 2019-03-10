#include "Gracz_Ludzki.h"

Gracz_Ludzki::~Gracz_Ludzki()
{
}

void Gracz_Ludzki::ruch(unsigned char id_p, sf::Vector2u wsp)
{
	Plansza::move_P(this, id_p,	sf::Vector2u(wsp.y,wsp.x));
}

void Gracz_Ludzki::tic()
{
}
