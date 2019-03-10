#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "Gracz.h"
#include "Pole_szachowe.h"
#include "Pion.h"

class Plansza
{
public:
	Plansza();
	~Plansza();

	static Pole_szachowe pole[8][8];

	static vector<Pion *> Pionki;

	///Rysowanie planszy
	static void draw(sf::RenderWindow & window);
	
	///Odpowiada za ruch pionka
	static void move_P(Gracz * gracz, unsigned char ID, sf::Vector2u wsp);
	
	///Zwraca pozycjê na ekranie dla figury na polu
	static sf::Vector2f get_poz_pola(sf::Vector2u t);

};

