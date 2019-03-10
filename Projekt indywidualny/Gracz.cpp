#pragma once
#include"Gracz.h"

Gracz::Gracz(/*Plansza & pl*/) : kolor_gracza()/*, plansza(pl)*/, czy_ruch(false), ID(ID_G++) {
	if (ID % 2 == 0)
	{
		kolor_gracza = CZARNY;
	}
	else
		kolor_gracza = BIALY;
}

unsigned char Gracz::ID_G=0;