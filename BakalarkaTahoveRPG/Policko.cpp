#include "Policko.h"
#include "Vrstva.h"
#include <iostream>
#include "Npc.h"
#include "Predmet.h"

Policko::Policko(bool paPriechodne) {
	priechodne = paPriechodne;
	npc = nullptr;
	polozenePredmety = new std::vector<Predmet*>();
	casMazaniaPredmetov = NULL;

	for (unsigned int i = 0; i < static_cast<unsigned int>(vrstvy.size()); i++) {
		vrstvy[i] = new Vrstva(32);
	}
}



Policko::~Policko() {
	for (unsigned int i = 0; i < static_cast<unsigned int>(vrstvy.size()); i++) {
		delete(vrstvy[i]);
	}
	delete polozenePredmety;
}

sf::Sprite* Policko::dajObrazokVrstvy(int poradie) {
	return vrstvy[poradie]->Getobrazok();
}

void Policko::hracSkok(Hrac* hrac) {
	
}


void Policko::interakcia(Hrac* hrac) {
	
}

void Policko::Setpriechodne(bool paPriechodne) {
	priechodne = paPriechodne;
}

bool Policko::jePrechodne() const
{
	return priechodne;
}

void Policko::nastavTexturu(sf::Texture* paTextura, int poradie) {
	vrstvy[poradie]->Setobrazok(paTextura);
}

void Policko::Setnpc(Npc* paNpc) {
	npc = paNpc;
}

Npc* Policko::Getnpc() const
{
	return npc;
}

void Policko::polozPredmet(Predmet* paPredmet,sf::Time kedy) {
	casMazaniaPredmetov = kedy.asSeconds() + 600.f;// o 10 minut
	polozenePredmety->push_back(paPredmet);
}

std::vector<Predmet*>* Policko::dajPolozenePredmety() const
{
	return polozenePredmety;
}

bool Policko::polozenyPredmet() const
{
	return (polozenePredmety->size() > 0) ? true : false;
}

float Policko::kedyZmazatPredmety() const
{
	return casMazaniaPredmetov;
}

void Policko::zmazPolozenePredmety(){
	polozenePredmety->clear();
	casMazaniaPredmetov = -1;
}
