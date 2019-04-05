#include "Pion.h"
#include <iostream>
#include "Plansza.h"

unsigned char Pion::ID_P = 0;

Pion::Pion() : ID(ID_P++) {
	//Jeœli ID < 8 
	//pionek czarny gracz 
	//IDGracza 0

	//Pozycjonowanie
	if (ID < 8)
	{
		wlasciciel = 0;
		texture->loadFromFile("pion_czarny.png");
		this->setTexture(*texture);
		if (ID < 4)
		{
			pozycja_na_planszy.x = (ID % 4) * 2;
			pozycja_na_planszy.y = 0;
		}
		else
		{
			pozycja_na_planszy.x = (ID % 4) * 2 +1;
			pozycja_na_planszy.y = 1;
		}
	}
	else
	{
		wlasciciel = 1;

		texture->loadFromFile("pion.png");
		this->setTexture(*texture);

		if (ID < 12)
		{
			pozycja_na_planszy.x = (ID % 4) * 2;
			pozycja_na_planszy.y = 6;
		}
		else
		{
			pozycja_na_planszy.x = (ID % 4) * 2 + 1;
			pozycja_na_planszy.y = 7;
		}
	}

}

Pion::~Pion()
{
}

void Pion::move(sf::Vector2u & wspolrzedne)
{
	pozycja_na_planszy.x = wspolrzedne.x;
	pozycja_na_planszy.y = wspolrzedne.y;
	
	//cout << "Pion::Move " << (int)pozycja_na_planszy[0] << (int)pozycja_na_planszy[1] << endl;
}

void Pion::update()
{
	sf::Vector2u pozycja = this->pozycja_na_planszy;
	pola_ruchu.clear();
	spr_zajetosc_sasiadow(pozycja, pola_ruchu);



}

