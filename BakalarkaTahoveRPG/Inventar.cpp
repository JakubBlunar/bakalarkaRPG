#include <iostream>

#include "Inventar.h"
#include "Predmet.h"
#include "Pouzitelny.h"
#include "Oblecenie.h"
#include "Zbran.h"
#include "Elixir.h"

Inventar::Inventar() {
	pocetZlata = 0;

	kapacita = 36;
	Pouzitelny* zbran = new Zbran("Katana", 9, "wp1", 100,1,1,5,2000);
	Pouzitelny* brnenie = new Oblecenie("Ruth brnenie", 3, "ch1", 3,1);
	Pouzitelny* stit = new Zbran("Tower stit", 11, "st1", 11,1,0,0,10000);
	Pouzitelny* ramena = new Oblecenie("Ruth ramena", 2, "sh1", 3, 1);
	Pouzitelny* helma = new Oblecenie("Ruthless helm", 1, "hm1", 3, 1);
	Pouzitelny* nohavice = new Oblecenie("Zlate nohavice", 4, "lg1", 3, 1);
	Pouzitelny* rukavice = new Oblecenie("Platove rukavice", 7, "gt1", 3, 1);
	Pouzitelny* topanky = new Oblecenie("Platovane topanky", 8, "bt1", 3, 1);
	Pouzitelny* nahrdelnik = new Oblecenie("Zlaty nahrdelnik", 5, "nc1", 3, 1);
	Pouzitelny* prsten = new Oblecenie("Prsten sily", 6, "pr1", 3, 1);
	stit->Setarmor(25);

	Pouzitelny* elixir = new Elixir("Maly Hp elixir", 12, "elixir", 5000, 1, "hp", 50);
	zbran->Setsila(3);
	zbran->SetsilaMult(0.05);
	

	brnenie->Setarmor(15);
	brnenie->SetarmorMult(0.03);
	brnenie->Setinteligencia(3);
	brnenie->SetinteligenciaMult(0.01);
	brnenie->Sethp(5);
	try {
	
		pridajPredmet(zbran);
		pridajPredmet(brnenie);
		pridajPredmet(stit);
		pridajPredmet(ramena);
		pridajPredmet(helma);
		pridajPredmet(nohavice);
		pridajPredmet(topanky);
		pridajPredmet(nahrdelnik);
		pridajPredmet(prsten);
		pridajPredmet(rukavice);
		pridajPredmet(elixir);
		pridajPredmet(new Zbran("Katana", 9, "wp1", 100, 1, 1, 5, 1000));
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
	for (auto &predmet : predmety)
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

Predmet* Inventar::dajPredmetNaIndexe(int i) {
	return predmety.at(i);
}

int Inventar::Getkapacita() {
	return kapacita;
}
void Inventar::Setkapacita(int paNova) {
	kapacita = paNova;
}