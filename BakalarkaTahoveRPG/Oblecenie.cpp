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
	Pouzitelny* docasny;

	if (!Pouzitelny::Isobleceny()) {
		int typ = Gettyp();
			if (oblecene->count(typ)) {
				docasny = (Pouzitelny*)oblecene->at(typ);
				oblecene->erase(typ);
				oblecene->insert(std::pair<int, Predmet*>(typ, this));

				docasny->Setobleceny(false);
				hrac->Getinventar()->pridajPredmet(docasny);
			}
			else {
				oblecene->insert(std::pair<int, Predmet*>(typ, this));
			}
			
			hrac->Getinventar()->zmazPredmet(this);
			Pouzitelny::Setobleceny(true);
	}
	else {
		Pouzitelny::Setobleceny(false);
		oblecene->erase(this->Gettyp());
		hrac->Getinventar()->pridajPredmet(this);
	}
}

Oblecenie* Oblecenie::copy() {
	Oblecenie* nove = new Oblecenie(meno, typ, sObrazok, cena, uroven);
	nove->Setarmor(armor);
	nove->SetarmorMult(armorMult);
	nove->Sethp(hp);
	nove->SethpMult(hpMult);
	nove->Setinteligencia(inteligencia);
	nove->SetinteligenciaMult(inteligenciaMult);
	nove->Setmp(mp);
	nove->SetmpMult(mpMult);
	nove->Setrychlost(rychlost);
	nove->SetrychlostMult(rychlostMult);
	nove->Setsila(sila);
	nove->SetsilaMult(silaMult);
	return nove;
}