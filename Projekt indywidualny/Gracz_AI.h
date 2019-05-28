#pragma once
#include "Gracz.h"
#include "Pion.h"
#include <vector>
#include <algorithm>
#include <string>

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

		unsigned char id_p;
		sf::Vector2u wsp;
	};

	vector<Gracz_AI::Ruch*> ruchy;
	
	Pion* pionki[8];

	int ruch_number;

	vector<sf::Vector2u> ending_path;
	Pion* ending_pion;

public:



	Gracz_AI();
	~Gracz_AI();

	void ruch(unsigned char id_p, sf::Vector2u wsp, sf::RenderWindow& window);
	sf::Vector2u find_best_pole_dla_piona(Pion* pionek);
	void tic(sf::Event& _event, sf::RenderWindow& window);
	bool find_ending_path(Pion*);
	vector<sf::Vector2u> find_path_to(sf::Vector2u from, sf::Vector2u to);


};