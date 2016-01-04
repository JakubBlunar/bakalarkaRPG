#include "Elixir.h"

#include "Hrac.h"
#include "Inventar.h"
#include "Statistika.h"

Elixir::Elixir(std::string meno, int typ, std::string paObrazok, int cena, int paUroven, std::string zvysCo, int paoKolko) :Pouzitelny(meno, typ, paObrazok, cena, paUroven) {
	this->stat = zvysCo;
	this->oKolko = paoKolko;
}



Elixir::~Elixir() {
	Pouzitelny::~Pouzitelny();
}


void Elixir::pouzi(Hrac* hrac) {

	if (hrac->Getstatistika()->dajUroven() < this->Geturoven()) return;
	hrac->Getstatistika()->zvysStat(oKolko, stat);
	hrac->Getinventar()->zmazPredmet(this);

}