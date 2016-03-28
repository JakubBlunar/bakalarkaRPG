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


int Predmet::Geturoven() const
{
	return uroven;
}

int Predmet::Gettyp() const
{
	return typ;
}

int Predmet::Getcena() const
{

	return cena;
}


std::string Predmet::Getmeno() const
{

	return meno;
}


sf::Sprite* Predmet::Getobrazok() const
{

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

std::string Predmet::Getstringovytyp() const
{
	switch (typ)
	{
	case (1) :
		return "Helm";
	case (2) :
		return "Shoulders";
	case (3) :
		return "Chest";
	case (4) :
		return "Legs";
	case (5) :
		return "Necklace";
	case (6) :
		return "Ring";
	case (7) :
		return "Hands";
	case (8) :
		return "Boots";
	case (9) :
		return "Weapon (1h)";
	case (10) :
		return "Weapon (2h)";
	case (11) :
		return "Shield";
	case(12) :
		return "Potion";
	case(13) :
		return "Quest item";
	default:
		return "Other";
	}
}

Predmet* Predmet::copy() {
	return new Predmet(meno, typ, sObrazok, cena, uroven);
}

std::string Predmet::Getsobrazok() const
{
	return sObrazok;
}
