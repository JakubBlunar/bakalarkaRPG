#include "QuestLoot.h"

#include <iostream>

#include "Hrac.h"
#include "Inventar.h"
#include "Loader.h"
#include "Hra.h"
#include "Predmet.h"

QuestLoot::QuestLoot(std::string paMeno,std::string paPopis,std::string paMenoPredmetu, int pocetKs, int pocetXp, int pocetZlata)
	:Quest(paMeno,paPopis,pocetXp,pocetZlata)
{
	menoPredmetu = paMenoPredmetu;
	potrebneMnozstvo = pocetKs;
}


QuestLoot::~QuestLoot()
{
}

void QuestLoot::lootnutiePredmetu(Predmet* paPredmet) {

	kontrola();

}


void QuestLoot::zabitieNpc(Nepriatel* paNepriatel) {
	kontrola();
}

void QuestLoot::dokonciSa(Hrac* paHrac) {
	kontrola();
	if (stav == StavQuestu::SPLNENIE_POZIADAVIEK) {
		stav = StavQuestu::DOKONCENY;
		Inventar* inv = paHrac->Getinventar();
		inv->zmazPredmet(menoPredmetu);
		Quest::dokonciSa(paHrac);
	}
}

void QuestLoot::kontrola() {
	Inventar* inv = Loader::Instance()->Gethra()->GetHrac()->Getinventar();
	if (inv->pocetPredmetov(menoPredmetu) < potrebneMnozstvo) {
		stav = StavQuestu::ROZROBENY;
	}
	else {
		stav = StavQuestu::SPLNENIE_POZIADAVIEK;
	}
}

std::string QuestLoot::coZbierat() {
	return menoPredmetu;
}

std::string QuestLoot::getPopis() {
	Inventar* inv = Loader::Instance()->Gethra()->GetHrac()->Getinventar();
	int aktPocet = inv->pocetPredmetov(menoPredmetu);

	std::string popis = Quest::getPopis()+ "\n\n";
	popis += "Progres: " + menoPredmetu + " - " + std::to_string(aktPocet) + " z " + std::to_string(potrebneMnozstvo)+"\n\n";
	popis += Quest::GetpopisOdmeny();
	return popis;
}