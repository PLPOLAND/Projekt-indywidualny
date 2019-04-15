#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#define WYSOKOSC 100
#define SZEROKOSC 100

class Pole_szachowe: public sf::RectangleShape
{
public:

	Pole_szachowe();
	~Pole_szachowe();

	static const sf::Color kolor_cz;
	static const sf::Color kolor_b;
	static const sf::Color kolor_trigg;
	static const sf::Color kolor_path;

	//Pozycja drukowania pionka na polu
	sf::Vector2f PozycjaIkony;

	//Czy na polu stoi pion
	bool zajete;
	
	//Czy pole jest zaznaczone przez gracza
	bool aktywne;

	//Czy pole jest oznaczone jako pole ruchu
	bool czy_ruch;

	//Kolor pola na planszy
	enum Kolor_Pola
	{
		CZARNY,
		BIALY
	};
	Kolor_Pola kolor;


	struct Flags
	{
		Flags();
		bool false_all();
		bool trig;
		bool path;
	};

	Flags flagi;
	///Uaktualnia  wspó³rzêdne po³o¿enia ikony na polu;
	void update();

	///Ustawia kolor pola
	void set_kolor(Kolor_Pola);

	///Zaznacz pole
	void set_trigg();
	///Odznacz pole
	void unset_trigg();
	///Czy pole jest zaznaczone
	bool get_trigg();

	///Zaznacz jako pole ruchu
	void set_path();
	///Odznacz oznaczenie jako pole ruchu
	void unset_path();
	
	///Kolorowanie
	void koloruj();
};

