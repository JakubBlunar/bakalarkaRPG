#include "Poziadavka.h"
#include "Nepriatel.h"

#include "Loader.h"
#include "Hrac.h"
#include "Mapa.h"
#include "Hra.h"
#include "Inventar.h"

void Poziadavka::akcia(Nepriatel* nepriatel){}
void Poziadavka::akcia(Predmet* nepriatel) {}
void Poziadavka::dokoncenie(Hrac* paHrac) {};

PoziadavkaZabi::PoziadavkaZabi(std::string paKohoZabit, int paKolkokrat, string kde) {
	this->kohoZabit = paKohoZabit;
	this->kolkoZabit = paKolkokrat;
	this->pocetZabiti = 0;
	this->menoMapy = kde;
}

void PoziadavkaZabi::akcia(Nepriatel* nepriatel) {
	Hrac* hrac = Loader::Instance()->Gethra()->GetHrac();
	if (nepriatel->Getmeno() == kohoZabit) {
		if (menoMapy == "") {
			pocetZabiti++;
		}
		else {
			if (menoMapy == hrac->getMapa()->Getmeno()) pocetZabiti++;
		}
	}
}


bool PoziadavkaZabi::jeSplnena() {
	if (pocetZabiti == kolkoZabit) {
		return true;
	}
	else return false;
}

string PoziadavkaZabi::Getpopis() {
	return "Progres: " + kohoZabit + " - " + std::to_string(pocetZabiti) + " z " + std::to_string(kolkoZabit);
}


PoziadavkaLoot::PoziadavkaLoot(std::string paMenoPredmetu, int pocetKs) {
	menoPredmetu = paMenoPredmetu;
	potrebneMnozstvo = pocetKs;
}

void PoziadavkaLoot::akcia(Predmet* paPredmet) {

}


bool PoziadavkaLoot::jeSplnena() {
	Inventar* inv = Loader::Instance()->Gethra()->GetHrac()->Getinventar();
	if (inv->pocetPredmetov(menoPredmetu) < potrebneMnozstvo) {
		return false;
	}
	else {
		return true;
	}
}

string PoziadavkaLoot::Getpopis() {
	Inventar* inv = Loader::Instance()->Gethra()->GetHrac()->Getinventar();
	int aktPocet = inv->pocetPredmetov(menoPredmetu);
	return "Progres: " + menoPredmetu + " - " + std::to_string(aktPocet) + " z " + std::to_string(potrebneMnozstvo);	
}

void PoziadavkaLoot::dokoncenie(Hrac* paHrac) {
	Inventar* inv = paHrac->Getinventar();
	inv->zmazPredmet(menoPredmetu);
}