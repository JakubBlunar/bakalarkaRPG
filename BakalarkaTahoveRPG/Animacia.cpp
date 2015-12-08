#include "Animacia.h"
#include <string>
#include <iostream>

Animacia::Animacia(std::string cesta, int pocetObrazkov, int trvanie, int velkost) {
	aktObrazok = 0;
	this->pocetObrazkov = pocetObrazkov;
	this->trvanie = trvanie;
	this->velkostTextury = velkost;

	
	if (!textura.loadFromFile(cesta, sf::IntRect(0, 0, velkost*pocetObrazkov, velkost)))
	{
		std::cout << "Chyba nacitavania textury " << cesta << std::endl;
		exit(1);
	}

	obrazok = new sf::Sprite();
	obrazok->setTexture(textura);
	obrazok->setTextureRect(sf::IntRect(aktObrazok*velkost, 0, velkost, velkost));

}

Animacia::~Animacia() {
	delete(obrazok);
}

sf::Sprite* Animacia::dajObrazok() {
	obrazok->setTextureRect(sf::IntRect(aktObrazok*velkostTextury, 0, velkostTextury, velkostTextury));
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