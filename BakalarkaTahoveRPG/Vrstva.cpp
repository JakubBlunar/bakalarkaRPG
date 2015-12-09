
#include "Vrstva.h"


Vrstva::Vrstva(sf::Texture paTextura, bool paPriechodna, int paVelkost){
	obrazok = new sf::Sprite();
	velkost = paVelkost;
	priechodna = paPriechodna;
	obrazok->setTexture(paTextura);
	obrazok->setTextureRect(sf::IntRect(0, 0, velkost, velkost));
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