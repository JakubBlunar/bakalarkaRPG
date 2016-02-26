#include "Nepriatel.h"
#include <random>
#include "Akcia.h"
#include <iostream>

Nepriatel::Nepriatel(std::string paMeno, std::string paObrazok, DialogovyStrom* dialog,Statistika* paStatistika):Npc(paMeno,dialog) {
	statistika = paStatistika;
	
	const std::string cesta = "./Data/Grafika/Potvory/";
	if (!textura.loadFromFile(cesta + paObrazok + ".png", sf::IntRect(0, 0, 256, 256))) {

	}
	obrazok = new sf::Sprite();
	obrazok->setTexture(textura);
	
}

Nepriatel::~Nepriatel() {
	delete statistika;
}

sf::Sprite* Nepriatel::Getobrazok() {
	return obrazok;
}

/*
LogikaNpc Nepriatel::Getlogika(){

return logika;
}
*/

Statistika* Nepriatel::Getstatistika() {

	return statistika;
}

/*
void Nepriatel::Setlogika(LogikaNpc newVal){

logika = newVal;
}
*/

void Nepriatel::Setstatistika(Statistika* newVal) {

	statistika = newVal;
}

Akcia* Nepriatel::vyberAkciu(std::map<Akcia*,int>* cooldowny) {

	if (statistika->Getakcie()->size() > 0) {
		if (cooldowny->size() >= statistika->Getakcie()->size()) {
			return nullptr;
		}

		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> uni(0, statistika->Getakcie()->size() - 1);
		int index = uni(rng);


		if (statistika->Getakcie()->at(index)->Getcenamany() <= statistika->Getmp()) {
			return  statistika->Getakcie()->at(index);
		}
		else {
			unsigned int i = 0;
			bool najdene = false;
			while(!najdene){
				if (statistika->Getakcie()->at(i)->Getcenamany() <= statistika->Getmp()) {
					return statistika->Getakcie()->at(i);
				}
				i++;
				if (i >= statistika->Getakcie()->size()) { najdene = true; }	
			}
			return nullptr;
		}
	}
	else {
		return new Akcia("Neznama akcia", "neznamy", 1000, 0, 0, "Neznamy spell", 0,AkciaTyp::MAGICKA);
	}

}