#include <SFML/Graphics.hpp>

#include "Plansza.h"
#include "Gracz_Ludzki.h"
#include "Menu_List.h"
#include "Gracz_AI.h"

void graj() {
	//cout << "Graj" << endl;
}
void info() {
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Skoczek");
	sf::Texture tx;
	tx.loadFromFile("Zasoby/info.png");
	element el;
	el.setTexture(tx);
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				window.close();
			}
		}
		window.clear();
		window.draw(el);
		window.display();
	}
	
}

void okno_powitalne() {
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Skoczek");
	sf::Texture tx;
	tx.loadFromFile("Zasoby/powitac.png");
	element el;
	el.setTexture(tx);
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				window.close();
			}
		}
		window.clear();
		window.draw(el);
		window.display();
	}

}

int main()
{
	okno_powitalne();

	sf::RenderWindow window(sf::VideoMode(1050, 800), "Skoczek");
	window.setFramerateLimit(60);
	
	Plansza plansza;
	Gracz_AI gracz1;
	Gracz_Ludzki gracz2;

	gracz1.czy_ruch = false;
	gracz2.czy_ruch = true;
	
	Menu_List menu(250,40,20,0,800);
	menu.dodajPrzycisk("Graj", true);
	menu.getPrzycisk(0)->setFunction(graj);
	menu.dodajPrzycisk("Info");
	menu.getPrzycisk(1)->setFunction(info);
	menu.setActive(0);

	plansza.print();
	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (menu.activate == true) {
			menu.tic(event,window);
		}
		else
		{
			menu.clear();
			if (gracz2.czy_ruch == false)
			{
				gracz1.tic(event, window);
				if (gracz1.czy_ruch == false)
				{
					gracz2.czy_ruch = true;
				}
			}
			else
			{
				gracz2.tic(event, window);
				if (gracz1.czy_ruch == false)
				{
					gracz1.czy_ruch = true;
				}
			}
			int wygrany = plansza.who_win();
			if (wygrany == 0)
			{
				menu.activate = true;
				menu.dodajPrzycisk("Wygral Gracz Czarny");
			}
			else if (wygrany == 1)
			{
				menu.activate = true;
				menu.dodajPrzycisk("Wygral Gracz Bialy");
			}
		}
		window.clear();
		menu.draw(window);
		plansza.draw(window);
		window.display();
	}
	
	return 0;
}