#include "Gracz_AI.h"
#include <conio.h>
#include <iostream>
#include "Plansza.h"
#include <fstream>
#include "Windows.h"
Gracz_AI::Gracz_AI():Gracz(), faza(ZAPROGRAMOWANA), ruchy(), ruch_number(0), ending_path(), ending_pion(nullptr)
{
	
	srand(time(NULL));//ustawienie ziarna
	int num = 0; //numerek wariantu ruchów pocz¹tkowych
	const int ile_plikow = 3;//ilosc plików w folderze

	num = rand() % ile_plikow;//losowanie
	string path = "Zasoby/AI/"; //sciezka do pliku z ruchami
	path += ('0'+num);
	path += ".moves";

	ifstream plik;
	
	while (true)//dopóki siê nie powiedzie
	{
		try
		{
			plik.open(path);
			while (!plik.eof())
			{
				string tmp;
				getline(plik, tmp);//pobierz linie tekstu
				Gracz_AI::Ruch* tmp1 = new Gracz_AI::Ruch(tmp);//stwórz nowe dane o ruchu
				ruchy.push_back(tmp1);//zapisz dane
			}
			break;//wczytano wszystkie zapisane ruchy
		}
		catch (const std::exception& e)
		{
			cout << e.what() << " Losowanie nowego pliku..." <<endl;
			ruchy.clear();
			num = rand() % ile_plikow;//ponowne losowanie
			path = "Zasoby/AI/"; 
			path += ('0' + num);//okreœlenie
			path += ".moves";
		}
	}
	plik.close();


	for (int i = 0; i < 8; i++)//zapisanie wskaŸników do pionków gracza
	{
		pionki[i] = Plansza::Pionki[i];
	}
}


Gracz_AI::~Gracz_AI()
{
}

void Gracz_AI::ruch(unsigned char id_p, sf::Vector2u wsp, sf::RenderWindow& window, Menu_List& menu)
{
	auto pion = Plansza::Pionki[id_p];
	auto pred = [&](sf::Vector2u vec) {//pokoloruj pola
		Plansza::path(vec);
	};
	auto predu = [&](sf::Vector2u vec) {//odkoloruj pola
		Plansza::unpath(vec);
	};

	for_each(pion->pola_ruchu.begin(), pion->pola_ruchu.end(), pred);
	Plansza::trigg(pion->pozycja_na_planszy);
	window.clear();
	Plansza::draw(window);
	menu.draw(window);
	window.display();
	Sleep(1500);
	for_each(pion->pola_ruchu.begin(), pion->pola_ruchu.end(), predu);
	Plansza::untrigg(pion->pozycja_na_planszy);

	Plansza::move_P(this, id_p, wsp);
	
	this->was_move = true;
}

