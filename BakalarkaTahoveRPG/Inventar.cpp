#include <iostream>

#include "Inventar.h"
#include "Predmet.h"
#include "Zbran.h"

#include "Loader.h"
#include "Hra.h"
#include "PopupOkno.h"
#include "Stav.h"
#include "Hrac.h"
#include "QuestManager.h"

Inventar::Inventar(int kapacita) {
	this->pocetZlata = 300;
	this->kapacita = 65;
	this->pridajPredmet(new Zbran("gm weapon", 10, "Twohand_sword/2", 100, 1, 100, 200, 500),false);
}



Inventar::~Inventar() {

}


int Inventar::Getzlato() const
{
	return pocetZlata;
}

void Inventar::Setzlato(int paPocet) {
	pocetZlata = paPocet;
}

void Inventar::pridajZlato(int paPocet) {
	pocetZlata += paPocet;
}


bool Inventar::maDostatokZlata(int potrebne) const
{
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

int Inventar::pocetPredmetov() const
{
	return predmety.size();
}


void Inventar::pridajPredmet(Predmet* predmet,bool loot){
	if (static_cast<signed int>(predmety.size()) < kapacita) {
		predmety.push_back(predmet);
		if (loot) {
			Loader::Instance()->Gethra()->GetHrac()->Getmanazerquestov()->udalost(QuestEvent::VYHODENIE_PREDMETU, predmet);
		}
	}
	else {
		Loader::Instance()->Gethra()->dajStav("hranieHry")->zobrazPopup(new PopupOkno("Inventory is full!"));
		throw 1;
	}
}

void Inventar::zmazPredmet(Predmet* predmet) {
	predmety.erase(std::remove(predmety.begin(), predmety.end(), predmet), predmety.end());
	Loader::Instance()->Gethra()->GetHrac()->Getmanazerquestov()->udalost(QuestEvent::VYHODENIE_PREDMETU, predmet);
}

void Inventar::zmazPredmet(std::string nazovPredmetu) {
	std::vector<Predmet*> naZmazanie;
	for (unsigned int i = 0; i < predmety.size(); i++) {
		if (predmety.at(i)->Getmeno() == nazovPredmetu) {
			naZmazanie.push_back(predmety.at(i));
		}
	}
	
	Predmet* predmet = nullptr;
	while (naZmazanie.size() > 0) {
		predmet = naZmazanie.back();
		naZmazanie.pop_back();
		zmazPredmet(predmet);
	}

	Loader::Instance()->Gethra()->GetHrac()->Getmanazerquestov()->udalost(QuestEvent::VYHODENIE_PREDMETU, predmet);
}

Predmet* Inventar::dajPredmetNaIndexe(int i) {
	return predmety.at(i);
}

int Inventar::Getkapacita() const
{
	return kapacita;
}
void Inventar::Setkapacita(int paNova) {
	kapacita = paNova;
}