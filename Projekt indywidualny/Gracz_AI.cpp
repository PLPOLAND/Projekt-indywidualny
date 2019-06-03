#include "Gracz_AI.h"
#include <conio.h>
#include <iostream>
#include "Plansza.h"
#include <fstream>
#include "Windows.h"
Gracz_AI::Gracz_AI():Gracz(), faza(ZAPROGRAMOWANA), ruchy(), ruch_number(0), ending_path(), ending_pion(nullptr)
{
	//cout << "Gracz" << endl;
	srand(time(NULL));
	int num = 0; //numerek wariantu ruchów pocz¹tkowych
	const int ile_plikow = 3;//ilosc plików w folderze

	num = rand() % ile_plikow;//losowanie
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
				/*//cout << path << endl;
				//cout << tmp << endl;*/
				Gracz_AI::Ruch* tmp1 = new Gracz_AI::Ruch(tmp);
				ruchy.push_back(tmp1);
			}
			break;
		}
		catch (const std::exception& e)
		{
			cout << e.what();
			break;
			num = rand() % ile_plikow;//ponowne losowanie
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
	Plansza::trigg(pion->pozycja_na_planszy);
	window.clear();
	Plansza::draw(window);
	window.display();
	Sleep(1500);
	for_each(pion->pola_ruchu.begin(), pion->pola_ruchu.end(), predu);
	Plansza::untrigg(pion->pozycja_na_planszy);

	Plansza::move_P(this, id_p, wsp);
}