void Gracz_AI::tic(sf::Event& _event, sf::RenderWindow& window, Menu_List& menu)
{
	if (faza == ZAPROGRAMOWANA)
	{
		sf::Vector2u tmp_wsp = ruchy[ruch_number]->to;
		if (Plansza::czy_pole_zajete(tmp_wsp))
		{
			faza = GRA; //Zmieñ faze gry
		}
		else
		{
			int id_p = Plansza::get_id_piona(ruchy[ruch_number]->from); //znajdŸ pionek dla którego wykonywany jest ruch
			this->ruch(id_p, ruchy[ruch_number]->to,window, menu); // wykonaj ruch
			this->czy_ruch = false; //zapisz info o wykonaniu ruchu
		}
		this->ruch_number++;
		if (ruch_number >= ruchy.size()) //czy wykonano wszystkie zapisane ruchy?
		{
			faza = GRA; //Zmieñ faze gry
		}
	}
	else if (faza == GRA)
	{
		Pion* b_pionek = pionki[0];

		sf::Vector2u best_pole= sf::Vector2u(0,0);

		for (int i = 0; i < 8; i++)
		{
			
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
		}
		else
		{
			unsigned char ID = Plansza::get_id_piona(b_pionek->pozycja_na_planszy);

			this->ruch(ID, best_pole, window, menu);
			this->czy_ruch = false;
		}
		
	}
	else if (faza==ZAKONCZENIE)
	{
		clearMove();
		static bool czy_szukano = false;
		if (ending_path.size() == 0 || ending_pion == nullptr) {
			//cout << "Szukanie";
			for (int i = 0; i < 8; i++)
			{
				if (pionki[i]->is_win_pos == false && find_ending_path(pionki[i]) == true) {
					ending_pion = pionki[i];
					break;
				}
				else {
					ending_path.clear();
				}
			}
			if (ending_path.size() == 0)
			{
				for (int i = 0; i < 8; i++)
				{
					if (pionki[i]->is_win_pos == false && pionki[i]->paths.size()>0)
					{
						ending_pion = pionki[i];
						ending_path = pionki[i]->paths[rand() % (pionki[i]->paths.size())];
						break;
					}
				}
			
			}

		}
		else if (Plansza::czy_pole_zajete(ending_path[0]) == false) {//jeœli nastepne pole jest wolne
			//cout << "ruch";

			this->ruch(ending_pion->ID, ending_path[0], window, menu);
			//ending_path.erase(ending_path.begin());//usuniêcie ju¿ wykonanego ruchu
			ending_path.clear();
			this->czy_ruch = false;
		}
		else{ //nastêpne pole jest zajête
			//cout << "czyszczenie bo zajete";

			ending_path.clear();
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

	if (pola_k.size()>0){
		for (int i = 0; i < pola_k.size(); i++){
			vector<sf::Vector2u> path;
			int tab_zaj[8][8];
			Plansza::uzupelnij_zajetosc_planszy(tab_zaj);
			tab_zaj[pion->pozycja_na_planszy.y][pion->pozycja_na_planszy.x] = 0;
			if (this->path(path, tab_zaj, pion->pozycja_na_planszy, pola_k[i]) == true)
			{
				ending_path = path;
				return true;
			}
			
		}
	}
	return false;
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

bool Gracz_AI::czy_poprawne_wsp(int x, int y) {
	if (x >= 0 && x < 8 && y >= 0 && y < 8)
		return true;
	else
		return false;
}
bool Gracz_AI::czy_bylo(vector<sf::Vector2u>& path, sf::Vector2u t) {
	if (path.end() == find(path.begin(), path.end(), t))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Gracz_AI::find_better_path(int tab[8][8], vector<sf::Vector2u>& path, vector<sf::Vector2u>& path_tmp, sf::Vector2u from, sf::Vector2u to, sf::Vector2u last) {
	
	vector<sf::Vector2u> path_tmp2 = path_tmp;//odwiedzone pola

	vector<sf::Vector2u> path_tmp_l = path;//œcie¿ka lewostronna
	vector<sf::Vector2u> path_tmp_r = path;//œcie¿ka prawostronna
	bool path_l = false;//czy znaleziono sciezke w prawo
	bool path_r = false;//czy znaleziono sciezke w lewo

	if (preffer_right_path(tab, path_tmp_r, path_tmp, from, to) == true) {
		path_r = true;
	}
	if (preffer_left_path(tab, path_tmp_l, path_tmp2, from, to) == true) {
		path_l = true;
	}

	//cout << endl;
	//cout << "Path L" << endl;
	//for (int i = 0; i < path_tmp_l.size(); i++)
	//{
	//	cout << path_tmp_l[i].x << ";" << path_tmp_l[i].y << " ";
	//}
	//cout << endl;
	//cout << endl;
	//cout << "Path R" << endl;
	//for (int i = 0; i < path_tmp_r.size(); i++)
	//{
	//	cout << path_tmp_r[i].x << ";" << path_tmp_r[i].y << " ";
	//}
	//cout << endl;


	if (path_l == true && path_r == true) //jeœli oba algorytmy znalaz³y drogê
	{
		if (path_tmp_l.size() > path_tmp_r.size())//Jeœli rozmiar lewostronnej œcie¿ki jest wiêkszy
		{
			path = path_tmp_r;//zapisz znalezion¹ œcie¿kê
		}
		else
		{
			path = path_tmp_l;//zapisz znalezion¹ œcie¿kê
		}
		return true;//zwróæ informacjê o znalezieniu œcie¿ki
	}
	else if (path_l == true)//jeœli tylko lewostronny znalaz³ drogê
	{
		path = path_tmp_l;//zapisz znalezion¹ œcie¿kê
		return true;//zwróæ informacjê o znalezieniu œcie¿ki
	}
	else if (path_r == true)//jeœli tylko prawostronny znalaz³ drogê
	{
		path = path_tmp_r;//zapisz znalezion¹ œcie¿kê
		return true;//zwróæ informacjê o znalezieniu œcie¿ki
	}
	else
	{
		return false;//zwróæ informacjê o nie znalezieniu œcie¿ki
	}

}

bool Gracz_AI::preffer_right_path(int tab[8][8], vector<sf::Vector2u>& path, vector<sf::Vector2u>& path_tmp, sf::Vector2u from, sf::Vector2u to, sf::Vector2u last) {
	//for (int i = 0; i < path.size(); i++)
	//{
	//	cout << path[i].x << ";" << path[i].y << " ";
	//}
	//cout << endl;




	int iterator = path.size() - 1; // ostatni dobry moment œcie¿ki

	int i = from.x;
	int j = from.y;

	if (from == to)
	{
		return true;
	}

	if (czy_poprawne_wsp(j + 1, i + 1) && tab[j + 1][i + 1] == 0 && last != sf::Vector2u(i + 1, j + 1))//pole  prawo dó³
	{
		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i + 1, j + 1)) == true)
		{
			return false;
		}
		path_tmp.push_back(sf::Vector2u(i + 1, j + 1));//dodaj pole do odwiedzanych
		path.push_back(sf::Vector2u(i + 1, j + 1));//dodaj pole do œcie¿ki
		iterator++; // zwiêkaszmy aktualne


		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i + 1, j + 1), to, from))//znajdŸ lepsz¹ œcie¿kê
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());//usuñ znalezione pola które nie prowadz¹ do celu
		}
	}
	else if (czy_poprawne_wsp(j + 1, i + 1) && czy_poprawne_wsp(j + 2, i + 2) && tab[j + 1][i + 1] == 1 &&
											tab[j + 2][i + 2] == 0 && last != sf::Vector2u(i + 2, j + 2)) {//przeskok prawo dó³

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i + 2, j + 2)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i + 2, j + 2));//dodaj pole do œcie¿ki
		path_tmp.push_back(sf::Vector2u(i + 2, j + 2));//dodaj pole do odwiedzanych
		iterator++;

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i + 2, j + 2), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());//usuñ znalezione pola które nie prowadz¹ do celu
		}
	}

	else if (czy_poprawne_wsp(j - 1, i + 1) && tab[j - 1][i + 1] == 0 && last != sf::Vector2u(i + 1, j - 1))//pole prawo góra
	{

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i + 1, j - 1)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i + 1, j - 1));//dodaj pole do œcie¿ki
		path_tmp.push_back(sf::Vector2u(i + 1, j - 1));//dodaj pole do œcie¿ki
		iterator++; // zwiêkaszmy aktualne

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i + 1, j - 1), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}
	else if (czy_poprawne_wsp(j - 1, i + 1) && czy_poprawne_wsp(j - 2, i + 2) && tab[j - 1][i + 1] == 1 && tab[j - 2][i + 2] == 0 && last != sf::Vector2u(i + 2, j - 2)) {//przeskok prawo góra

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i + 2, j - 2)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i + 2, j - 2));
		path_tmp.push_back(sf::Vector2u(i + 2, j - 2));
		iterator++;

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i + 2, j - 2), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}

	else if (czy_poprawne_wsp(j + 1, i - 1) && tab[j + 1][i - 1] == 0 && last != sf::Vector2u(i - 1, j + 1))//pole lewo dó³
	{

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i - 1, j + 1)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i - 1, j + 1));//dodaj pole do œcie¿ki
		path_tmp.push_back(sf::Vector2u(i - 1, j + 1));//dodaj pole do œcie¿ki
		iterator++; // zwiêkaszmy aktualne

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i - 1, j + 1), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}
	else if (czy_poprawne_wsp(j + 1, i - 1) && czy_poprawne_wsp(j + 2, i - 2) && tab[j + 1][i - 1] == 1 && tab[j + 2][i - 2] == 0 && last != sf::Vector2u(i - 2, j + 2)) //przeskok lewo dó³
	{

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i - 2, j + 2)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i - 2, j + 2));
		path_tmp.push_back(sf::Vector2u(i - 2, j + 2));
		iterator++;

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i - 2, j + 2), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}

	else if (czy_poprawne_wsp(j - 1, i - 1) && tab[j - 1][i - 1] == 0 && last != sf::Vector2u(i - 1, j - 1))//pole lewo góra
	{

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i - 1, j - 1)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i - 1, j - 1));//dodaj pole do œcie¿ki
		path_tmp.push_back(sf::Vector2u(i - 1, j - 1));//dodaj pole do œcie¿ki
		iterator++; // zwiêkaszmy aktualne


		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i - 1, j - 1), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}


	}
	else if (czy_poprawne_wsp(j - 1, i - 1) && czy_poprawne_wsp(j - 2, i - 2) && tab[j - 1][i - 1] == 1 && tab[j - 2][i - 2] == 0 && last != sf::Vector2u(i - 2, j - 2)) {//przeskok lewo góra


		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i - 2, j - 2)) == true)
		{
			return false;
		}
		path.push_back(sf::Vector2u(i - 2, j - 2));
		path_tmp.push_back(sf::Vector2u(i - 2, j - 2));
		iterator++;

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i - 2, j - 2), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}

	}
	return false;
}
bool Gracz_AI::preffer_left_path(int tab[8][8], vector<sf::Vector2u>& path, vector<sf::Vector2u>& path_tmp, sf::Vector2u from, sf::Vector2u to, sf::Vector2u last) {

	//for (int i = 0; i < path.size(); i++)
	//{
	//	cout << path[i].x << ";" << path[i].y << " ";
	//}
	//cout << endl;



	int iterator = path.size() - 1; // ostatni dobry moment œcie¿ki

	int i = from.x;
	int j = from.y;

	if (from == to)
	{
		return true;
	}

	if (czy_poprawne_wsp(j + 1, i - 1) && tab[j + 1][i - 1] == 0 && last != sf::Vector2u(i - 1, j + 1))//pole lewo dó³
	{
		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i - 1, j + 1)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i - 1, j + 1));//dodaj pole do œcie¿ki
		path_tmp.push_back(sf::Vector2u(i - 1, j + 1));//dodaj pole do odwiedzanych
		iterator++; // zwiêkaszmy aktualne pole

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i - 1, j + 1), to, from))//znajdŸ lepsz¹ œcie¿kê
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());//usuñ znalezione pola które nie prowadz¹ do celu
		}
	}
	else if (czy_poprawne_wsp(j + 1, i - 1) && czy_poprawne_wsp(j + 2, i - 2) && tab[j + 1][i - 1] == 1 && tab[j + 2][i - 2] == 0 && last != sf::Vector2u(i - 2, j + 2)) {//przeskok lewo dó³

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i - 2, j + 2)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i - 2, j + 2));//dodaj pole do œcie¿ki
		path_tmp.push_back(sf::Vector2u(i - 2, j + 2));//dodaj pole do odwiedzanych
		iterator++;// zwiêkaszmy aktualne pole

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i - 2, j + 2), to, from))//znajdŸ lepsz¹ œcie¿kê
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());//usuñ znalezione pola które nie prowadz¹ do celu
		}
	}

	else if (czy_poprawne_wsp(j - 1, i - 1) && tab[j - 1][i - 1] == 0 && last != sf::Vector2u(i - 1, j - 1))//pole lewo góra
	{
		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i - 1, j - 1)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i - 1, j - 1));//dodaj pole do œcie¿ki
		path_tmp.push_back(sf::Vector2u(i - 1, j - 1));//dodaj pole do œcie¿ki
		iterator++; // zwiêkaszmy aktualne

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i - 1, j - 1), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}
	else if (czy_poprawne_wsp(j - 1, i - 1) && czy_poprawne_wsp(j - 2, i - 2) && tab[j - 1][i - 1] == 1 && tab[j - 2][i - 2] == 0 && last != sf::Vector2u(i - 2, j - 2)) {//przeskok lewo góra

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i - 2, j - 2)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i - 2, j - 2));
		path_tmp.push_back(sf::Vector2u(i - 2, j - 2));
		iterator++;

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i - 2, j - 2), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}
	else if (czy_poprawne_wsp(j + 1, i + 1) && tab[j + 1][i + 1] == 0 && last != sf::Vector2u(i + 1, j + 1))//pole  prawo dó³
	{

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i + 1, j + 1)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i + 1, j + 1));//dodaj pole do œcie¿ki
		path_tmp.push_back(sf::Vector2u(i + 1, j + 1));//dodaj pole do œcie¿ki
		iterator++; // zwiêkaszmy aktualne

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i + 1, j + 1), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}
	else if (czy_poprawne_wsp(j + 1, i + 1) && czy_poprawne_wsp(j + 2, i + 2) && tab[j + 1][i + 1] == 1 && tab[j + 2][i + 2] == 0 && last != sf::Vector2u(i + 2, j + 2)) {//przeskok prawo dó³

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i + 2, j + 2)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i + 2, j + 2));
		path_tmp.push_back(sf::Vector2u(i + 2, j + 2));
		iterator++;

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i + 2, j + 2), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}

	else if (czy_poprawne_wsp(j - 1, i + 1) && tab[j - 1][i + 1] == 0 && last != sf::Vector2u(i + 1, j - 1))//pole prawo góra
	{

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i + 1, j - 1)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i + 1, j - 1));//dodaj pole do œcie¿ki
		path_tmp.push_back(sf::Vector2u(i + 1, j - 1));//dodaj pole do œcie¿ki
		iterator++; // zwiêkaszmy aktualne

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i + 1, j - 1), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}
	else if (czy_poprawne_wsp(j - 1, i + 1) && czy_poprawne_wsp(j - 2, i + 2) && tab[j - 1][i + 1] == 1 && tab[j - 2][i + 2] == 0 && last != sf::Vector2u(i + 2, j - 2)) {//przeskok prawo góra

		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i + 2, j - 2)) == true)
		{
			return false;
		}

		path.push_back(sf::Vector2u(i + 2, j - 2));
		path_tmp.push_back(sf::Vector2u(i + 2, j - 2));
		iterator++;

		if (find_better_path(tab, path, path_tmp, sf::Vector2u(i + 2, j - 2), to, from))
		{
			return true;
		}
		else
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}
	return false;

}

