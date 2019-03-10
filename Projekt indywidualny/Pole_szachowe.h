#pragma once
#include <SFML/Graphics.hpp>
#define WYSOKOSC 100
#define SZEROKOSC 100

class Pole_szachowe: public sf::RectangleShape
{
public:

	Pole_szachowe();
	~Pole_szachowe();

	sf::Vector2f PozycjaIkony;
	//Czy na polu stoi pion
	bool zajete;
	//ID Stojacego piona
	//unsigned char ID_Piona;


	///Uaktualnia  wspó³rzêdne po³o¿enia ikony na polu;
	void update();




};

