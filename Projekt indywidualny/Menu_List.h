#pragma once
#include <vector>
#include <algorithm>
#include "Przycisk.h"

using namespace std;

class Menu_List : public std::vector<Przycisk*>
{
private:
	float width;//szeroko�� przycisk�w
	float height;//wysoko�� przycisk�w
	int text_size;//rozmiar textu na przyciskach
	float top;//g�rna kraw�d� nastepnego przycisku
	float ftop;//g�rna kraw�d� g�rnego przycisku
	float left;//lewa kraw�d� przycisk�w
	
	
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

