#include "Poziadavka.h"
#include "Nepriatel.h"

#include "Loader.h"
#include "Hrac.h"
#include "Mapa.h"
#include "Hra.h"
#include "Inventar.h"

void Poziadavka::akcia(Nepriatel* nepriatel){}
void Poziadavka::akcia(string paMenoNepriatela) {}
void Poziadavka::akcia(Predmet* nepriatel) {}
void Poziadavka::dokoncenie(Hrac* paHrac) {}

PoziadavkaZabi::PoziadavkaZabi(std::string paKohoZabit, int paKolkokrat) {
	this->kohoZabit = paKohoZabit;
	this->kolkoZabit = paKolkokrat;
	this->pocetZabiti = 0;
}

void PoziadavkaZabi::akcia(Nepriatel* nepriatel) {
	Hrac* hrac = Loader::Instance()->Gethra()->Gethrac();
	if (!jeSplnena()) {
		if (nepriatel->Getmeno() == kohoZabit) {
				pocetZabiti++;
		}
	}
}

void PoziadavkaZabi::akcia(string paMenoNepriatela) {
	if (!jeSplnena()) {
		if (paMenoNepriatela == kohoZabit) {
			pocetZabiti++;
		}
	}
}

bool PoziadavkaZabi::jeSplnena() {
	if (pocetZabiti == kolkoZabit) {
		return true;
	}
	return false;
}

string PoziadavkaZabi::Getkohozabit() const
{
	return kohoZabit;
}
int PoziadavkaZabi::Getaktualnypocetzabitych() const
{
	return pocetZabiti;
}

void PoziadavkaZabi::Setpocetzabiti(int paPocet) {
	pocetZabiti = paPocet;
}


string PoziadavkaZabi::Getpopis() {
	return "Progres: " + kohoZabit + " - " + std::to_string(pocetZabiti) + " / " + std::to_string(kolkoZabit);
}


PoziadavkaLoot::PoziadavkaLoot(std::string paMenoPredmetu, int pocetKs) {
	menoPredmetu = paMenoPredmetu;
	potrebneMnozstvo = pocetKs;
}

void PoziadavkaLoot::akcia(Predmet* paPredmet) {

}


bool PoziadavkaLoot::jeSplnena() {
	Inventar* inv = Loader::Instance()->Gethra()->Gethrac()->Getinventar();
	if (inv->pocetPredmetov(menoPredmetu) < potrebneMnozstvo) {
		return false;
	}
	return true;
}

string PoziadavkaLoot::Getpopis() {
	Inventar* inv = Loader::Instance()->Gethra()->Gethrac()->Getinventar();
	int aktPocet = inv->pocetPredmetov(menoPredmetu);
	return "Progres: " + menoPredmetu + " - " + std::to_string(aktPocet) + " / " + std::to_string(potrebneMnozstvo);	
}

void PoziadavkaLoot::dokoncenie(Hrac* paHrac) {
	Inventar* inv = paHrac->Getinventar();
	inv->zmazPredmet(menoPredmetu);
}