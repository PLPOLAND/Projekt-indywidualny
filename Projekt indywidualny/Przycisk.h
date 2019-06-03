#pragma once

#include <SFML/Graphics.hpp>
//#include <Text.hpp>
#include <string>

using namespace std;

class Przycisk : public sf::RectangleShape
{
private:
	sf::Text text;//text
	sf::Font font;//czcionka

	bool isActive; // czy przycisk jest Aktywny
	bool end; //czy wy³¹czyæ menu po aktywacji tego przycisku

	void(*funkcja)(); // wskaŸnik na funkcje wywo³ywan¹ przez przycisk

public:
	Przycisk(sf::Vector2f rozm, sf::Vector2f wspo = sf::Vector2f(0,0), int rozm_tex = 12, string text ="", bool endi = false);
	~Przycisk();
	///ustaw jako aktywny
	void setActive();
	///ustaw jako nie aktywny
	void setUnActive();
	///ustaw funkcje wykonywan¹ po "wcisnieciu" przyciska
	void setFunction(void(*fun)());

	///wykonaj funkcje
	void run();

	void draw(sf::RenderWindow& win);
	friend class Menu_List;
};

