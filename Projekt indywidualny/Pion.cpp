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
	paths.clear();
	spr_zajetosc_sasiadow(pozycja, pola_ruchu);



}

void Pion::spr_zajetosc_sasiadow(sf::Vector2u main, vector<sf::Vector2u>& pola, sf::Vector2u last,Kierunek hop)
{
	static vector<sf::Vector2u> tmp_path;
	static int tmp_path_iter = (int)tmp_path.size() - 1;
	if (hop == BRAK)
	{
		tmp_path.clear();
		tmp_path_iter = (int)tmp_path.size() - 1;
	}
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

	bool poz0_2 = true; //
	bool poz1_2 = true; //
	bool poz2_2 = true; //
	bool poz3_2 = true; //

	if ((int)poz0.x - 1 < 0 || (int)poz0.y -1 <0 || poz0==last || hop == LG)
	{
		poz0_2 = false;
	}
	if ((int)poz1.x - 1 < 0 || (int)poz1.y + 1 >7 || poz1 == last || hop == LD)
	{
		poz1_2 = false;
	}
	if ((int)poz2.x + 1 >7 || (int)poz2.y - 1 < 0 || poz2 == last || hop == RG)
	{
		poz2_2 = false;
	}
	if ((int)poz3.x + 1 >7 || (int)poz3.y + 1 >7 || poz3 == last || hop == RD)
	{
		poz3_2 = false;
	}



	sf::Vector2i poz0_offset = sf::Vector2i(-1, -1);
	sf::Vector2i poz1_offset = sf::Vector2i(-1, 1);
	sf::Vector2i poz2_offset = sf::Vector2i(1, -1);
	sf::Vector2i poz3_offset = sf::Vector2i(1, 1);



	bool czy_wsz_zaj0 = false;
	bool czy_wsz_zaj1 = false;
	bool czy_wsz_zaj2 = false;
	bool czy_wsz_zaj3 = false;
	

	if (poz0 != last && get_pole(poz0)->zajete == false && hop == BRAK)
	{
		pola.push_back(poz0);

		tmp_path.push_back(poz0);
		paths.push_back(tmp_path);
		tmp_path.clear();
	}
	else if (poz0 != last && poz0_2 == true && get_pole(poz0)->zajete == true && get_pole(poz0, poz0_offset)->zajete == false)
	{
		if (pola.end() == find(pola.begin(),pola.end(),get_wsp(poz0, poz0_offset)) || pola.size() == 0)
		{
			pola.push_back(get_wsp(poz0, poz0_offset));
			tmp_path.push_back(get_wsp(poz0, poz0_offset));
			tmp_path_iter++;
		}
		else
		{
			return;
		}


		spr_zajetosc_sasiadow(get_wsp(poz0, poz0_offset), pola, poz0, RD);
		for (int i = tmp_path.size()-1 ; i >= tmp_path_iter; i--)
		{
			tmp_path.erase(tmp_path.begin() + i);
		}
		tmp_path_iter--;
	}
	else
	{
		czy_wsz_zaj0 = true;
	}

	if (poz1 != last && get_pole(poz1)->zajete == false && hop == BRAK)
	{
		pola.push_back(poz1);

		tmp_path.push_back(poz1);
		paths.push_back(tmp_path);
		tmp_path.clear();
	}
	else if (poz1 != last && poz1_2 == true && get_pole(poz1)->zajete == true && get_pole(poz1, poz1_offset)->zajete == false)
	{
		if (pola.end() == find(pola.begin(),pola.end(), get_wsp(poz1, poz1_offset)) || pola.size() == 0)
		{
			pola.push_back(get_wsp(poz1, poz1_offset));
			tmp_path.push_back(get_wsp(poz1, poz1_offset));
			tmp_path_iter++;
		}
		else
		{
			return;
		}


		spr_zajetosc_sasiadow(get_wsp(poz1, poz1_offset), pola, poz1, RG);

		for (int i = tmp_path.size()-1; i >= tmp_path_iter; i--)
		{
			tmp_path.erase(tmp_path.begin() + i);
		}
		tmp_path_iter--;
	}
	else
	{
		czy_wsz_zaj1 = true;
	}

	if (poz2 != last && get_pole(poz2)->zajete == false && hop == BRAK)
	{
		pola.push_back(poz2);

		tmp_path.push_back(poz2);
		paths.push_back(tmp_path);
		tmp_path.clear();
	}
	else if (poz2 != last && poz2_2 == true && get_pole(poz2)->zajete == true && get_pole(poz2, poz2_offset)->zajete == false)
	{
		if (pola.end() == find(pola.begin(), pola.end(), get_wsp(poz2, poz2_offset)) || pola.size() == 0)
		{
			pola.push_back(get_wsp(poz2, poz2_offset));
			tmp_path.push_back(get_wsp(poz2, poz2_offset));
			tmp_path_iter++;
		}
		else
		{
			return;
		}


		spr_zajetosc_sasiadow(get_wsp(poz2, poz2_offset), pola, poz2, LD);

		for (int i = tmp_path.size()-1; i >= tmp_path_iter; i--)
		{
			tmp_path.erase(tmp_path.begin() + i);
		}
		tmp_path_iter--;
	}
	else
	{
		czy_wsz_zaj2 = true;
	}

	if (poz3 != last && get_pole(poz3)->zajete == false && hop == BRAK)
	{
		pola.push_back(poz3);

		tmp_path.push_back(poz3);
		paths.push_back(tmp_path);
		tmp_path.clear();
	}
	else if (poz3 != last && poz3_2 == true && get_pole(poz3)->zajete == true && get_pole(poz3, poz3_offset)->zajete == false)
	{
		if (pola.end() == find(pola.begin(), pola.end(), get_wsp(poz3, poz3_offset)) || pola.size() == 0)
		{
			pola.push_back(get_wsp(poz3, poz3_offset));

			tmp_path.push_back(get_wsp(poz3, poz3_offset));
			tmp_path_iter++;

		}
		else
		{
			return;
		}

		spr_zajetosc_sasiadow(get_wsp(poz3, poz3_offset), pola, poz3, LG);

		for (int i = tmp_path.size()-1; i >= tmp_path_iter; i--)
		{
			tmp_path.erase(tmp_path.begin() + i);
		}
		tmp_path_iter--;

	}
	else
	{
		czy_wsz_zaj3 = true;
	}

	if (czy_wsz_zaj0 == true && czy_wsz_zaj1 == true && czy_wsz_zaj2 == true && czy_wsz_zaj3 == true)
	{
		paths.push_back(tmp_path);
	}
}
void Pion::spr_zajetosc_sasiadow2(sf::Vector2u main, vector<sf::Vector2u>& pola, sf::Vector2u last, Kierunek hop)
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

	bool poz0_2 = true; //
	bool poz1_2 = true; //
	bool poz2_2 = true; //
	bool poz3_2 = true; //

	if ((int)poz0.x - 1 < 0 || (int)poz0.y - 1 < 0 || poz0 == last || hop == LG)
	{
		poz0_2 = false;
	}
	if ((int)poz1.x - 1 < 0 || (int)poz1.y + 1 > 7 || poz1 == last || hop == LD)
	{
		poz1_2 = false;
	}
	if ((int)poz2.x + 1 > 7 || (int)poz2.y - 1 < 0 || poz2 == last || hop == RG)
	{
		poz2_2 = false;
	}
	if ((int)poz3.x + 1 > 7 || (int)poz3.y + 1 > 7 || poz3 == last || hop == RD)
	{
		poz3_2 = false;
	}



	sf::Vector2i poz0_offset = sf::Vector2i(-1, -1);
	sf::Vector2i poz1_offset = sf::Vector2i(-1, 1);
	sf::Vector2i poz2_offset = sf::Vector2i(1, -1);
	sf::Vector2i poz3_offset = sf::Vector2i(1, 1);



	bool czy_wsz_zaj0 = false;
	bool czy_wsz_zaj1 = false;
	bool czy_wsz_zaj2 = false;
	bool czy_wsz_zaj3 = false;


	if (poz0 != last && get_pole(poz0)->zajete == false && hop == BRAK)
	{
		pola.push_back(poz0);
	}
	else if (poz0 != last && poz0_2 == true && get_pole(poz0)->zajete == true && get_pole(poz0, poz0_offset)->zajete == false)
	{
		pola.push_back(get_wsp(poz0, poz0_offset));
		spr_zajetosc_sasiadow(get_wsp(poz0, poz0_offset), pola, poz0, RD);
	}
	else
	{
		czy_wsz_zaj0 = true;
	}

	if (poz1 != last && get_pole(poz1)->zajete == false && hop == BRAK)
	{
		pola.push_back(poz1);
	}
	else if (poz1 != last && poz1_2 == true && get_pole(poz1)->zajete == true && get_pole(poz1, poz1_offset)->zajete == false)
	{
		pola.push_back(get_wsp(poz1, poz1_offset));
		spr_zajetosc_sasiadow(get_wsp(poz1, poz1_offset), pola, poz1, RG);
	}
	else
	{
		czy_wsz_zaj1 = true;
	}

	if (poz2 != last && get_pole(poz2)->zajete == false && hop == BRAK)
	{
		pola.push_back(poz2);
	}
	else if (poz2 != last && poz2_2 == true && get_pole(poz2)->zajete == true && get_pole(poz2, poz2_offset)->zajete == false)
	{
		pola.push_back(get_wsp(poz2, poz2_offset));
		spr_zajetosc_sasiadow(get_wsp(poz2, poz2_offset), pola, poz2, LD);
	}
	else
	{
		czy_wsz_zaj2 = true;
	}

	if (poz3 != last && get_pole(poz3)->zajete == false && hop == BRAK)
	{
		pola.push_back(poz3);
	}
	else if (poz3 != last && poz3_2 == true && get_pole(poz3)->zajete == true && get_pole(poz3, poz3_offset)->zajete == false)
	{
		pola.push_back(get_wsp(poz3, poz3_offset));
		spr_zajetosc_sasiadow(get_wsp(poz3, poz3_offset), pola, poz3, LG);
	}
	else
	{
		czy_wsz_zaj3 = true;
	}

	if (czy_wsz_zaj0 == true && czy_wsz_zaj1 == true && czy_wsz_zaj2 == true && czy_wsz_zaj3 == true)
	{
		pola.push_back(main);
	}

}

sf::Vector2u Pion::get_wsp(sf::Vector2u wsp, sf::Vector2i offset) {
	sf::Vector2u tmp(0, 0);
	tmp.x = wsp.x + offset.x;
	tmp.y = wsp.y + offset.y;
	return tmp;
};

Pole_szachowe* Pion::get_pole(sf::Vector2u wsp, sf::Vector2i offset) {
	
	if (wsp.x + offset.x >= 0 && wsp.x + offset.x < 8 && wsp.y + offset.y >= 0 && wsp.y + offset.y < 8)
	{

		return &Plansza::pole[wsp.x + offset.x][wsp.y + offset.y];
	}
	else
	{
		cout << "Blad";
		return &Plansza::pole[0][0];
	}
};