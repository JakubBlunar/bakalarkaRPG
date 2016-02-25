#include "Efekt.h"



Efekt::Efekt(std::string paObrazok)
{
	const std::string cesta = "./Data/Grafika/Akcie/";
	if (!textura.loadFromFile(cesta + paObrazok + ".png", sf::IntRect(0,0,32, 32))) {

	}
	obrazok = new sf::Sprite();
	obrazok->setTexture(textura);
	this->trvanieDo = sf::Time::Zero;
}


Efekt::~Efekt()
{
	delete obrazok;
}

sf::Time Efekt::GettrvanieDo() {
	return trvanieDo;
}

void Efekt::setTrvanieDo(sf::Time paKoniec) {
	trvanieDo = paKoniec;
}


sf::Sprite* Efekt::Getobrazok() {
	return obrazok;
}