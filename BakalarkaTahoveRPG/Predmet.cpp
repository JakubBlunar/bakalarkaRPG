#include "Predmet.h"


Predmet::Predmet() {

}



Predmet::~Predmet() {

}





int Predmet::Getcena() {

	return cena;
}


std::string Predmet::Getmeno() {

	return meno;
}


sf::Image* Predmet::Getobrazok() {

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


void Predmet::Setobrazok(sf::Image* newVal) {

	obrazok = newVal;
}