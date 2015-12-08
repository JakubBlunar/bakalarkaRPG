#include "Animacia.h"
#include <string>

Animacia::Animacia(std::string cesta, int pocetObrazkov, int trvanie, int velkost) {
	aktObrazok = 0;
	this->pocetObrazkov = pocetObrazkov;
	this->trvanie = trvanie;
	this->velkostTextury = velkost;

	
	if (!textura.loadFromFile("image.png", sf::IntRect(0, 0, velkost, velkost)))
	{
		// error...
	}

	obrazok = new sf::Sprite();
	obrazok->setTexture(textura);
	obrazok->setTextureRect(sf::IntRect(aktObrazok*velkost, 0, aktObrazok*velkost + velkost, velkost));

}

Animacia::~Animacia() {
	delete(obrazok);
}

sf::Sprite* Animacia::dajObrazok() {
	obrazok->setTextureRect(sf::IntRect(aktObrazok*velkostTextury, 0, aktObrazok*velkostTextury + velkostTextury, velkostTextury));
	return obrazok;
}


void Animacia::reset() {
	aktObrazok = 0;
	trvanieCounter = 0;
}


void Animacia::tick() {
	trvanieCounter++;
}