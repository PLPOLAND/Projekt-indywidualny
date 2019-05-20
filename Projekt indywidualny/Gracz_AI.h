#pragma once
#include "Gracz.h"
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

	int ruch_number;

public:



	Gracz_AI();
	~Gracz_AI();

	void ruch(unsigned char id_p, sf::Vector2u wsp);
	void tic(sf::Event& _event, sf::RenderWindow& window);
};