#include <iostream>

#include "Predmet.h"



Predmet::Predmet(std::string meno, int typ, std::string paObrazok, int cena) {
	
	const std::string predmety_cesta = "Data/Grafika/Predmety/";
	
	this->meno = meno;
	this->typ = typ;
	this->cena = cena;
	obrazok = new sf::Sprite();
	
	textura = new sf::Texture();
	if (!textura->loadFromFile(predmety_cesta + "" + paObrazok+".png", sf::IntRect(0, 0, 32, 32))) {
		
	}
	textura->setSmooth(true);
	obrazok->setTexture(*textura);
	
}



Predmet::~Predmet() {
	delete obrazok;
	delete textura;
}



int Predmet::Gettyp() {
	return typ;
}

int Predmet::Getcena() {

	return cena;
}


std::string Predmet::Getmeno() {

	return meno;
}


sf::Sprite* Predmet::Getobrazok() {

	return obrazok;
}


void Predmet::pouzi(Hrac* hrac) {

}


void Predmet::Setcena(int newVal) {

	cena = newVal;
}


void Predmet::Setmeno(std::string newVal) {

	meno = newVal;
}


void Predmet::Setobrazok(sf::Sprite* newVal) {

	obrazok = newVal;
}

void Predmet::Settyp(int newVal) {
	typ = newVal;
}

std::string Predmet::Getstringovytyp() {
	switch (typ)
	{
	case (1) :
		return "Zbran (1h)";
	case (2) :
		return "Zbran (2h)";
	case (3) :
		return "Stit";
	case (4) :
		return "Brnenie";
	default:
		return "ine";
		break;
	}
}