#pragma once
#include "element.h"
#include <vector>
#include "Pole_szachowe.h"

enum Kierunek
{
	BRAK,
	LG,
	RG,
	LD,
	RD
};

class Pion : public element
{
public:

	Pion();
	~Pion();

	//Wspó³rzêdne na planszy
	sf::Vector2u pozycja_na_planszy;
	
	//Pola do mozliwego ruchu
	vector<sf::Vector2u> pola_ruchu;

	//Sciezki ruchu (dla AI)
	vector<vector<sf::Vector2u>> paths;

	//Czy pionek jest ju¿ na polu docelowym
	bool is_win_pos;


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

	///sprawdza dostêpne pola ruchu
	void spr_zajetosc_sasiadow(sf::Vector2u, vector<sf::Vector2u>&, sf::Vector2u last = sf::Vector2u(10, 10),Kierunek kierunek = BRAK);
	
	///zwraca wspolrzedne z podanym offsetem
	static sf::Vector2u get_wsp(sf::Vector2u wsp, sf::Vector2i offset);

	///zwraca PoleSzachowe o podanych wspolrzednych z ewentualnym offsetem
	static Pole_szachowe* get_pole(sf::Vector2u wsp, sf::Vector2i offset = sf::Vector2i(0, 0));

	///sprawdza czy Pionek jest na wygranej pozycji
	bool is_win_position();
};
 
