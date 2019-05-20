#include "Gracz_AI.h"
#include <conio.h>
#include <iostream>
#include "Plansza.h"
#include <fstream>
#include "Windows.h"
Gracz_AI::Gracz_AI():Gracz(), faza(ZAPROGRAMOWANA), ruchy(), ruch_number(0)
{
	cout << "Gracz" << endl;
	int num = 1; //numerek wariantu ruchów pocz¹tkowych
	//num = rand() % 2;//losowanie
	string path = "Zasoby/AI/"; //sciezka do pliku z ruchami
	path += '0'+num;
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
			//num = rand() % 2;//ponowne losowanie
		}
	}
	
	plik.close();
}


Gracz_AI::~Gracz_AI()
{
}

void Gracz_AI::ruch(unsigned char id_p, sf::Vector2u wsp)
{
	Plansza::move_P(this, id_p, wsp);
}

void Gracz_AI::tic(sf::Event& _event, sf::RenderWindow& window)
{
	if (faza == ZAPROGRAMOWANA)
	{
		Sleep(1000);
		sf::Vector2u tmp_wsp = ruchy[ruch_number]->wsp;
		if (Plansza::czy_pole_zajete(tmp_wsp))
		{
			faza = GRA;
		}
		else
		{
			this->ruch(ruchy[ruch_number]->id_p, ruchy[ruch_number]->wsp);
			this->czy_ruch = false;
		}
		this->ruch_number++;
		if (ruch_number >= ruchy.size())
		{
			faza = GRA;
		}
	}
	if (faza == GRA)
	{
		while (true) {
			;
		}
	}
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
