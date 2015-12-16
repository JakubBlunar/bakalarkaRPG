///////////////////////////////////////////////////////////
//  Inventar.cpp
//  Implementation of the Class Inventar
//  Created on:      16-12-2015 20:50:14
//  Original author: Jakub Blunár
///////////////////////////////////////////////////////////

#include "Inventar.h"


Inventar::Inventar() {

}



Inventar::~Inventar() {

}





bool Inventar::maDostatokZlata(int aktualneZlato) {

	return false;
}


int Inventar::pocetPredmetov(std::string meno) {
	return predmety.size();
}


void Inventar::pridajPredmet(Predmet* predmet) {
	predmety.push_back(predmet);
}


void Inventar::vyberPredmet(Predmet* predmet) {
	//predmety.erase(std::remove(predmety.begin(), predmety.end(), predmet), predmety.end());

	// ešte polozit na mapu atd atd
}


void Inventar::zdviholPredemt(Predmet* paPredmet) {

}