void Pion::spr_zajetosc_sasiadow(sf::Vector2u main, vector<sf::Vector2u>& pola, sf::Vector2u last)
{

	sf::Vector2u poz0 = last;
	sf::Vector2u poz1 = last;
	sf::Vector2u poz2 = last;
	sf::Vector2u poz3 = last;
	if (main.x - 1 >= 0 && main.x - 1 < 8 && main.y - 1 >= 0 && main.y - 1 < 8)
	{
		poz0 = sf::Vector2u(main.x - 1, main.y - 1);
	}	
	if (main.x - 1 >= 0 && main.x - 1 < 8 && main.y + 1 >= 0 && main.y + 1 < 8)
	{
		poz1 = sf::Vector2u(main.x - 1, main.y + 1);
	}	
	if (main.x + 1 >= 0 && main.x + 1 < 8 && main.y - 1 >= 0 && main.y - 1 < 8)
	{
		poz2 = sf::Vector2u(main.x + 1, main.y - 1);
	}	
	if (main.x + 1 >= 0 && main.x + 1 < 8 && main.y + 1 >= 0 && main.y + 1 < 8)
	{
		poz3 = sf::Vector2u(main.x + 1, main.y + 1);
	}

	bool poz0_2 = true; //przechowuje warunek czy pole "nastepne" jest nadal w planszy
	bool poz1_2 = true; //przechowuje warunek czy pole "nastepne" jest nadal w planszy
	bool poz2_2 = true; //przechowuje warunek czy pole "nastepne" jest nadal w planszy
	bool poz3_2 = true; //przechowuje warunek czy pole "nastepne" jest nadal w planszy

	if (poz0.x - 1 < 0 || poz0.y -1 <0)
	{
		poz0_2 = false;
	}
	if (poz1.x - 1 < 0 || poz1.y + 1 >7)
	{
		poz1_2 = false;
	}
	if (poz2.x + 1 >7 || poz2.y - 1 < 0)
	{
		poz2_2 = false;
	}
	if (poz3.x + 1 >7 || poz3.y + 1 >7)
	{
		poz3_2 = false;
	}



	sf::Vector2i poz0_offset = sf::Vector2i(-1, -1);
	sf::Vector2i poz1_offset = sf::Vector2i(-1, 1);
	sf::Vector2i poz2_offset = sf::Vector2i(1, -1);
	sf::Vector2i poz3_offset = sf::Vector2i(1, 1);



	auto pola_p = Plansza::pole; //uchwyt pomocniczy do pol

	bool czy_wsz_zaj0 = false;
	bool czy_wsz_zaj1 = false;
	bool czy_wsz_zaj2 = false;
	bool czy_wsz_zaj3 = false;
	
	//TODO Naprawic!!! WYWALA PROGRAM!

	/////////////////TMP/////////////////////

	auto get_pole = [&pola_p](sf::Vector2u wsp, sf::Vector2i offset = sf::Vector2i(0,0)) {
		return pola_p[wsp.x - offset.x][wsp.y - offset.y];
	};

	auto get_wsp = [](sf::Vector2u wsp, sf::Vector2i offset) {
		sf::Vector2u tmp(0,0);
		tmp.x = wsp.x + offset.x;
		tmp.y = wsp.y + offset.y;
		return tmp;
	};

	if (poz0 != last && get_pole(poz0).zajete == false )
	{
		pola.push_back(poz0);
	}
	else if (poz0 != last && poz0_2 == true && get_pole(poz0, poz0_offset).zajete == false)
	{
		spr_zajetosc_sasiadow(get_wsp(poz0, poz0_offset), pola, poz0);
	}
	else
	{
		czy_wsz_zaj0 = true;
	}

	if (poz1 != last && get_pole(poz1).zajete == false)
	{
		pola.push_back(poz1);
	}
	else if (poz1 != last && poz1_2 == true && get_pole(poz1, poz1_offset).zajete == false)
	{
		spr_zajetosc_sasiadow(get_wsp(poz1, poz1_offset), pola, poz1);
	}
	else
	{
		czy_wsz_zaj1 = true;
	}

	if (poz2 != last && get_pole(poz2).zajete == false)
	{
		pola.push_back(poz2);
	}
	else if (poz2 != last && poz2_2 == true && get_pole(poz2, poz2_offset).zajete == false)
	{
		spr_zajetosc_sasiadow(get_wsp(poz2, poz2_offset), pola, poz2);
	}
	else
	{
		czy_wsz_zaj2 = true;
	}

	if (poz3 != last && get_pole(poz3).zajete == false)
	{
		pola.push_back(poz3);
	}
	else if (poz3 != last && poz3_2 == true && get_pole(poz3, poz3_offset).zajete == false)
	{
		spr_zajetosc_sasiadow(get_wsp(poz3, poz3_offset), pola, poz3);
	}
	else
	{
		czy_wsz_zaj3 = true;
	}

	if (czy_wsz_zaj0 == true && czy_wsz_zaj1 == true && czy_wsz_zaj2 == true && czy_wsz_zaj3 == true)
	{
		pola.push_back(main);
	}
	/////////////////\TMP/////////////////////




	/*if ((poz0.x) >= 0 && (poz0.y) >= 0 && (poz0.x) < 8 && (poz0.y) < 8)
	{
		if (!pola_p[poz0.x][poz0.y].zajete)
		{
			pola.push_back(poz0);
		}
		else if (!pola_p[poz0.x - 1][poz0.y - 1].zajete && poz0 != last)
		{
			spr_zajetosc_sasiadow(sf::Vector2u(poz0.x - 1, poz0.y - 1), pola, main);
		}
	}
	else
	{
		czy_wsz_zaj0 = true;
	}

	if ((poz1.x) >= 0 && (poz1.y) >= 0 && (poz1.x) < 8 && (poz1.y) < 8)
	{
		if (!pola_p[poz1.x][poz1.y].zajete) {
			pola.push_back(poz1);
		}
		else if (((poz1.x) > 0 && (poz1.y) > 0 && (poz1.x) < 8 && (poz1.y) < 8) && !pola_p[poz1.x - 1][poz1.y + 1].zajete && poz1 != last)
		{
			spr_zajetosc_sasiadow(sf::Vector2u(poz1.x - 1, poz1.y + 1), pola, main);
		}
	}
	else
	{
		czy_wsz_zaj1 = true;
	}
	
	if ((poz2.x) >= 0 && (poz2.y) >= 0 && (poz2.x) < 8 && (poz2.y) < 8)
	{
		if (!pola_p[poz2.x][poz2.y].zajete) {
			pola.push_back(poz2);
		}
		else if (!pola_p[poz2.x + 1][poz2.y - 1].zajete && poz2 != last)
		{
			spr_zajetosc_sasiadow(sf::Vector2u(poz2.x + 1, poz2.y - 1), pola, main);
		}
		
	}
	else
	{
		czy_wsz_zaj2 = true;
	}
	
	
	if ((poz3.x) >= 0 && (poz3.y) >= 0 && (poz3.x) < 8 && (poz3.y) < 8)
	{
		if (!pola_p[poz3.x][poz3.y].zajete) {
			pola.push_back(poz3);
		}
		else if (!pola_p[poz3.x + 1][poz3.y + 1].zajete && poz2 != last)
		{
			spr_zajetosc_sasiadow(sf::Vector2u(poz3.x + 1, poz3.y + 1), pola, main);
		}
		
	}
	else
	{
		czy_wsz_zaj3 = true;
	}
	

	if (czy_wsz_zaj0 && czy_wsz_zaj1 && czy_wsz_zaj2 && czy_wsz_zaj3 && last != sf::Vector2u(10, 10))
	{
		pola.push_back(main);
	}*/


}
