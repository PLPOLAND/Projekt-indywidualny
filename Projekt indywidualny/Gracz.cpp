#pragma once
#include"Gracz.h"

Gracz::Gracz() : kolor_gracza(), czy_ruch(false), wynik(0), ID(ID_G++) {
	if (ID % 2 == 0)
	{
		kolor_gracza = CZARNY;
	}
	else
		kolor_gracza = BIALY;
}

unsigned char Gracz::ID_G=0;

bool Gracz::wasMove()
{
	return this->was_move;
}

void Gracz::clearMove()
{
	was_move = false;
}