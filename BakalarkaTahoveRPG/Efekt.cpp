#include "Efekt.h"



Efekt::Efekt(std::string paObrazok)
{
	const std::string cesta = "./Data/Grafika/Akcie/";
	if (!textura.loadFromFile(cesta + paObrazok + ".png", sf::IntRect(0,0,32, 32))) {

	}
	obrazok = new sf::Sprite();
	obrazok->setTexture(textura);
	this->trvanieDo = sf::Time::Zero;
	statistikaNaPocitanie = nullptr;
}


Efekt::~Efekt()
{
	delete obrazok;
}

sf::Time Efekt::GettrvanieDo() const
{
	return trvanieDo;
}

void Efekt::setTrvanieDo(sf::Time paKoniec) {
	trvanieDo = paKoniec;
}


sf::Sprite* Efekt::Getobrazok() const
{
	return obrazok;
}

void  Efekt::Setstatistikanapocitanie(Statistika* statistika) {
	statistikaNaPocitanie = statistika;
}