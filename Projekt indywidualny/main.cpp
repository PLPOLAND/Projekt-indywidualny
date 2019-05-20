#include <SFML/Graphics.hpp>

#include "Plansza.h"
#include "Gracz_Ludzki.h"
#include "Menu_List.h"
#include "Gracz_AI.h"

void graj() {
	cout << "Graj" << endl;
}
void info() {
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Skoczek");
	Menu_List menu(200, 40, 20, 0, 0);
	menu.dodajPrzycisk("Wyjdz");
	//menu.getPrzycisk(0)->setFunction();
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		menu.draw(window);
		window.display();
	}
	
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Skoczek");
	window.setFramerateLimit(60);

	
	Plansza plansza;
	Gracz_AI gracz1;
	Gracz_Ludzki gracz2;
	
	Menu_List menu(200,40,20,0,800);
	menu.dodajPrzycisk("Graj");
	menu.getPrzycisk(0)->setFunction(graj);
	menu.dodajPrzycisk("Info");
	menu.getPrzycisk(1)->setFunction(info);
	menu.setActive(0);

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
		}
		if (menu.activate == true) {
			menu.tic(event,window);
		}
		else
		{
			if (gracz2.czy_ruch == false)
			{
				gracz1.tic(event, window);
				if (gracz1.czy_ruch == false)
				{
					gracz2.czy_ruch = true;
				}
				gracz2.tic(event, window);
			}
			else
			{
				gracz2.tic(event, window);
				if (gracz1.czy_ruch == false)
				{
					gracz1.czy_ruch = true;
				}
			}
		}
		
		window.clear();
		menu.draw(window);
		plansza.draw(window);
		window.display();
	}
	
	return 0;
}