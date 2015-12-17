#include <iostream>

#include "Inventar.h"
#include "Predmet.h"

Inventar::Inventar() {
	kapacita = 18;
	try {
		pridajPredmet(new Predmet("Sword 1", 1, "zbran1", 100));
		pridajPredmet(new Predmet("Sword 2", 1, "zbran1", 1000));
		pridajPredmet(new Predmet("Sword 3", 1, "zbran1", 10000));
	}
	catch (int ex) {
		if (ex == 1) {
			std::cout << "inventar je plny" << std::endl;
		}
	}
}



Inventar::~Inventar() {

}


int Inventar::Getzlato() {
	return pocetZlata;
}

void Inventar::Setzlato(int paPocet) {
	pocetZlata = paPocet;
}

void Inventar::pridajZlato(int paPocet) {
	pocetZlata += paPocet;
}


bool Inventar::maDostatokZlata(int potrebne) {
	return (pocetZlata >= potrebne)? true:false;
}


int Inventar::pocetPredmetov(std::string meno) {
	return predmety.size();
}

int Inventar::pocetPredmetov() {
	return predmety.size();
}


void Inventar::pridajPredmet(Predmet* predmet){
	if ((signed int)predmety.size() < kapacita) {
		predmety.push_back(predmet);
	}
	else {
		throw 1;
	}
}

void Inventar::zmazPredmet(Predmet* predmet) {
	predmety.erase(std::remove(predmety.begin(), predmety.end(), predmet), predmety.end());
}

void Inventar::vyberPredmet(Predmet* predmet) {
	//predmety.erase(std::remove(predmety.begin(), predmety.end(), predmet), predmety.end());

	// ešte polozit na mapu atd atd
}


void Inventar::zdviholPredemt(Predmet* paPredmet) {

}

Predmet* Inventar::dajPredmetNaIndexe(int i) {
	return predmety.at(i);
}

int Inventar::Getkapacita() {
	return kapacita;
}
void Inventar::Setkapacita(int paNova) {
	kapacita = paNova;
}