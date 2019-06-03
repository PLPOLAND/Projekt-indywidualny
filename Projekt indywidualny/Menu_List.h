#pragma once
#include <vector>
#include <algorithm>
#include "Przycisk.h"

using namespace std;

class Menu_List : public std::vector<Przycisk*>
{
private:
	float width;//szerokoœæ przycisków
	float height;//wysokoœæ przycisków
	int text_size;//rozmiar textu na przyciskach
	float top;//górna krawêdŸ nastepnego przycisku
	float ftop;//górna krawêdŸ górnego przycisku
	float left;//lewa krawêdŸ przycisków
	
	
	int active;


public:
	bool activate;

	Menu_List(float width, float height, int text_size, float top, float left);
	~Menu_List();

	void dodajPrzycisk(string t, bool czy_end = false);
	Przycisk* getPrzycisk(int i);
	void draw(sf::RenderWindow& window);
	void setActive(int i);
	void unsetActive(int i);
	void tic(sf::Event& _event, sf::RenderWindow& window);

	void clear();
};

