#include <iostream>

#include "Predmet.h"



Predmet::Predmet(std::string meno, int typ, std::string paObrazok, int cena,int paUroven) {
	
	std::string predmety_cesta = "Data/Grafika/Predmety/";
	this->sObrazok = paObrazok;
	this->uroven = paUroven;
	this->meno = meno;
	this->typ = typ;
	this->cena = cena;

	switch (typ)
	{
	case (1) :
		predmety_cesta += "Helma";
		break;
	case (2) :
		predmety_cesta += "Ramena";
		break;
	case (3) :
		predmety_cesta += "Brnenie";
		break;
	case (4) :
		predmety_cesta += "Nohavice";
		break;
	case (5) :
		predmety_cesta += "Nahrdelnik";
		break;
	case (6) :
		predmety_cesta += "Prsten";
		break;
	case (7) :
		predmety_cesta += "Rukavice";
		break;
	case (8) :
		predmety_cesta += "Topanky";
		break;
	case (9) :
		predmety_cesta += "Zbran1h";
		break;
	case (10) :
		predmety_cesta += "Zbran2h";
		break;
	case (11) :
		predmety_cesta += "Stit";
		break;
	case(12) :
		predmety_cesta += "Elixir";
		break;
	case(13) :
		predmety_cesta += "Ostatne";
		break;
	}
	predmety_cesta += "/";
	
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


int Predmet::Geturoven() {
	return uroven;
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
		return "Helma";
	case (2) :
		return "Ramena";
	case (3) :
		return "Brnenie";
	case (4) :
		return "Nohavice";
	case (5) :
		return "Nahrdelnik";
	case (6) :
		return "Prsten";
	case (7) :
		return "Rukavice";
	case (8) :
		return "Topanky";
	case (9) :
		return "Zbran (1h)";
	case (10) :
		return "Zbran (2h)";
	case (11) :
		return "Stit";
	case(12) :
		return "Elixir";
	case(13) :
		return "Ulohovy predmet";
	default:
		return "ine";
		break;
	}
}

Predmet* Predmet::copy() {
	return new Predmet(meno, typ, sObrazok, cena, uroven);
}