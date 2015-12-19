#include <iostream>

#include "Inventar.h"
#include "Predmet.h"
#include "Pouzitelny.h"
#include "Oblecenie.h"
#include "Zbran.h"

Inventar::Inventar() {
	kapacita = 36;
	Pouzitelny* o = new Zbran("Sword 1", 1, "zbran1", 100,1,5);
	Pouzitelny* brnenie = new Oblecenie("Brnenie1", 4, "brnenie1", 3);
	Pouzitelny* stit = new Zbran("Stit", 3, "stit", 3,0,0);
	
	brnenie->Setarmor(15);
	brnenie->Sethp(5);
	try {
		pridajPredmet(o);
		pridajPredmet(new Zbran("Sword 2", 1, "zbran1", 1000,2,6));
		pridajPredmet(new Zbran("Sword 3", 2, "zbran1", 10000,3,7));
		pridajPredmet(brnenie);
		pridajPredmet(stit);
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
	int counter = 0;
	for (auto &predmet : predmety) // access by reference to avoid copying
	{
		if (predmet->Getmeno() == meno)
		{
			counter++;
		}
	}
	return counter;
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