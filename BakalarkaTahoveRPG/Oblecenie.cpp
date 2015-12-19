#include "Oblecenie.h"

#include <iostream>
#include <map>

#include "Hrac.h"
#include "Inventar.h"
#include "Statistika.h"

Oblecenie::Oblecenie(std::string meno, int typ, std::string paObrazok, int cena, int paUroven):Pouzitelny(meno, typ, paObrazok, cena,paUroven) {

}



Oblecenie::~Oblecenie() {

}


void Oblecenie::pouzi(Hrac* hrac) {

	if (hrac->Getstatistika()->dajUroven() < this->Geturoven()) return;

	std::map<int, Predmet*>* oblecene = hrac->Getstatistika()->Getoblecene();
	Predmet* docasny;

	if (!Pouzitelny::Isobleceny()) {
		int typ = Gettyp();
		if (oblecene->count(typ)){
			docasny = oblecene->at(typ);
			oblecene->erase(typ);
			oblecene->insert(std::pair<int, Predmet*>(typ, this));
			hrac->Getinventar()->pridajPredmet(docasny);
		}
		else {
			oblecene->insert(std::pair<int, Predmet*>(typ, this));
		}
		hrac->Getinventar()->zmazPredmet(this);
		Pouzitelny::Setobleceny(true);
	}
	else {

	}
	//hrac->Getinventar()->zmazPredmet(this);
}