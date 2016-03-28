#include "Quest.h"

#include "Hrac.h"
#include "Nepriatel.h"
#include "QuestOdmena.h"
#include "Inventar.h"

#include "Mapa.h"
#include "Policko.h"
#include "Poziadavka.h"

#include "QuestPolozka.h"
#include "DialogovyStrom.h"

Quest::Quest(string paNazov, string paPopis, int pocetXp, int pocetZlata, string paStartNpc, string paEndNpc, std::string nazovSuboru)
{
	this->poziadavky = new vector<Poziadavka*>();
	this->nazovSuboru = nazovSuboru;
	this->predchadzajuci = nullptr;
	this->nasledujuci = nullptr;
	this->odmena = new QuestOdmena(pocetXp, pocetZlata);
	this->nazov = paNazov;
	this->popis = paPopis;
	this->startNpc = paStartNpc;
	this->endNpc = paEndNpc;
	stav = StavQuestu::NEPRIJATY;
	dialogPolozka = nullptr;
	volbaKuQuestu = nullptr;
}

Quest::~Quest() {
	delete poziadavky;
}

void Quest::setStav(StavQuestu paStav) {
	stav = paStav;
}

string Quest::Getnazovsuboru() const
{
	return nazovSuboru;
}

StavQuestu Quest::Getstav() const
{
	return stav;
}

string Quest::Getnazov() const
{
	return nazov;
}

string Quest::getPopis() {


	string popisQuestu = "";

	string ts = "";
	switch (stav)
	{
	case StavQuestu::NEPRIJATY:
		ts = "";
		break;
	case StavQuestu::ROZROBENY:
		ts = "Active";
		break;
	case StavQuestu::SPLNENIE_POZIADAVIEK:
		ts = "Waiting for return";
		break;
	case StavQuestu::DOKONCENY:
		ts = "Complete";
		break;
	}
	popisQuestu += "State: " + ts + "\n\n" + popis + "\n\n";

	for (unsigned int i = 0; i < poziadavky->size(); i++) {
		popisQuestu += poziadavky->at(i)->Getpopis() + "\n";
	}

	popisQuestu += "\n" + GetpopisOdmeny();

	return popisQuestu;
}

void Quest::pridajOdmenu(Predmet* paPredmet) const
{
	odmena->pridajPredmet(paPredmet);
}

void Quest::dokonciSa(Hrac* paHrac) {
	if (stav == StavQuestu::SPLNENIE_POZIADAVIEK) {
		stav = StavQuestu::DOKONCENY;

		for (unsigned int i = 0; i < poziadavky->size(); i++) poziadavky->at(i)->dokoncenie(paHrac);

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

string Quest::GetpopisOdmeny() const
{
	string popis = "You will recieve:\n\n";
	if (odmena->Getpocetzlata() != 0) {
		popis += "Gold: " + std::to_string(odmena->Getpocetzlata()) + "\n";
	}

	if (odmena->Getpocetxp() != 0) {
		popis += "Experience : " + std::to_string(odmena->Getpocetxp()) + "\n";
	}

	if (odmena->getPredmety()->size() != 0) {
		popis += "Items:\n";
		for (unsigned int i = 0; i < odmena->getPredmety()->size(); i++) {
			popis += odmena->getPredmety()->at(i)->Getmeno() + "\n";
		}
	}
	return popis;
}

void Quest::zabitieNpc(Nepriatel* nepriatel) {
	if (stav == StavQuestu::ROZROBENY) {
		for (unsigned int i = 0; i < poziadavky->size(); i++) poziadavky->at(i)->akcia(nepriatel);
		kontrola();
	}
}


void Quest::lootnutiePredmetu(Predmet* paPredmet) {
	if (stav == StavQuestu::ROZROBENY) {
		for (unsigned int i = 0; i < poziadavky->size(); i++) poziadavky->at(i)->akcia(paPredmet);
		kontrola();
	}

}

void Quest::kontrola() {
	bool splnene = true;
	for (unsigned int i = 0; i < poziadavky->size(); i++) {
		if (!poziadavky->at(i)->jeSplnena()) splnene = false;
	}

	if (splnene && stav != StavQuestu::DOKONCENY) {
		stav = StavQuestu::SPLNENIE_POZIADAVIEK;
	}
	else {
		stav = StavQuestu::ROZROBENY;
	}
}

void Quest::pridajPoziadavku(Poziadavka* poziadavka) const
{
	poziadavky->push_back(poziadavka);
}

void Quest::Setnasledujuci(Quest* paQuest) {
	nasledujuci = paQuest;
}

Quest* Quest::Getnasledujuci() const
{
	return nasledujuci;
}

Quest* Quest::Getpredchadzajuci() const
{
	return predchadzajuci;
}

string Quest::Getstartnpc() const
{
	return startNpc;
}

string Quest::Getendnpc() const
{
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

QuestPolozka* Quest::GetdialogPolozka() const
{
	return dialogPolozka;
}
DialogVolba* Quest::GetvolbaKuQuestu() const
{
	return volbaKuQuestu;
}

vector<Poziadavka*>* Quest::Getpoziadavky() const
{
	return poziadavky;
}
