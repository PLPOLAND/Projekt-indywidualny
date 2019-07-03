#pragma once
#include "Gracz.h"
#include "Pion.h"
#include <vector>
#include <algorithm>
#include <string>
#include "Menu_List.h"

using namespace std;

class Gracz_AI : public Gracz
{
	enum faza_ruchu {
		ZAPROGRAMOWANA,
		GRA,
		ZAKONCZENIE
	};

	faza_ruchu faza;
	
	struct Ruch
	{
	public:
		Ruch(string t);

		sf::Vector2u from;
		sf::Vector2u to;
	};

	vector<Gracz_AI::Ruch*> ruchy;
	
	Pion* pionki[8];

	int ruch_number;

	vector<sf::Vector2u> ending_path;
	Pion* ending_pion;


public:



	Gracz_AI();
	~Gracz_AI();

	void ruch(unsigned char id_p, sf::Vector2u wsp, sf::RenderWindow& window, Menu_List& menu);

	sf::Vector2u find_best_pole_dla_piona(Pion* pionek);

	bool czy_poprawne_wsp(int x, int y);
	bool czy_bylo(vector<sf::Vector2u>& path, sf::Vector2u t); 
	bool find_better_path(int tab[8][8], vector<sf::Vector2u>& path, vector<sf::Vector2u>& path_tmp, sf::Vector2u from, sf::Vector2u to, sf::Vector2u last = sf::Vector2u(0, 0));
	bool preffer_right_path(int tab[8][8], vector<sf::Vector2u>& path, vector<sf::Vector2u>& path_tmp, sf::Vector2u from, sf::Vector2u to, sf::Vector2u last = sf::Vector2u(0, 0));
	bool preffer_left_path(int tab[8][8], vector<sf::Vector2u>& path, vector<sf::Vector2u>& path_tmp, sf::Vector2u from, sf::Vector2u to, sf::Vector2u last = sf::Vector2u(0,0));
	bool path(vector<sf::Vector2u> & path, int tab[8][8], sf::Vector2u from, sf::Vector2u to, sf::Vector2u last = sf::Vector2u(0, 0));

	void tic(sf::Event& _event, sf::RenderWindow& window, Menu_List&);
	bool find_ending_path(Pion*);


};