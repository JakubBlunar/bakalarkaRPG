#include "QuestKill.h"

#include <iostream>

#include "Nepriatel.h"
#include "Hrac.h"
#include "QuestOdmena.h"


QuestKill::QuestKill(std::string paNazov,std::string paPopis, std::string paKohoZabit, int paKolkokrat, int pocetXp, int pocetZlata)
	:Quest(paNazov,paPopis,pocetXp,pocetZlata)
{
	this->kohoZabit = paKohoZabit;
	this->kolkoZabit = paKolkokrat;
	this->pocetZabiti = 0;
}


QuestKill::~QuestKill()
{
}


void QuestKill::zabitieNpc(Nepriatel* nepriatel) {
	if (nepriatel->Getmeno() == kohoZabit && stav == ROZROBENY) {
		pocetZabiti++;
		//std::cout << "Quest " << nazov << " progress " << pocetZabiti << " z " << kolkoZabit << std::endl;
		kontrola();
	}
}


void QuestKill::kontrola() {
	if (pocetZabiti == kolkoZabit) {
		stav = StavQuestu::SPLNENIE_POZIADAVIEK;
		//std::cout << "Splnenie poziadaviek q " << nazov << std::endl;
	}
	else {
		stav = StavQuestu::ROZROBENY;
	}
}

void QuestKill::dokonciSa(Hrac* paHrac) {
	if (stav == StavQuestu::SPLNENIE_POZIADAVIEK) {
		stav = StavQuestu::DOKONCENY;
		Quest::dokonciSa(paHrac);
	}
}

void QuestKill::lootnutiePredmetu(Predmet* paPredmet) {
	kontrola();
}

std::string QuestKill::getPopis() {
	std::string popis = Quest::getPopis() + "\n\n";
	popis += "Progres: " + kohoZabit + " - " + std::to_string(pocetZabiti) + " z " + std::to_string(kolkoZabit)+"\n\n";
	popis += Quest::GetpopisOdmeny();
	return popis;
}