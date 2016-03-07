#include "Policko.h"
#include "Vrstva.h"
#include <iostream>
#include "Npc.h"
#include "Predmet.h"

Policko::Policko(bool paPriechodne) {
	priechodne = paPriechodne;
	npc = nullptr;
	polozenePredmety = new std::vector<Predmet*>();

	int kedyZmazatPredmety = -1; // nemazaù

	for (unsigned int i = 0; i < (unsigned int)vrstvy.size(); i++) {
		vrstvy[i] = new Vrstva(32);
	}
}



Policko::~Policko() {
	for (unsigned int i = 0; i < (unsigned int)vrstvy.size(); i++) {
		delete(vrstvy[i]);
	}
	delete polozenePredmety;
}

sf::Sprite* Policko::dajObrazokVrstvy(int poradie) {
	return vrstvy[poradie]->Getobrazok();
}

void Policko::hracSkok(Hrac* hrac) {
	//std::cout << "Pocet predmetov na policku" << polozenePredmety->size() << std::endl;
}


void Policko::interakcia(Hrac* hrac) {
	//std::cout << "hrac interakcia policko" << std::endl;
}

void Policko::Setpriechodne(bool paPriechodne) {
	priechodne = paPriechodne;
}

bool Policko::jePrechodne() {
	return priechodne;
}

void Policko::nastavTexturu(sf::Texture* paTextura, int poradie) {
	vrstvy[poradie]->Setobrazok(paTextura);
}

void Policko::Setnpc(Npc* paNpc) {
	npc = paNpc;
}

Npc* Policko::Getnpc() {
	return npc;
}

void Policko::polozPredmet(Predmet* paPredmet,sf::Time kedy) {
	casMazaniaPredmetov = kedy.asSeconds() + 600.f;// o 10 minut
	polozenePredmety->push_back(paPredmet);
}

std::vector<Predmet*>* Policko::dajPolozenePredmety() {
	return polozenePredmety;
}

bool Policko::polozenyPredmet() {
	return (polozenePredmety->size() > 0) ? true : false;
}

float Policko::kedyZmazatPredmety() {
	return casMazaniaPredmetov;
}

void Policko::zmazPolozenePredmety() {
	// neviem Ëi vola deötruktory predmetov
	polozenePredmety->clear();
	casMazaniaPredmetov = -1;
}
