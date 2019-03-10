#include "Plansza.h"

#include <iostream>

Pole_szachowe Plansza::pole[8][8];
vector<Pion *> Plansza::Pionki;

Plansza::Plansza()
{

	//Ustawienie i kolorowanie szachownicy
	float height = 0;
	for (int i = 0; i < 8; i++)
	{
		float width = 0;

		for (int j = 0; j < 8; j++)
		{

			
			pole[i][j].setPosition(sf::Vector2f(width,height));
			pole[i][j].update();
			if ((i+j)%2==0)
			{
				pole[i][j].setFillColor(sf::Color(255, 220, 185));
			}
			else
			{
				pole[i][j].setFillColor(sf::Color(233, 107, 57));
			}
			
			width += SZEROKOSC;
		}

		height += WYSOKOSC;
	}
	for (int i = 0; i < 32; i++)//Stworzenie pionków
	{
		Pionki.push_back(new Pion());
	}
	for_each(Pionki.begin(), Pionki.end(), [&](Pion* t) { t->setPosition(pole[t->pozycja_na_planszy[0]][t->pozycja_na_planszy[1]].PozycjaIkony); t->set_size(100, 100); pole[t->pozycja_na_planszy[0]][t->pozycja_na_planszy[1]].zajete = true; });//usawienie na plansy i ustawienie rozmiaru
}


Plansza::~Plansza()
{
}

///Rysowanie Planszy i pionków

void Plansza::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			window.draw(pole[i][j]);
		}
	}
	for_each(Pionki.begin(), Pionki.end(), [&](Pion* t) { window.draw(*t); });
}

///Przesuniecie pionka

void Plansza::move_P(Gracz * gracz, unsigned char ID, sf::Vector2u wsp)
{
	Pion *pionek;//stworzenie uchwytu na pionek

	auto pred = [&](Pion* pi) { if ((pi)->ID == ID) return true; else return false; };//predykator do poszukiwania pionka o zadanym ID

	pionek = *(find_if(Pionki.begin(), Pionki.end(), pred));//znalezienie odpowiedniego pionka i wy³uskanie go z kontenera

	if (gracz->ID!=pionek->wlasciciel)
	{
		//TODO
	}
	else
	{
		auto wsk = pole[wsp.x][wsp.y];//wskaŸnik na pole docelowe

		if (wsk.zajete==false)
		{
			cout << wsk.zajete;

			wsk.zajete = true;//zajêcie pola

			pole[pionek->pozycja_na_planszy[0]][pionek->pozycja_na_planszy[1]].zajete = false;//zwolnienie poprzedniego pola

			pionek->move(wsp);//zapisanie wspó³rzêdnych nowego pola

			pionek->setPosition(wsk.PozycjaIkony);//ustawienie wspó³rzêdnych do rysowania
			
			//cout << "Plansza::move_P" << endl;
			//cout << wsp.x << " " << wsp.y <<endl;
			//cout << wsk.PozycjaIkony.x <<" "<< wsk.PozycjaIkony.y<<endl;

		}
		else
		{
			cout << wsk.zajete;
			//TODO
		}
	}

}

sf::Vector2f Plansza::get_poz_pola(sf::Vector2u t)
{
	
	return pole[t.x][t.y].PozycjaIkony;
}
