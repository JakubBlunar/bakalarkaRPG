
#include "Vrstva.h"


Vrstva::Vrstva() {
	obrazok = new sf::Sprite();
}



Vrstva::~Vrstva() {
	delete(obrazok);
}





sf::Sprite* Vrstva::Getobrazok() {
	return obrazok;
}


bool Vrstva::Ispriechodna() {
	return priechodna;
}


void Vrstva::Setobrazok(sf::Texture newVal) {
	obrazok->setTexture(newVal);
	obrazok->setTextureRect(sf::IntRect(0, 0, velkost, velkost));
}


void Vrstva::Setpriechodna(bool newVal) {
	priechodna = newVal;
}