bool Gracz_AI::path(vector<sf::Vector2u> & path, int tab[8][8], sf::Vector2u from, sf::Vector2u to, sf::Vector2u last) {
	vector<sf::Vector2u> path_tmp;//przetrzymuje odwiedzone pola
	vector<sf::Vector2u> path_tmp2;

	vector<sf::Vector2u> path_tmp_l;
	vector<sf::Vector2u> path_tmp_r;
	bool path_l = false;//czy znaleziono sciezke w prawo
	bool path_r = false;//czy znaleziono sciezke w lewo

	if (preffer_right_path(tab, path_tmp_r, path_tmp, from, to) == true) {
		if (path_tmp_r[0] == from)
		{
			path.erase(path.begin());
		}
		path_r = true;
	}
	if (preffer_left_path(tab, path_tmp_l, path_tmp2, from, to) == true) {
		if (path_tmp_l[0] == from)
		{
			path.erase(path.begin());
		}
		path_l = true;
	}

	//cout << "Path L" << endl;
	//for (int i = 0; i < path_tmp_l.size(); i++)
	//{
	//	cout << path_tmp_l[i].x << ";" << path_tmp_l[i].y << " ";
	//}
	//cout << endl;
	//cout << endl;
	//cout << "Path R" << endl;
	//for (int i = 0; i < path_tmp_r.size(); i++)
	//{
	//	cout << path_tmp_r[i].x << ";" << path_tmp_r[i].y << " ";
	//}
	//cout << endl;


	if (path_l == true && path_r == true)
	{
		if (path_tmp_l.size() > path_tmp_r.size())
		{
			path = path_tmp_r;
		}
		else
		{
			path = path_tmp_l;
		}
		return true;
	}
	else if (path_l == true)
	{
		path = path_tmp_l;
		return true;
	}
	else if (path_r == true)
	{
		path = path_tmp_r;
		return true;
	}
	else
	{
		return false;
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
		throw exception("Blad w danych wejsciowych AI");
	}
	if (t[1] != ' ')
	{
		throw exception("Blad w danych wejsciowych AI");
	}
	if (isdigit(t[2]))
	{
		y = t[2] - '0';
	}
	else
	{		
		throw exception("Blad w danych wejsciowych AI");
	}
	if (t[3] != ' ')
	{
		throw exception("Blad w danych wejsciowych AI");
	}
	if (Gracz_AI::czy_poprawne_wsp(x, y))
	{
		this->from = sf::Vector2u(x, y);
	}
	if (isdigit(t[4]))
	{
		x1 = t[4] - '0';
	}
	else
	{
		throw exception("Blad w danych wejsciowych AI");

	}
	if (t[5] != ' ')
	{
		throw exception("Blad w danych wejsciowych AI");
	}
	if (isdigit(t[6]))
	{
		y1 = t[6] - '0';
	}
	else
	{
		throw exception("Blad w danych wejsciowych AI");

	}
	if (Gracz_AI::czy_poprawne_wsp(x1, y1))
	{
		this->to = sf::Vector2u(x1, y1);
	}
	else
	{
		throw exception("Blad w danych wejsciowych AI \n dane po za zakresem");
	}

}