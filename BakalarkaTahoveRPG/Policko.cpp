#include "Policko.h"
#include "Vrstva.h"
#include <iostream>

Policko::Policko(bool paPriechodne) {
	priechodne = paPriechodne;

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
