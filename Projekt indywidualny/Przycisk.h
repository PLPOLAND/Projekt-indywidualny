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

	void(*funkcja)(); // wskaünik na funkcje wywo≥ywanπ przez przycisk

public:
	Przycisk(sf::Vector2f rozm, sf::Vector2f wspo = sf::Vector2f(0,0), int rozm_tex = 12, string text ="");
	~Przycisk();
	///ustaw jako aktywny
	void setActive();
	///ustaw jako nie aktywny
	void setUnActive();
	///ustaw funkcje wykonywanπ po "wcisnieciu" przyciska
	void setFunction(void(*fun)());

	///wykonaj funkcje
	void run();

	void draw(sf::RenderWindow& win);
};

