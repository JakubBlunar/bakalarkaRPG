
#include "Vrstva.h"

Vrstva::Vrstva(int paVelkost) {
	velkost = paVelkost;
	obrazok = new sf::Sprite();
}

Vrstva::Vrstva(sf::Texture paTextura, int paVelkost){
	obrazok = new sf::Sprite();
	velkost = paVelkost;
	obrazok->setTexture(paTextura);
	obrazok->setTextureRect(sf::IntRect(0, 0, velkost, velkost));
}



Vrstva::~Vrstva() {
	delete(obrazok);
}


sf::Sprite* Vrstva::Getobrazok() const
{
	return obrazok;
}


void Vrstva::Setobrazok(sf::Texture* newVal) const
{
	obrazok->setTexture(*newVal);
	obrazok->setTextureRect(sf::IntRect(0, 0, velkost, velkost));
}
