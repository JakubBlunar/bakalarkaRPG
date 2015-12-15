#include "Mapa.h"
#include "Policko.h"
#include "Hrac.h"
#include <iostream>
#include "PolickoDvere.h"
#include "Hra.h"

Mapa::Mapa(std::string menoMapy, Hrac* paHrac,Hra* hra) {
	this->hrac = paHrac;
	this->hra = hra;
	smerPohybu = 0;
	posunX = 0;
	posunY = 0;
	vyska = 0;
	sirka = 0;
	pohybDelta = 0;
	smerPohybu = 0;

}

Mapa::~Mapa() {
	for (int i = 0; i < vyska; i++)
	{
		for (int j = 0; j < vyska; j++)
		{
			delete mapa[i][j];
		}
	}
}


void Mapa::setHrac(Hrac* paHrac) {
	hrac = paHrac;
}


void Mapa::posun(int posunX, int posunY) {
	this->posunX += posunX;
	this->posunY += posunY;

}

void Mapa::render(sf::RenderWindow* okno) {
	sf::Sprite* sprite;
	
	//od akeho policka po ake policko sa ma vykreslovat mapa
	int odX = (int)(hrac->GetpolickoX() - 34 * (1.0*hrac->GetoffsetX() / okno->getSize().x)-2);
	if (odX <0) {
		odX = 0;
	}

	int doX = (int)(hrac->GetpolickoX() + 34 *(1-(1.0*hrac->GetoffsetX()/okno->getSize().x ))+2);
	if (doX >= sirka) {
		doX = sirka - 1;
	}

	int odY = (int)(hrac->GetpolickoY() - 24 * (1.0*hrac->GetoffsetY() / okno->getSize().y) - 1);
	if (odY <0) {
		odY = 0;
	}
	
	int doY = (int)(hrac->GetpolickoY() + 24 * (1 - (1.0*hrac->GetoffsetY() / okno->getSize().y)) + 1);
	if (doY >= vyska) {
		doY = vyska - 1;
	}
	
	for (int vrstva = 0; vrstva < 4; vrstva++) {

		for (int i = odX; i <= doX; i++)
		{
			for (int j = odY; j <= doY; j++)
			{
				if (vrstva == 1) {
					hrac->render(okno);
				}
				sprite = mapa[i][j]->dajObrazokVrstvy(vrstva);
				sprite->setPosition(sf::Vector2f(32.f * i + posunX, 32.f * j+posunY));
				okno->draw(*sprite);
			}
		}
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
		posunMapyX = offsetHracaX - 350;
		offsetHracaX = 350;
	}

	if (offsetHracaY > 350) {
		posunMapyY = offsetHracaY - 350;
		offsetHracaY = 350;
	}
	hrac->setOffsetX(offsetHracaX);
	hrac->setOffsetY(offsetHracaY);
	posunX = -posunMapyX;
	posunY = -posunMapyY;

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

void Mapa::update(double delta) {

	switch (smerPohybu)
	{
	case 0:
		break;
	case 1:
		if (pohybDelta < 32) {
			hrac->animaciaTick();
			pohybDelta++;
			posun(-1, 0);
		}
		else {
			hrac->setPolickoX(hrac->GetpolickoX() +1);
			mapa[hrac->GetpolickoX()][hrac->GetpolickoY()]->hracSkok(hrac);
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;
	case 2:
		if (pohybDelta < 32) {
			hrac->animaciaTick();
			pohybDelta++;
			posun(+1, 0);
		}
		else {
			hrac->setPolickoX(hrac->GetpolickoX() - 1);
			mapa[hrac->GetpolickoX()][hrac->GetpolickoY()]->hracSkok(hrac);
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;
	case 3:
		if (pohybDelta < 32) {
			hrac->animaciaTick();
			pohybDelta ++;
			posun(0, 1);
		}
		else {
			hrac->setPolickoY(hrac->GetpolickoY() - 1);
			mapa[hrac->GetpolickoX()][hrac->GetpolickoY()]->hracSkok(hrac);
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;
	case 4:
		if (pohybDelta < 32) {
			hrac->animaciaTick();
			pohybDelta++;
			posun(0, -1);
		}
		else {
			hrac->setPolickoY(hrac->GetpolickoY() +1);
			mapa[hrac->GetpolickoX()][hrac->GetpolickoY()]->hracSkok(hrac);
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;

	default:
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
	return mapa[x][y]->jePrechodne();
}

void Mapa::setSirkaVyska(int paSirka, int paVyska) {
	this->sirka = paSirka;
	this->vyska = paVyska;
}

void Mapa::nastavPolicko(int paX, int paY, Policko* paPolicko) {
	mapa[paX][paY] = paPolicko;
}