#include "Gracz_Ludzki.h"
#include <iostream>

Gracz_Ludzki::Gracz_Ludzki() : Gracz(), faza(WYB_PIONA), last_trigg(0, 0)
{
}


void Gracz_Ludzki::ruch(unsigned char id_p, sf::Vector2u wsp)
{
	Plansza::move_P(this, id_p,	wsp);
	this->was_move = true;
}

void Gracz_Ludzki::tic(sf::Event& _event, sf::RenderWindow& window, Menu_List&)
{
	if (faza==WYB_PIONA)//Wybieranie pionka
	{
		Plansza::trigg(last_trigg);
		if (_event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//przesuniecie pola wyboru w lewo
		{
			this->trigg(sf::Keyboard::Left);

			while (_event.type != sf::Event::KeyReleased)
			{
				window.pollEvent(_event);
			}
		}		
		else if (_event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//przesuniecie pola wyboru w prawo
		{
			this->trigg(sf::Keyboard::Right);

			while (_event.type != sf::Event::KeyReleased)
			{
				window.pollEvent(_event);
			}
		}
		else if (_event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//przesuniecie pola wyboru w dó³
		{
			this->trigg(sf::Keyboard::Down);

			while (_event.type != sf::Event::KeyReleased)
			{
				window.pollEvent(_event);
			}
		}
		else if (_event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//przesuniecie pola wyboru w górê
		{
			this->trigg(sf::Keyboard::Up);

			while (_event.type != sf::Event::KeyReleased)
			{
				window.pollEvent(_event);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))//Wybranie
		{
			//cout << "Enter" << endl;
			if (Plansza::czy_pionek_nalezy(last_trigg, this) == true) {
				wsp_piona = last_trigg;
				faza = RUCH_PIONA;

				auto pion = Plansza::get_pion(last_trigg);
				auto pred = [&](sf::Vector2u vec) {
					Plansza::path(vec);
				};

				for_each(pion->pola_ruchu.begin(), pion->pola_ruchu.end(), pred);

				
			}
			else
			{
				cout << "Nie twoj pion!" << endl;
			}
			while (_event.type != sf::Event::KeyReleased)
			{
				window.pollEvent(_event);
			}
		}
	}
	else if (faza==RUCH_PIONA)
	{
		if (_event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//przesuniecie pola wyboru w lewo
		{
			this->trigg(sf::Keyboard::Left);

			while (_event.type != sf::Event::KeyReleased)
			{
				window.pollEvent(_event);
			}
		}
		else if (_event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//przesuniecie pola wyboru w prawo
		{
			this->trigg(sf::Keyboard::Right);

			while (_event.type != sf::Event::KeyReleased)
			{
				window.pollEvent(_event);
			}
		}
		else if (_event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//przesuniecie pola wyboru w dó³
		{
			this->trigg(sf::Keyboard::Down);

			while (_event.type != sf::Event::KeyReleased)
			{
				window.pollEvent(_event);
			}
		}
		else if (_event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//przesuniecie pola wyboru w górê
		{
			this->trigg(sf::Keyboard::Up);

			while (_event.type != sf::Event::KeyReleased)
			{
				window.pollEvent(_event);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			//cout << "Enter" << endl;

			auto pion = Plansza::get_pion(wsp_piona);
			if (Plansza::czy_pole_zajete(last_trigg) == false && pion->pola_ruchu.end() != find(pion->pola_ruchu.begin(),pion->pola_ruchu.end(),last_trigg) ) {
				
				//auto pion = Plansza::get_pion(wsp_piona);
				auto pred = [&](sf::Vector2u vec) {
					Plansza::unpath(vec);
				};

				for_each(pion->pola_ruchu.begin(), pion->pola_ruchu.end(), pred);
				
				this->ruch(Plansza::get_id_piona(wsp_piona), last_trigg);
				faza = WYB_PIONA;

				czy_ruch = false;
				wsp_piona = sf::Vector2u(0, 0);

				Plansza::print();
				Plansza::untrigg(last_trigg);
			}
			else
			{
				cout << "Zajete!/ niedozwolone" << endl;
			}
			while (_event.type != sf::Event::KeyReleased)
			{
				window.pollEvent(_event);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			auto pion = Plansza::get_pion(wsp_piona);
			auto pred = [&](sf::Vector2u vec) {
				Plansza::unpath(vec);
			};

			for_each(pion->pola_ruchu.begin(), pion->pola_ruchu.end(), pred);



			faza = WYB_PIONA;
			wsp_piona = sf::Vector2u(0, 0);
		}

	}


}

void Gracz_Ludzki::trigg(sf::Keyboard::Key key)
{
	if (key==sf::Keyboard::Left)
	{
		Plansza::untrigg(last_trigg);

		if (last_trigg.x != 0)
		{
			last_trigg.x--;
		}
		Plansza::trigg(last_trigg);
	}
	else if (key == sf::Keyboard::Right)
	{
		Plansza::untrigg(last_trigg);//Odznacz poprzednie pole

		if (last_trigg.x != 7)
		{
			last_trigg.x++;
		}
		Plansza::trigg(last_trigg);//zaznacz nowe pole
	}
	else if (key == sf::Keyboard::Down)
	{
		Plansza::untrigg(last_trigg);//Odznacz poprzednie pole

		if (last_trigg.y != 7)
		{
			last_trigg.y++;
		}
		Plansza::trigg(last_trigg);//zaznacz nowe pole
	}
	else if (key == sf::Keyboard::Up)
	{
		Plansza::untrigg(last_trigg);//Odznacz poprzednie pole

		if (last_trigg.y != 0)
		{
			last_trigg.y--;
		}
		Plansza::trigg(last_trigg);//zaznacz nowe pole
	}
}
//void Gracz_Ludzki::trigg(sf::Keyboard::Key key)
//{
//	if (key == sf::Keyboard::Left)
//	{
//		Plansza::untrigg(last_trigg);
//
//		if (last_trigg.x != 0)
//		{
//			last_trigg.x--;
//		}
//		Plansza::trigg(last_trigg);
//	}
//	else if (key == sf::Keyboard::Right)
//	{
//		Plansza::untrigg(last_trigg);//Odznacz poprzednie pole
//
//		if (last_trigg.x != 7)
//		{
//			last_trigg.x++;
//		}
//		Plansza::trigg(last_trigg);//zaznacz nowe pole
//	}
//	else if (key == sf::Keyboard::Down)
//	{
//		Plansza::untrigg(last_trigg);//Odznacz poprzednie pole
//
//		if (last_trigg.y != 7)
//		{
//			last_trigg.y++;
//		}
//		Plansza::trigg(last_trigg);//zaznacz nowe pole
//	}
//	else if (key == sf::Keyboard::Up)
//	{
//		Plansza::untrigg(last_trigg);//Odznacz poprzednie pole
//
//		if (last_trigg.y != 0)
//		{
//			last_trigg.y--;
//		}
//		Plansza::trigg(last_trigg);//zaznacz nowe pole
//	}
//}