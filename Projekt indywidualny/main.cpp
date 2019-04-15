#include <SFML/Graphics.hpp>

#include "Plansza.h"
#include "Gracz_Ludzki.h"
//#include "Pion.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Skoczek");
	window.setFramerateLimit(60);

	Plansza plansza;
	Gracz_Ludzki gracz1;
	Gracz_Ludzki gracz2;
	
	plansza.print();
	while (window.isOpen())
	{
		//auto t = plansza.pole[0][0];
		auto p = plansza.Pionki;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
			}
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				tmp.ruch(0, sf::Vector2u(0,1));
			}*/
		}
		if (gracz1.czy_ruch == false)
		{
			gracz2.tic(event, window);
			if (gracz2.czy_ruch == false)
			{
				gracz1.czy_ruch = true;
			}
		}
		else
		{
			gracz1.tic(event, window);
			if (gracz1.czy_ruch == false)
			{
				gracz2.czy_ruch = true;
			}
		}
		window.clear();
		plansza.draw(window);
		window.display();
	}

	return 0;
}