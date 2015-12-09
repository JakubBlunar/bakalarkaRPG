#include "Mapa.h"
#include "Policko.h"
#include "Hrac.h"
#include <iostream>

Mapa::Mapa(Hrac* hrac) {
	this->hrac = hrac;

	sf::Texture* textura = new sf::Texture();
	if (!textura->loadFromFile("Data/Grafika/Mapa/Textury/trava1.png", sf::IntRect(0, 0, 32, 32))) {
		std::cout << "Chyba nahravania textury policka" << std::endl;
	}



	int rozmer = 100;

	for (int i = 0; i < rozmer; i++)
	{
		for (int j = 0; j < rozmer; j++)
		{
			mapa[i][j] = new Policko(true);
			mapa[i][j]->nastavTexturu(textura, 0);
		}
	}

}



Mapa::~Mapa() {
	
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

	for (int vrstva = 0; vrstva < 4; vrstva++) {

		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				sprite = mapa[i][j]->dajObrazokVrstvy(vrstva);
				sprite->setPosition(sf::Vector2f(32.f * i + posunX, 32.f * j+posunY));
				okno->draw(*sprite);
			}
		}
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
			smerPohybu = 0;
			pohybDelta = 0;
		}
		break;
	case 3:
		if (pohybDelta < 32) {
			hrac->animaciaTick();
			pohybDelta++;
			posun(0, 1);
		}
		else {
			hrac->setPolickoY(hrac->GetpolickoY() - 1);
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
	hybeSa = true;
}

void Mapa::posunHore() {
	pohybDelta = 0;
	smerPohybu = 3;
	hybeSa = true;
}

void Mapa::posunDole() {
	pohybDelta = 0;
	smerPohybu = 4;
	hybeSa = true;
}

int Mapa::Getsmerpohybu() {
	return smerPohybu;
}