void Gracz_AI::tic(sf::Event& _event, sf::RenderWindow& window)
{
	if (faza == ZAPROGRAMOWANA)
	{
		
		sf::Vector2u tmp_wsp = ruchy[ruch_number]->to;
		if (Plansza::czy_pole_zajete(tmp_wsp))
		{
			faza = GRA;
		}
		else
		{
			int id_p = Plansza::get_id_piona(ruchy[ruch_number]->from);
			this->ruch(id_p, ruchy[ruch_number]->to,window);
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
				if (pionki[i]->is_win_pos == false && find_ending_path(pionki[i]) == true) {
					ending_pion = pionki[i];
					break;
				}
				else if (pionki[i]->is_win_pos == false && pionki[i]->paths.size())
				{
					ending_path = pionki[i]->paths[0];
				}
			}
		}
		else if (Plansza::czy_pole_zajete(ending_path[0]) == false) {//jeœli nastepne pole jest wolne
			
			this->ruch(ending_pion->ID, ending_path[0], window);
			ending_path.erase(ending_path.begin());//usuniêcie ju¿ wykonanego ruchu
			this->czy_ruch = false;
		}
		else{ //nastêpne pole jest zajête
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
			if (this->path(path, tab_zaj, pion->pozycja_na_planszy, pola_k[i]) == true)
			{
				ending_path = path;
				return true;
			}
			
		}
		return false;
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



//bool Gracz_AI::find_path_to(sf::Vector2u from, sf::Vector2u to, sf::Vector2u last, Kierunek hop){
//
//	static vector<sf::Vector2u> tmp_path;
//	static int tmp_path_iter = (int)tmp_path.size() - 1;
//
//	static bool done = false;
//
//	if (hop == BRAK)
//	{
//		tmp_path.clear();
//		tmp_path_iter = (int)tmp_path.size() - 1;
//	}
//	sf::Vector2u poz0 = last;
//	sf::Vector2u poz1 = last;
//	sf::Vector2u poz2 = last;
//	sf::Vector2u poz3 = last;
//	if (from.x - 1 >= 0 && from.x - 1 < 8 && from.y - 1 >= 0 && from.y - 1 < 8)
//	{
//		poz0 = sf::Vector2u(from.x - 1, from.y - 1);
//	}
//	if (from.x - 1 >= 0 && from.x - 1 < 8 && from.y + 1 >= 0 && from.y + 1 < 8)
//	{
//		poz1 = sf::Vector2u(from.x - 1, from.y + 1);
//	}
//	if (from.x + 1 >= 0 && from.x + 1 < 8 && from.y - 1 >= 0 && from.y - 1 < 8)
//	{
//		poz2 = sf::Vector2u(from.x + 1, from.y - 1);
//	}
//	if (from.x + 1 >= 0 && from.x + 1 < 8 && from.y + 1 >= 0 && from.y + 1 < 8)
//	{
//		poz3 = sf::Vector2u(from.x + 1, from.y + 1);
//	}
//
//	bool poz0_2 = true; //
//	bool poz1_2 = true; //
//	bool poz2_2 = true; //
//	bool poz3_2 = true; //
//
//	if ((int)poz0.x - 1 < 0 || (int)poz0.y - 1 < 0 || poz0 == last || hop == LG)
//	{
//		poz0_2 = false;
//	}
//	if ((int)poz1.x - 1 < 0 || (int)poz1.y + 1 > 7 || poz1 == last || hop == LD)
//	{
//		poz1_2 = false;
//	}
//	if ((int)poz2.x + 1 > 7 || (int)poz2.y - 1 < 0 || poz2 == last || hop == RG)
//	{
//		poz2_2 = false;
//	}
//	if ((int)poz3.x + 1 > 7 || (int)poz3.y + 1 > 7 || poz3 == last || hop == RD)
//	{
//		poz3_2 = false;
//	}
//
//
//
//	sf::Vector2i poz0_offset = sf::Vector2i(-1, -1);
//	sf::Vector2i poz1_offset = sf::Vector2i(-1, 1);
//	sf::Vector2i poz2_offset = sf::Vector2i(1, -1);
//	sf::Vector2i poz3_offset = sf::Vector2i(1, 1);
//
//
//
//	bool czy_wsz_zaj0 = false;
//	bool czy_wsz_zaj1 = false;
//	bool czy_wsz_zaj2 = false;
//	bool czy_wsz_zaj3 = false;
//
//	if (poz0 != last && Pion::get_pole(poz0)->zajete == false && hop == BRAK)
//	{
//
//		ending_path.push_back(poz0);
//
//		
//	}
//	else if (poz0 != last && poz0_2 == true && Pion::get_pole(poz0)->zajete == true && Pion::get_pole(poz0, poz0_offset)->zajete == false)
//	{
//		if (ending_path.end() == find(ending_path.begin(), ending_path.end(), Pion::get_wsp(poz0, poz0_offset))/* || ending_path.size() == 0*/)
//		{
//			ending_path.push_back(Pion::get_wsp(poz0, poz0_offset));
//			tmp_path_iter++;
//		}
//		else
//		{
//			return false;
//		}
//
//		if (find_path_to(Pion::get_wsp(poz0, poz0_offset), to, last, RD) == false)
//		{
//			for (int i = tmp_path.size() - 1; i >= tmp_path_iter; i--)
//			{
//				ending_path.erase(ending_path.begin() + i);
//			}
//			tmp_path_iter--;
//		}
//		
//	}
//	else
//	{
//		czy_wsz_zaj0 = true;
//	}
//	//TODO
//}




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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
bool Gracz_AI::preffer_right_path(int tab[8][8], vector<sf::Vector2u>& path, vector<sf::Vector2u>& path_tmp, sf::Vector2u from, sf::Vector2u to, sf::Vector2u last) {
	for (int i = 0; i < path.size(); i++)
	{
		//cout << path[i].x << ";" << path[i].y<<" ";
	}
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
		path_tmp.push_back(sf::Vector2u(i + 1, j + 1));//dodaj pole do œcie¿ki
		path.push_back(sf::Vector2u(i + 1, j + 1));//dodaj pole do œcie¿ki
		iterator++; // zwiêkaszmy aktualne
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i + 1, j + 1), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca ¿e znaleziono
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i + 1, j + 1), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i + 2, j + 2), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca true (znaleziono)
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i + 2, j + 2), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i + 1, j - 1), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca ¿e znaleziono
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i + 1, j - 1), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i + 2, j - 2), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca true (znaleziono)
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i + 2, j - 2), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i - 1, j + 1), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca ¿e znaleziono
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i - 1, j + 1), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i - 2, j + 2), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca true (znaleziono)
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i - 2, j + 2), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i - 1, j - 1), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca ¿e znaleziono
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i - 1, j - 1), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i - 2, j - 2), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca true (znaleziono)
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i - 2, j - 2), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}
	return false;
}
bool Gracz_AI::preffer_left_path(int tab[8][8], vector<sf::Vector2u>& path, vector<sf::Vector2u>& path_tmp, sf::Vector2u from, sf::Vector2u to, sf::Vector2u last) {

	for (int i = 0; i < path.size(); i++)
	{
		//cout << path[i].x << ";" << path[i].y << " ";
	}
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
		path_tmp.push_back(sf::Vector2u(i - 1, j + 1));//dodaj pole do œcie¿ki
		iterator++; // zwiêkaszmy aktualne
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i - 1, j + 1), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca ¿e znaleziono
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i - 1, j + 1), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}
	else if (czy_poprawne_wsp(j + 1, i - 1) && czy_poprawne_wsp(j + 2, i - 2) && tab[j + 1][i - 1] == 1 && tab[j + 2][i - 2] == 0 && last != sf::Vector2u(i - 2, j + 2)) {//przeskok lewo dó³
		
		if (path.size() > 1 && czy_bylo(path_tmp, sf::Vector2u(i - 2, j + 2)) == true)
		{
			return false;
		}
		
		path.push_back(sf::Vector2u(i - 2, j + 2));
		path_tmp.push_back(sf::Vector2u(i - 2, j + 2));
		iterator++;
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i - 2, j + 2), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca true (znaleziono)
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i - 2, j + 2), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i - 1, j - 1), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca ¿e znaleziono
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i - 1, j - 1), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i - 2, j - 2), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca true (znaleziono)
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i - 2, j - 2), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i + 1, j + 1), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca ¿e znaleziono
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i + 1, j + 1), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i + 2, j + 2), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca true (znaleziono)
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i + 2, j + 2), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i + 1, j - 1), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca ¿e znaleziono
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i + 1, j - 1), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
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
		if (preffer_right_path(tab, path, path_tmp, sf::Vector2u(i + 2, j - 2), to, from) == true) { //rekurencyjnie, jeœli siê znajdzie œcie¿ka to zwraca true (znaleziono)
			return true;
		}
		else if (preffer_left_path(tab, path, path_tmp, sf::Vector2u(i + 2, j - 2), to, from) == true)
		{
			return true;
		}
		else // jeœli nie to usuwamy znalezion¹ wczeœniej œcie¿kê do aktualnego momentu
		{
			path.erase(path.begin() + iterator, path.end());
		}
	}
	return false;

}

bool Gracz_AI::path(vector<sf::Vector2u> & path, int tab[8][8], sf::Vector2u from, sf::Vector2u to, sf::Vector2u last) {
	vector<sf::Vector2u> path_tmp;//przetrzymuje odwiedzone pola
	 if (from.x < to.x)
	{
		if (preffer_right_path(tab, path, path_tmp, from, to) == true) {
			if (path[0] == from)
			{
				path.erase(path.begin());
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (preffer_left_path(tab, path, path_tmp, from, to) == true) {
			if (path[0] == from)
			{
				path.erase(path.begin());
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	if (isdigit(t[2]))
	{
		y = t[2] - '0';
	}
	else
	{		
		throw exception("Blad w danych wejsciowych AI");

	}
	if (isdigit(t[4]))
	{
		x1 = t[4] - '0';
	}
	else
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

	this->from = sf::Vector2u(x, y);
	this->to = sf::Vector2u(x1, y1);

}
