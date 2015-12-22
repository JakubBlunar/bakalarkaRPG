#include "Policko.h"
#include "Vrstva.h"
#include <iostream>
#include "Npc.h"

Policko::Policko(bool paPriechodne) {
	priechodne = paPriechodne;
	npc = nullptr;

	for (unsigned int i = 0; i < (unsigned int)vrstvy.size(); i++) {
		vrstvy[i] = new Vrstva(32);
	}
}



Policko::~Policko() {
	for (unsigned int i = 0; i < (unsigned int)vrstvy.size(); i++) {
		delete(vrstvy[i]);
	}
}

sf::Sprite* Policko::dajObrazokVrstvy(int poradie) {
	return vrstvy[poradie]->Getobrazok();
}

void Policko::hracSkok(Hrac* hrac) {
	//std::cout << "hrac skocil na policko" << std::endl;
}


void Policko::interakcia(Hrac* hrac) {
	std::cout << "hrac interakcia policko" << std::endl;
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