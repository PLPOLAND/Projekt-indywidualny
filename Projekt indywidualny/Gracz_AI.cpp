#include "Gracz_AI.h"
#include <conio.h>
#include <iostream>
#include "Plansza.h"
#include <fstream>
#include "Windows.h"
Gracz_AI::Gracz_AI():Gracz(), faza(ZAPROGRAMOWANA), ruchy(), ruch_number(0), ending_path(), ending_pion(nullptr)
{
	cout << "Gracz" << endl;
	int num = 1; //numerek wariantu ruchów pocz¹tkowych
	num = rand() % 2;//losowanie
	string path = "Zasoby/AI/"; //sciezka do pliku z ruchami
	path += ('0'+num);
	path += ".moves";

	ifstream plik;
	
	while (true)
	{
		try
		{
			plik.open(path);
			while (!plik.eof())
			{
				string tmp;
				getline(plik, tmp);
				cout << path << endl;
				cout << tmp << endl;
				Gracz_AI::Ruch* tmp1 = new Gracz_AI::Ruch(tmp);
				ruchy.push_back(tmp1);
			}
			break;
		}
		catch (const std::exception& e)
		{
			cout << e.what();
			break;
			//num = rand() % 2;//ponowne losowanie
		}
	}
	plik.close();


	for (int i = 0; i < 8; i++)
	{
		pionki[i] = Plansza::Pionki[i];
	}
}


Gracz_AI::~Gracz_AI()
{
}

void Gracz_AI::ruch(unsigned char id_p, sf::Vector2u wsp, sf::RenderWindow& window)
{
	auto pion = Plansza::Pionki[id_p];
	auto pred = [&](sf::Vector2u vec) {
		Plansza::path(vec);
	};
	auto predu = [&](sf::Vector2u vec) {
		Plansza::unpath(vec);
	};

	for_each(pion->pola_ruchu.begin(), pion->pola_ruchu.end(), pred);
	window.clear();
	Plansza::draw(window);
	window.display();
	//Sleep(1500);
	for_each(pion->pola_ruchu.begin(), pion->pola_ruchu.end(), predu);
	
	Plansza::move_P(this, id_p, wsp);
}

void Gracz_AI::tic(sf::Event& _event, sf::RenderWindow& window)
{
	if (faza == ZAPROGRAMOWANA)
	{
		
		sf::Vector2u tmp_wsp = ruchy[ruch_number]->wsp;
		if (Plansza::czy_pole_zajete(tmp_wsp))
		{
			faza = GRA;
		}
		else
		{
			this->ruch(ruchy[ruch_number]->id_p, ruchy[ruch_number]->wsp,window);
			this->czy_ruch = false;
		}
		this->ruch_number++;
		if (ruch_number >= ruchy.size())
		{
			faza = GRA;
		}
	}
	else if (faza == GRA)
	{
		Pion* b_pionek = pionki[0];

		sf::Vector2u best_pole= sf::Vector2u(0,0);

		for (int i = 0; i < 8; i++)
		{
			/*if (pionki[i]->pozycja_na_planszy.y>5)
			{
				continue;
			}*/
			if (pionki[i]->is_win_pos)
			{
				continue;
			}
			else
			{
				sf::Vector2u pole_p = find_best_pole_dla_piona(pionki[i]);

				if (pole_p.y > best_pole.y)
				{
					best_pole = pole_p;
					b_pionek = pionki[i];
				}
			}
			

		}
		if (best_pole == sf::Vector2u(0,0))
		{
			faza = ZAKONCZENIE;
			this->czy_ruch = false;
		}
		else
		{
			unsigned char ID = Plansza::get_id_piona(b_pionek->pozycja_na_planszy);

			this->ruch(ID, best_pole, window);
			this->czy_ruch = false;
		}
		
	}
	if (faza==ZAKONCZENIE)
	{
		if (ending_path.size() == 0 || ending_pion == nullptr) {
			for (int i = 0; i < 8; i++)
			{
				if (pionki[i]->is_win_pos == false) {
					ending_pion = pionki[i];
					if (find_ending_path(ending_pion))
					{
						break;
					}
					else
					{
						continue;
					}
				}
			}
		}
		else
		{
			if (Plansza::czy_pole_zajete(ending_path[0])==true)
			{
				ending_path.clear();
			}
			else
			{
				ruch(ending_pion->ID, ending_path[0], window);
				ending_path.erase(ending_path.begin());
				this->czy_ruch = false;
			}
		}
	}
}

