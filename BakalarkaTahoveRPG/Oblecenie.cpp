#include "Oblecenie.h"

#include <iostream>

#include "Hrac.h"
#include "Inventar.h"

Oblecenie::Oblecenie(std::string meno, int typ, std::string paObrazok, int cena):Pouzitelny(meno, typ, paObrazok, cena) {

}



Oblecenie::~Oblecenie() {

}


void Oblecenie::pouzi(Hrac* hrac) {
	std::cout << "Pouzivam" << Getmeno() << std::endl;
	//hrac->Getinventar()->zmazPredmet(this);
}