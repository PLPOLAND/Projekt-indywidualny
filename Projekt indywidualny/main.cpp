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
	okno_powitalne();//Wy�wietl okno powitalne

	sf::RenderWindow window(sf::VideoMode(1050, 800), "Skoczek");	//otworzenie okna o rozdzielczo�ci 
																	//1050x800px i nazwie tytuowej "Skoczek"
	window.setFramerateLimit(60);//ustawienie limitu klatek na 60/s
	
	Plansza plansza;
	Gracz_AI gracz1;
	Gracz_Ludzki gracz2;

	gracz1.czy_ruch = false;
	gracz2.czy_ruch = true;//Gracz ludzki rusz si� jako pierwszy.
	
	Menu_List menu(250,40,20,0,800);//zainicjuj menu na wsp�rz�dnych (800,0) rozmiarze tekstu 20 i rozmiarze 
									//przycisku 250x40px
	menu.dodajPrzycisk("Graj", true); //dodaj przycisk kt�ry po wybraniu wyczy�ci i deaktywuje menu
	menu.getPrzycisk(0)->setFunction(graj);//dodaj funkcje dla przycisku "Graj"
	menu.dodajPrzycisk("Info"); //dodaj przycisk
	menu.getPrzycisk(1)->setFunction(info);//dodaj funkcje dla przycisku "Info"
	menu.setActive(0);//ustaw przycisk "Graj" jako aktywny

	while (window.isOpen())//dop�ki nie zamkni�to okna
	{
		
		sf::Event event;
		while (window.pollEvent(event))//pobierz eventy systemowe
		{
			if (event.type == sf::Event::Closed)//czy poproszono o zmkni�cie okna
				window.close();//zamknij okno
		}

		if (menu.activate == true) {
			menu.tic(event,window);//obs�� menu
		}
		else if(plansza.who_win() == -1)//je�li nikt nie zaj�� pozycji wygranej
		{
			menu.clear();
			if (gracz2.czy_ruch == false)//je�li nie ruch gracza ludzkiego
			{
				gracz1.tic(event, window, menu);//wywo�aj metod� obs�uguj�c� gracza AI
				if (gracz1.czy_ruch == false)//Je�li wykonano ruch
				{
					gracz2.czy_ruch = true;//ustaw kolej gracza ludzkiego
				}
			}
			else//je�li ruch gracza ludzkiego
			{
				gracz2.tic(event, window, menu);
				if (gracz1.czy_ruch == false)
				{
					gracz1.czy_ruch = true;
				}
			}
			
		}
		else
		{
			int wygrany = plansza.who_win();
			if (wygrany == 0 && menu.isEmpty())
			{
				menu.activate = false;
				menu.dodajPrzycisk("Wygral Gracz Czarny");
			}
			else if (wygrany == 1 && menu.isEmpty())
			{
				menu.activate = false;
				menu.dodajPrzycisk("Wygral Gracz Bialy");
			}
			else if (wygrany == 2 && menu.size()==1) {
				menu.activate = false;
				menu.dodajPrzycisk("Wynik:");
				string t = to_string(gracz2.wynik);
				menu.dodajPrzycisk(t);
			}

			if (wygrany == 0)//je�li pozycj� wygran� zaj�� gracz AI
			{
				gracz2.clearMove();
				gracz2.tic(event, window, menu); 
				if (gracz2.wasMove() == true)
				{
					gracz2.wynik -= 1;
				}
			}
			else if(wygrany == 1)//je�li pozycj� wygran� zaj�� gracz ludzki
			{
				gracz1.clearMove();
				gracz1.tic(event, window, menu);
				if (gracz1.wasMove() == true)
				{
					gracz2.wynik += 1;
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
