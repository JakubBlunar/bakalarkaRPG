#include "Policko.h"
#include "Vrstva.h"

Policko::Policko(bool paPriechodne) {
	priechodne = paPriechodne;

	for (int i = 0; i < vrstvy.size(); i++) {
		vrstvy[i] = new Vrstva(32);
	}
}



Policko::~Policko() {
	for (int i = 0; i < vrstvy.size(); i++) {
		delete(vrstvy[i]);
	}
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

bool Policko::jePrechodne() {
	return priechodne;
}

void Policko::nastavTexturu(sf::Texture paTextura, int poradie) {
	vrstvy[poradie]->Setobrazok(paTextura);
}

