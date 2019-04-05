#include <SFML/Graphics.hpp>

#include "Plansza.h"
#include "Gracz_Ludzki.h"
//#include "Pion.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Skoczek");
	window.setFramerateLimit(60);

	Plansza plansza;
	Gracz_Ludzki tmp;
	
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
		tmp.tic(event,window);
		window.clear();
		plansza.draw(window);
		window.display();
	}

	return 0;
}