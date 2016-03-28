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
	questDrop = new std::map< std::string,Predmet*>();
}

Nepriatel::~Nepriatel() {
	delete questDrop;
	delete statistika;
}

sf::Sprite* Nepriatel::Getobrazok() const
{
	return obrazok;
}


Statistika* Nepriatel::Getstatistika() const
{

	return statistika;
}

void Nepriatel::Setstatistika(Statistika* newVal) {

	statistika = newVal;
}

Akcia* Nepriatel::vyberAkciu(std::map<Akcia*,int>* cooldowny) const
{

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
		return new Akcia("Unknown spell", "neznamy", 1000, 0, 0, "Unknown spell", 0,AkciaTyp::MAGICKA);
	}

	

}
void Nepriatel::pridajDropItem(std::string paNazovQuestu, Predmet* paPredmet) const
{
	questDrop->insert_or_assign(paNazovQuestu, paPredmet);
}

std::map< std::string, Predmet*>* Nepriatel::dropQuestPredmetov() const
{
	return questDrop;
}
