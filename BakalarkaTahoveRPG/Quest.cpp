#include "Quest.h"

#include <iostream>
#include "Hrac.h"
#include "Nepriatel.h"
#include "QuestOdmena.h"
#include "Inventar.h"

#include "Mapa.h"
#include "Policko.h"
#include "Poziadavka.h"

#include "VolbaUpravaQuestu.h"
#include "QuestPolozka.h"
#include "DialogovyStrom.h"

Quest::Quest(string paNazov, string paPopis, int pocetXp, int pocetZlata, string paStartNpc, string paEndNpc)
{
	this->predchadzajuci = nullptr;
	this->nasledujuci = nullptr;
	this->odmena = new QuestOdmena(pocetXp, pocetZlata);
	this->nazov = paNazov;
	this->popis = paPopis;
	this->startNpc = paStartNpc;
	this->endNpc = paEndNpc;
	stav = StavQuestu::NEPRIJATY;
}

void Quest::setStav(StavQuestu paStav) {
	stav = paStav;
}

StavQuestu Quest::Getstav() {
	return stav;
}

string Quest::Getnazov() {
	return nazov;
}

string Quest::getPopis() {
	
	
	string popisQuestu = "";
	
	string ts = "";
	switch (stav)
	{
	case StavQuestu::NEPRIJATY:
		ts = "Neprijaty";
		break;
	case StavQuestu::ROZROBENY:
		ts = "Aktivny";
		break;
	case StavQuestu::SPLNENIE_POZIADAVIEK:
		ts = "Caka na odovzdanie";
		break;
	case StavQuestu::DOKONCENY:
		ts = "Dokonceny";
		break;
	}
	popisQuestu+= "Stav: " + ts + "\n\n" + popis + "\n\n";

	for (unsigned int i = 0; i < poziadavky.size(); i++) {
		popisQuestu += poziadavky.at(i)->Getpopis() + "\n";
	}

	popisQuestu += "\n" + GetpopisOdmeny();

	return popisQuestu;
}

void Quest::pridajOdmenu(Predmet* paPredmet) {
	odmena->pridajPredmet(paPredmet);
}

void Quest::dokonciSa(Hrac* paHrac) {
	if (stav == StavQuestu::SPLNENIE_POZIADAVIEK) {
		stav = StavQuestu::DOKONCENY;

		for (unsigned int i = 0; i < poziadavky.size(); i++) poziadavky.at(i)->dokoncenie(paHrac);

		paHrac->pridajSkusenosti(odmena->Getpocetxp());

		Inventar* inv = paHrac->Getinventar();
		inv->pridajZlato(odmena->Getpocetzlata());

		vector<Predmet*>* predmety = odmena->getPredmety();
		for (unsigned int i = 0; i < predmety->size(); i++) {
			if (inv->pocetPredmetov() < inv->Getkapacita()) {
				paHrac->Getinventar()->pridajPredmet(predmety->at(i));
			}
			else {// ak nemá kapacitu v inventary tak sa predmety vyhodia na mapu kde hrac stoji
				Mapa* m = paHrac->getMapa();
				m->GetPolicko(paHrac->GetpolickoX(), paHrac->GetpolickoY())->polozPredmet(predmety->at(i), m->aktCas() + sf::seconds(300));
				
			}
		}
		
	}
}

string Quest::GetpopisOdmeny() {
	string popis = "Dostanes :\n\n";
	if (odmena->Getpocetzlata() != 0) {
		popis += "Zlato: " + std::to_string(odmena->Getpocetzlata())+"\n";
	}

	if (odmena->Getpocetxp() != 0) {
		popis += "Skusenosti: " + std::to_string(odmena->Getpocetxp()) + "\n";
	}

	if (odmena->getPredmety()->size() != 0) {
		popis += "Predmety:\n";
		for (unsigned int i = 0; i < odmena->getPredmety()->size(); i++) {
			popis += odmena->getPredmety()->at(i)->Getmeno() + "\n";
		}
	}
	return popis;
}

void Quest::zabitieNpc(Nepriatel* nepriatel) {
	if (stav == StavQuestu::ROZROBENY) {
		for (unsigned int i = 0; i < poziadavky.size(); i++) poziadavky.at(i)->akcia(nepriatel);
		kontrola();
	}
}

void Quest::lootnutiePredmetu(Predmet* paPredmet) {
	if (stav == StavQuestu::ROZROBENY) {
		for (unsigned int i = 0; i < poziadavky.size(); i++) poziadavky.at(i)->akcia(paPredmet);
		kontrola();
	}
	
}

void Quest::kontrola() {
	bool splnene = true;
	for (unsigned int i = 0; i < poziadavky.size(); i++) {
		if (!poziadavky.at(i)->jeSplnena()) splnene = false;
	}

	if (splnene && stav != StavQuestu::DOKONCENY) {
		stav = StavQuestu::SPLNENIE_POZIADAVIEK;
	}
	else {
		stav = StavQuestu::ROZROBENY;
	}
}

void Quest::pridajPoziadavku(Poziadavka* poziadavka) {
	poziadavky.push_back(poziadavka);
}

void Quest::Setnasledujuci(Quest* paQuest) {
	nasledujuci = paQuest;
}

Quest* Quest::Getnasledujuci() {
	return nasledujuci;
}

Quest* Quest::Getpredchadzajuci() {
	return predchadzajuci;
}

string Quest::Getstartnpc() {
	return startNpc;
}

string Quest::Getendnpc() {
	return endNpc;
}

void Quest::Setpredchadzajuci(Quest* paQuest) {
	predchadzajuci = paQuest;
}

void Quest::SetdialogPolozka(QuestPolozka* paPolozka) {
	dialogPolozka = paPolozka;
}
void Quest::SetvolbaKuQuestu(DialogVolba* paVolba) {
	volbaKuQuestu = paVolba;
}

QuestPolozka* Quest::GetdialogPolozka() {
	return dialogPolozka;
}
DialogVolba* Quest::GetvolbaKuQuestu() {
	return volbaKuQuestu;
}