bool Gracz_AI::find_ending_path(Pion * pion)
{
	vector<sf::Vector2u> pola_k;//pola koñcowe na które trzeba dostarczyæ pionki
	sf::Vector2u pole;//Wybrane pole na które trzeba dostarczyæ piona


	if (Plansza::czy_pole_zajete(sf::Vector2u(0, 6)) == false)
	{
		pola_k.push_back(sf::Vector2u(0, 6));
	}
	if (Plansza::czy_pole_zajete(sf::Vector2u(1, 7)) == false)
	{
		pola_k.push_back(sf::Vector2u(1, 7));
	}
	if (Plansza::czy_pole_zajete(sf::Vector2u(2, 6)) == false)
	{
		pola_k.push_back(sf::Vector2u(2, 6));
	}
	if (Plansza::czy_pole_zajete(sf::Vector2u(3, 7)) == false)
	{
		pola_k.push_back(sf::Vector2u(3, 7));
	}
	if (Plansza::czy_pole_zajete(sf::Vector2u(4, 6)) == false)
	{
		pola_k.push_back(sf::Vector2u(4, 6));
	}
	if (Plansza::czy_pole_zajete(sf::Vector2u(5, 7)) == false)
	{
		pola_k.push_back(sf::Vector2u(5, 7));
	}
	if (Plansza::czy_pole_zajete(sf::Vector2u(6, 6)) == false)
	{
		pola_k.push_back(sf::Vector2u(6, 6));
	}
	if (Plansza::czy_pole_zajete(sf::Vector2u(7, 7)) == false)
	{
		pola_k.push_back(sf::Vector2u(7, 7));
	}
	if (pola_k.size()>0)
	{
		for (int i = 0; i < pola_k.size(); i++)
		{
			vector<sf::Vector2u> path = find_path_to(pion->pozycja_na_planszy, pola_k[i]);
			if (path.size() > 0)
			{
				ending_path = path;
			}
		}
	}
	else
	{
		if (pion->paths.size()>0)
		{
			ending_path = pion->paths[0];
		}
		else
		{
			return false;
		}
	}
	return true;
	

}




vector<sf::Vector2u> Gracz_AI::find_path_to(sf::Vector2u from, sf::Vector2u to)
{
	vector<sf::Vector2u> path;

	sf::Vector2u now = from;
	sf::Vector2u last = now;

	while (now!=to)
	{
		if (now.x-1 <= to.x) {
			if (Plansza::czy_pole_zajete(Pion::get_wsp(now,sf::Vector2i(1,-1))) == false && Pion::get_wsp(now, sf::Vector2i(1, -1)) != last)
			{
				last = now;
				now = Pion::get_wsp(now, sf::Vector2i(1, -1));
				path.push_back(now);
			}
			else if(Plansza::czy_pole_zajete(Pion::get_wsp(now, sf::Vector2i(1, 1))) == false && Pion::get_wsp(now, sf::Vector2i(1, 1)) != last)
			{
				last = now;
				now = Pion::get_wsp(now, sf::Vector2i(1, 1));
				path.push_back(now);
			}
			else
			{
				break;
			}
		}
		else
		{
			if (Plansza::czy_pole_zajete(Pion::get_wsp(now, sf::Vector2i(-1, -1))) == false && Pion::get_wsp(now, sf::Vector2i(-1, -1)) != last)
			{
				last = now;
				now = Pion::get_wsp(now, sf::Vector2i(-1, -1));
				path.push_back(now);
			}
			else if (Plansza::czy_pole_zajete(Pion::get_wsp(now, sf::Vector2i(-1, 1))) == false && Pion::get_wsp(now, sf::Vector2i(-1, 1)) != last)
			{
				last = now;
				now = Pion::get_wsp(now, sf::Vector2i(-1, 1));
				path.push_back(now);
			}
			else
			{
				break;
			}
		}
	}


	return path;
}

sf::Vector2u Gracz_AI::find_best_pole_dla_piona(Pion* pionek) {

	sf::Vector2u pole_b = sf::Vector2u(0, 0);
	for (int i = 0; i < pionek->paths.size() ; i++)
	{

		vector<sf::Vector2u> sciezka = pionek->paths[i];
		
		for (int i = 0; i < sciezka.size(); i++)
		{
			sf::Vector2u pole = sciezka[i];
			if (pole.y > pole_b.y && pole.y > pionek->pozycja_na_planszy.y)
			{
				pole_b = pole;
			}
		}
	}
	return pole_b;
}


Gracz_AI::Ruch::Ruch(string t)
{
	int x;
	int y;
	int x1;
	int y1;

	if (isdigit(t[0]))
	{
		x = t[0] - '0';
	}
	else
	{
		//cout << "Blad w danych wejsciowych AI" << endl;
		throw exception("Blad w danych wejsciowych AI");
	}
	if (isdigit(t[2]))
	{
		y = t[2] - '0';
	}
	else
	{
		//cout << "Blad w danych wejsciowych AI" << endl;		
		throw exception("Blad w danych wejsciowych AI");

	}
	if (isdigit(t[4]))
	{
		x1 = t[4] - '0';
	}
	else
	{
		//cout << "Blad w danych wejsciowych AI" << endl;
		throw exception("Blad w danych wejsciowych AI");

	}
	if (isdigit(t[6]))
	{
		y1 = t[6] - '0';
	}
	else
	{
		//cout << "Blad w danych wejsciowych AI" << endl;	
		throw exception("Blad w danych wejsciowych AI");

	}

	this->id_p = Plansza::get_id_piona(sf::Vector2u(x, y));
	this->wsp = sf::Vector2u(x1, y1);

}
