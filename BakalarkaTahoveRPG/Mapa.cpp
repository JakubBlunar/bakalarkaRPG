#include "Mapa.h"
#include "Policko.h"
#include "Hrac.h"
#include <iostream>
#include "PolickoDvere.h"
#include "Hra.h"
#include "Npc.h"

Mapa::Mapa(std::string menoMapy, Hrac* paHrac, Hra* hram, int paVyska, int paSirka) {
	this->hrac = paHrac;
	this->hra = hra;
	smerPohybu = 0;
	posunX = 0;
	posunY = 0;
	vyska = paVyska;
	sirka = paSirka;
	pohybDelta = 0;
	smerPohybu = 0;

	mapa = new Policko**[sirka];
	for (int i = 0; i < sirka; ++i) {
		mapa[i] = new Policko*[vyska];
	}

	for (int i = 0; i < sirka; ++i) {
		for (int j = 0; j < vyska; ++j) {
			mapa[i][j] = nullptr;
		}
	}

}

Mapa::~Mapa() {
	for (int i = 0; i < sirka; i++)
	{
		for (int j = 0; j < vyska; j++)
		{
			delete mapa[i][j];
		}
	}

	for (int i = 0; i < sirka; ++i) {
		delete[] mapa[i];
	}

	delete[] mapa;
}


void Mapa::setHrac(Hrac* paHrac) {
	hrac = paHrac;
}


void Mapa::posun(int posunX, int posunY) {
	this->posunX += posunX;
	this->posunY += posunY;

}

void Mapa::render(sf::RenderWindow* okno) {
	view.reset(sf::FloatRect(posunX, posunY, okno->getSize().x, okno->getSize().y));
	okno->setView(view);
	
	sf::Sprite* sprite;
	for (int vrstva = 0; vrstva < 4; vrstva++) {

		for (int i = 0; i < sirka; i++)
		{
			for (int j = 0; j < vyska; j++)
			{

				sprite = mapa[i][j]->dajObrazokVrstvy(vrstva);
				sprite->setPosition(sf::Vector2f(32.f * i, 32.f * j));
				okno->draw(*sprite);

				if (vrstva == 2 && hrac->GetpolickoY() < j) {
					if (mapa[i][j]->Getnpc() != nullptr) {
						sf::Sprite* npcObrazok = mapa[i][j]->Getnpc()->dajObrazok();
						npcObrazok->setPosition(sf::Vector2f(32.f * i, 32 - 48.f + 32.f* j));
						okno->draw(*npcObrazok);
					}
				}

				if (vrstva == 1) {
					hrac->render(okno);
				}

				if (vrstva == 1 && hrac->GetpolickoY() >= j) {
					if (mapa[i][j]->Getnpc() != nullptr) {
						sf::Sprite* npcObrazok = mapa[i][j]->Getnpc()->dajObrazok();
						npcObrazok->setPosition(sf::Vector2f(32.f * i, 32 - 48.f + 32.f* j));
						okno->draw(*npcObrazok);
					}
				}


			}
		}
	}
	okno->setView(okno->getDefaultView());
}


sf::FloatRect Mapa::Getzobrazenaoblast() {
	return sf::FloatRect(posunX,posunY,view.getSize().x,view.getSize().y);
}

void Mapa::update(double delta) {

	switch (smerPohybu)
	{
	case 0:
		break;
	case 1:
		if (pohybDelta < 32) {
			pohybDelta++;
			posun(1, 0);
		}
		else {
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;
	case 2:
		if (pohybDelta < 32) {
			pohybDelta++;
			posun(-1, 0);
		}
		else {
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;
	case 3:
		if (pohybDelta < 32) {
			hrac->animaciaTick();
			pohybDelta++;
			posun(0, -1);
		}
		else {
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;
	case 4:
		if (pohybDelta < 32) {
			pohybDelta++;
			posun(0, 1);
		}
		else {
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;

	default:
		break;
	}
}


void Mapa::hracSkocilNaPolicko(int x, int y) {
	mapa[x][y]->hracSkok(hrac);
}

void Mapa::posunHracaNaPolicko(int x, int y,int smerPohladu) {
	
	
	int offsetHracaX = x*32;
	int offsetHracaY = y*32;
	int posunMapyX = 0;
	int posunMapyY = 0;

	hrac->setPolickoX(x);
	hrac->setPolickoY(y);
	if (offsetHracaX > 350) {
		posunMapyX = offsetHracaX-6*32;
	}

	if (offsetHracaY > 350) {
		posunMapyY = offsetHracaY - 5*32;
	}
	hrac->setOffsetX(offsetHracaX);
	hrac->setOffsetY(offsetHracaY);
	posunX = posunMapyX;
	posunY = posunMapyY;

	switch (smerPohladu)
	{
	case 0:
		hrac->zmenSmerPohladu(SmerPohladu::dole);
		break;
	case 1:
		hrac->zmenSmerPohladu(SmerPohladu::vpravo);
		break;
	case 2:
		hrac->zmenSmerPohladu(SmerPohladu::hore);
		break;
	case 3:
		hrac->zmenSmerPohladu(SmerPohladu::vlavo);
		break;
	default:
		hrac->zmenSmerPohladu(SmerPohladu::dole);
		break;
	}

}

void Mapa::posunVpravo() {
	pohybDelta = 0;
	smerPohybu = 1;
}

void Mapa::posunVlavo() {
	pohybDelta = 0;
	smerPohybu = 2;
}

void Mapa::posunHore() {
	pohybDelta = 0;
	smerPohybu = 3;
}

void Mapa::posunDole() {
	pohybDelta = 0;
	smerPohybu = 4;
}

int Mapa::Getsmerpohybu() {
	return smerPohybu;
}

int Mapa::Getvyska() {
	return vyska;
}

int Mapa::Getsirka() {
	return sirka;
}

bool Mapa::jeMoznyPohyb(int x, int y) {
	if (x < 0 || x >= sirka || y < 0 || y >= vyska) {
		return false;
	}

	bool priechodne = true;

	if (mapa[x][y]->Getnpc() != nullptr) {
		priechodne = false;
	}

	if (!mapa[x][y]->jePrechodne()) {
		priechodne = false;
	}
	return priechodne;
}

void Mapa::setSirkaVyska(int paSirka, int paVyska) {
	this->sirka = paSirka;
	this->vyska = paVyska;
}

void Mapa::nastavPolicko(int paX, int paY, Policko* paPolicko) {
	mapa[paX][paY] = paPolicko;
}

Policko* Mapa::GetPolicko(int x, int y) {
	return mapa[x][y];
}

void Mapa::hracInterakcia() {
	if (hrac->GethybeSa() || smerPohybu != 0) return;

	int x = hrac->GetpolickoX();
	int y = hrac->GetpolickoY();

	if (hrac->GetSmerPohladu() == SmerPohladu::hore) {
		y--;
	}
	if (hrac->GetSmerPohladu() == SmerPohladu::dole) {
		y++;
	}

	if (hrac->GetSmerPohladu() == SmerPohladu::vpravo) {
		x++;
	}

	if (hrac->GetSmerPohladu() == SmerPohladu::vlavo) {
		x--;
	}

	if (x < 0 || x >= sirka || y < 0 || y >= vyska) {
		return;
	}

	if (mapa[x][y]->Getnpc() != nullptr) {
		mapa[x][y]->Getnpc()->dialog(hrac);
	}
	else {
		mapa[x][y]->interakcia(hrac);
	}

	



}