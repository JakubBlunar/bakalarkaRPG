#include "Animacia.h"
#include <string>
#include <iostream>

Animacia::Animacia(std::string cesta, int pocetObrazkov, int trvanie, int velkostX, int velkostY) {
	aktObrazok = 0;
	this->pocetObrazkov = pocetObrazkov;
	this->trvanie = trvanie;
	this->velkostTexturyX = velkostX;
	this->velkostTexturyY = velkostY;

	
	if (!textura.loadFromFile(cesta, sf::IntRect(0, 0, velkostX*pocetObrazkov, velkostY)))
	{
		std::cout << "Chyba nacitavania textury " << cesta << std::endl;
		exit(1);
	}

	obrazok = new sf::Sprite();
	obrazok->setTexture(textura);
	obrazok->setTextureRect(sf::IntRect(aktObrazok*velkostX, 0, velkostX, velkostY));

}

Animacia::~Animacia() {
	delete(obrazok);
}

sf::Sprite* Animacia::dajObrazok() {
	obrazok->setTextureRect(sf::IntRect(aktObrazok*velkostTexturyX, 0, velkostTexturyX, velkostTexturyY));
	return obrazok;
}


void Animacia::reset() {
	aktObrazok = 0;
	trvanieCounter = 0;
}


void Animacia::tick() {
	trvanieCounter++;
	if (trvanieCounter >= trvanie) {
		aktObrazok++;
		if (aktObrazok >= pocetObrazkov) {
			aktObrazok = 0;
		}
		trvanieCounter = 0;
	}
}

int Animacia::GetvelkostX() {
	return velkostTexturyX;
}

int Animacia::GetvelkostY() {
	return velkostTexturyY;
}