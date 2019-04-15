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

		for (int j = 0; j <8; j++)
		{
			pole[j][i].setPosition(sf::Vector2f(width, height));
			pole[j][i].update();

			if ((i+j)%2==0)//Jesli suma indexów jest parzysta to ustaw kolor pola na bia³y
			{
				pole[j][i].set_kolor(Pole_szachowe::BIALY);
			}
			else
			{
				pole[j][i].set_kolor(Pole_szachowe::CZARNY);
			}
			
			width += SZEROKOSC;
		}

		height += WYSOKOSC;
	}
	for (int i = 0; i < 16; i++)//Stworzenie pionków
	{
		Pionki.push_back(new Pion());
	}
	cout << "piony" << endl;
	for_each(Pionki.begin(), Pionki.end(), [&](Pion* t) { 
		t->setPosition(pole[t->pozycja_na_planszy.x][t->pozycja_na_planszy.y].PozycjaIkony);
		t->set_size(100, 100); 
		pole[t->pozycja_na_planszy.x][t->pozycja_na_planszy.y].zajete = true; 
		});//ustawienie na plansy i ustawienie rozmiaru
	Plansza::print();
	Plansza::update_p();
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
		auto wsk = &pole[wsp.x][wsp.y];//wskaŸnik na pole docelowe

		if (wsk->zajete==false)
		{
			wsk->zajete = true;//zajêcie pola

			pole[pionek->pozycja_na_planszy.x][pionek->pozycja_na_planszy.y].zajete = false;//zwolnienie poprzedniego pola

			pionek->move(wsp);//zapisanie wspó³rzêdnych nowego pola

			pionek->setPosition(wsk->PozycjaIkony);//ustawienie wspó³rzêdnych do rysowania
			
			Plansza::update_p();


		}
		else
		{
			cout << "Pole "<< wsp.x<<" "<< wsp.y  << " jest zajete"<< endl;
			//TODO
		}
	}
	
}

void Plansza::trigg(sf::Vector2u t)
{
	pole[t.x][t.y].set_trigg();
}

void Plansza::untrigg(sf::Vector2u t)
{
	pole[t.x][t.y].unset_trigg();
}

void Plansza::path(sf::Vector2u t)
{
	pole[t.x][t.y].set_path();
}

void Plansza::unpath(sf::Vector2u t)
{
	pole[t.x][t.y].unset_path();
}

sf::Vector2f Plansza::get_poz_pola(sf::Vector2u t)
{
	
	return pole[t.x][t.y].PozycjaIkony;
}

bool Plansza::czy_pionek_nalezy(sf::Vector2u kordynaty, Gracz* gracz)
{
	
	if (czy_pole_zajete(kordynaty) == false)
	{
		return false;
	}
	
	
	Pion* pionek;
	auto pred = [&](Pion* pion) { 
		if (pion->pozycja_na_planszy.x == kordynaty.x && pion->pozycja_na_planszy.y == kordynaty.y) {
			return true;
		}
		else
			return false;
	};
	
	pionek = *(find_if(Pionki.begin(), Pionki.end(), pred));//znalezienie odpowiedniego pionka i wy³uskanie go z vektora

	
	if (pionek == nullptr)
	{
		return false;
	}

	if (pionek->wlasciciel == gracz->ID)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Plansza::czy_pole_zajete(sf::Vector2u kordynaty)
{
	if (pole[kordynaty.x][kordynaty.y].zajete==true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Plansza::get_id_piona(sf::Vector2u kordynaty)
{
	Pion* pionek;
	auto pred = [&](Pion* pion) {
		if (pion->pozycja_na_planszy.x == kordynaty.x && pion->pozycja_na_planszy.y == kordynaty.y) {
			return true;
		}
		else
			return false;
	};

	pionek = *(find_if(Pionki.begin(), Pionki.end(), pred));

	if (pionek != nullptr){
		return pionek->ID;
	}
	else {//TODO:
		return -1;
	}
}

void Plansza::update_p()
{
	for_each(Pionki.begin(), Pionki.end(), [&](Pion* t) {
		t->update();
	});//usawienie na plansy i ustawienie rozmiaru
}

Pion* Plansza::get_pion(sf::Vector2u kordynaty)
{
	auto pred = [&](Pion* pion) {
		if (pion->pozycja_na_planszy.x == kordynaty.x && pion->pozycja_na_planszy.y == kordynaty.y) {
			return true;
		}
		else
			return false;
	};

	return *(find_if(Pionki.begin(), Pionki.end(), pred));
}

void Plansza::print()
{

	for (int i = 0; i < 8; i++)
	{
		cout << i << " ";
		for (int j = 0; j < 8; j++)
		{
			cout << pole[i][j].zajete << " ";
		}
		cout << endl;
	}

}
