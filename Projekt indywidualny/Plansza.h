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

	///oznaczenie pola jako aktywne
	static void trigg(sf::Vector2u);

	///oznaczenie pola jako nieaktywne
	static void untrigg(sf::Vector2u);

	///oznaczenie pola jako dostepne do ruchu
	static void path(sf::Vector2u);

	///odznaczenie pola jako dostepnego do ruchu
	static void unpath(sf::Vector2u);
	
	///Zwraca pozycjê na ekranie dla figury na polu
	static sf::Vector2f get_poz_pola(sf::Vector2u t);

	///Zwraca wartosc boolwska czy pionek o podanych kordynatach nalezy do danego gracza
	static bool czy_pionek_nalezy(sf::Vector2u, Gracz* );

	static bool czy_pole_zajete(sf::Vector2u);

	static int get_id_piona(sf::Vector2u);
	
	static void update_p();

	static Pion* get_pion(sf::Vector2u);
	static void print();
};

