#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

///////////////////////////////////////////////////
///Klasa przeznaczona do tworzenia obiektÛw 
///		wykorzystujacych tekstury
///////////////////////////////////////////////////

class element : public sf::Sprite
{
public:
	element();
	element(string t);	
	element(sf::Texture *t);

	~element();

	////////////////////////////////////////////////
	///Ustawia rozmiar obiektu w pikselach
	/// \arg 
	///		float x -> rozmiar w x
	///		float y -> rozmiar w y
	////////////////////////////////////////////////
	void set_size(float x, float y);

	////////////////////////////////////////////////
	///Zwraca wskaünik do przechowywanej tekstury
	/// \return sf::Texture *
	////////////////////////////////////////////////
	sf::Texture* get_Texture();

	sf::Texture *texture;

};

