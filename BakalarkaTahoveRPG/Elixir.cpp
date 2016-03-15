#include "Elixir.h"

#include "Hrac.h"
#include "Inventar.h"
#include "Statistika.h"

Elixir::Elixir(std::string meno, int typ, std::string paObrazok, int cena, int paUroven, std::string zvysCo, int paoKolko) :Pouzitelny(meno, typ, paObrazok, cena, paUroven) {
	this->stat = zvysCo;
	this->oKolko = paoKolko;
}



Elixir::~Elixir() {
}


void Elixir::pouzi(Hrac* hrac) {

	if (hrac->Getstatistika()->dajUroven() < this->Geturoven()) return;
	hrac->Getstatistika()->zvysStat(oKolko, stat);
	hrac->Getinventar()->zmazPredmet(this);
	delete this;
}

std::string Elixir::dajInfo() {
	std::string info ="";
	//hp
	if (stat == "hp") {
		info += "Body zdravia";
	}
	//hpMax
	if (stat == "hpMax") {
		info += "Max Hp";
	}

	//mp
	if ( stat == "mp") {
		info += "Mana:";
	}

	//mpMax
	if (stat == "mpMax") {
		info += "Max Mp";
	}

	//sila
	if (stat == "sila") {
		info += "Sila";
	}

	//intel
	if (stat == "intel") {
		info += "Intelekt";
	}

	//rychlost
	if (stat == "rychlost") {
		info += "Rychlost";
	}

	//obrana
	if (stat == "obrana") {
		info += "Obrana";
	}
	
	if (oKolko >= 0) {
		info += "+" + std::to_string(oKolko);
	}
	else {
		info += "-" + std::to_string(oKolko);
	}

	return info;
}

Elixir* Elixir::copy() {
	return new Elixir(meno,typ,sObrazok,cena,uroven,stat,oKolko);
}

std::string Elixir::Getstat() {
	return stat;
}

int Elixir::Getokolko() {
	return oKolko;
}