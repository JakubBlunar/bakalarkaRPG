#include "Akcia.h"

#include <iostream>
#include "Statistika.h"

Akcia::Akcia(std::string meno, std::string obrazok, int casCastenia, int cooldown, int trvanie, std::string popis,int mana, AkciaTyp typ) {
	const std::string akcie_cesta = "./Data/Grafika/Akcie/";
	this->cenaMany = mana;
	this->meno = meno;
	this->casCastenia = casCastenia;
	this->cooldown = cooldown;
	this->trvanie = trvanie;
	this->popis = popis;
	this->typ = typ;
	this->obrazok = new sf::Sprite();
	this->textura = new sf::Texture();
	if (!textura->loadFromFile(akcie_cesta + "" + obrazok + ".png", sf::IntRect(0, 0, 32, 32))) {
		
	}
	this->textura->setSmooth(true);
	this->obrazok->setTexture(*textura);
	
}

Akcia::~Akcia() {
	delete obrazok;
	delete textura;
}

std::string Akcia::dajPopis() {

	return  popis;
}


int Akcia::GetcasCastenia() {

	return casCastenia;
}


int Akcia::Getcooldown() {

	return cooldown;
}


std::string Akcia::Getmeno() {

	return meno;
}


sf::Sprite* Akcia::Getobrazok() {

	return obrazok;
}


int Akcia::Gettrvanie() {

	return trvanie;
}

int Akcia::Getcenamany() {
	return cenaMany;
}

std::string Akcia::vykonajSa(Statistika* statHrac, Statistika* statNepriatel,sf::Time aktCas) {
	statHrac->Setmp(statHrac->Getmp() - cenaMany);
	return "";
}