#include <iostream>

#include "Inventar.h"
#include "Predmet.h"
#include "Pouzitelny.h"
#include "Oblecenie.h"
#include "Zbran.h"

Inventar::Inventar() {
	kapacita = 36;
	Pouzitelny* o = new Zbran("Gladius", 9, "zbran1", 100,10,1,5);
	Pouzitelny* brnenie = new Oblecenie("Brnenie1", 3, "brnenie1", 3,1);
	Pouzitelny* stit = new Zbran("Stit", 3, "stit", 11,1,0,0);
	
	stit->Setarmor(25);

	o->Setsila(3);
	o->SetsilaMult(0.05);
	

	brnenie->Setarmor(15);
	brnenie->SetarmorMult(0.03);
	brnenie->Setinteligencia(3);
	brnenie->SetinteligenciaMult(0.01);
	brnenie->Sethp(5);
	try {
		pridajPredmet(o);
		pridajPredmet(new Zbran("Sword 2", 9, "zbran1", 1000,1,2,6));
		pridajPredmet(new Zbran("Sword 3", 10, "zbran1", 10000,1,3,7));
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