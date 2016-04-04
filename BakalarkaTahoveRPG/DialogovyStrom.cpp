#include "DialogovyStrom.h"

#include "Loader.h"
#include "Hra.h"
#include "Quest.h"
#include "QuestPolozka.h"
#include "Hrac.h"

DialogPolozka::DialogPolozka(string paText) {
	text = paText;
}

string DialogPolozka::Gettext() {
	return text;
}

DialogPolozka::~DialogPolozka() {
	for (unsigned int i = 0; i < dialogoveMoznosti.size(); i++)
	{
		delete dialogoveMoznosti[i];
	}
}

void DialogPolozka::pridajMoznost(DialogVolba* paVolba) {
	dialogoveMoznosti.push_back(paVolba);
}


int DialogPolozka::pocetMoznosti() {
	return dialogoveMoznosti.size();
}

DialogVolba* DialogPolozka::Getvolba(int paIndex) {
	if (paIndex >= 0 && static_cast<unsigned int>(paIndex)< static_cast<unsigned int>(dialogoveMoznosti.size())) {
		return dialogoveMoznosti[paIndex];
	}
	return nullptr;
}

string DialogVolba::Gettext() {
	return text;
}

void DialogPolozka::zmazMoznost(DialogVolba* paVolba) {
	dialogoveMoznosti.erase(std::remove(dialogoveMoznosti.begin(), dialogoveMoznosti.end(), paVolba), dialogoveMoznosti.end());
}


void DialogVolba::akcia(Hrac* hrac) {

}

DialogVolba::DialogVolba(string paText, int dalsia) {
	text = paText;
	this->dalsia = dalsia;
}

DialogovyStrom::DialogovyStrom()
{
	dialogQuest = nullptr;
	aktualnaPolozka = nullptr;
	stav = DialogStav::VYTVORENY;
}


DialogovyStrom::~DialogovyStrom()
{
	for (unsigned int i = 0; i < castiDialogu.size(); i++) {
		delete castiDialogu[i];
	}
	castiDialogu.clear();
}

DialogStav DialogovyStrom::Getstav() const
{
	return stav;
}


void DialogovyStrom::init() {
	//prva node ktoru vlozim do stromu bude prva
	aktualnaPolozka = castiDialogu[0];
	stav = DialogStav::INIT;
}

int DialogovyStrom::zmenPolozku(int moznost) {

	if (moznost >= 0 && moznost< aktualnaPolozka->pocetMoznosti()) {
		Loader* loader = Loader::Instance();
		aktualnaPolozka->Getvolba(moznost)->akcia(loader->Gethra()->Gethrac());
		if (aktualnaPolozka->Getvolba(moznost)->dalsia == -1) {
			stav = DialogStav::SKONCIL;
			if (dialogQuest != nullptr) {
				zmazMoznost(dialogQuest->GetvolbaKuQuestu(), dialogQuest->GetdialogPolozka());
				dialogQuest = nullptr;
			}
			return 0;
		}

		aktualnaPolozka = castiDialogu[aktualnaPolozka->Getvolba(moznost)->dalsia];
		return 0;
	}
	else return -1;
}

DialogPolozka* DialogovyStrom::Getaktualnapolozka() const
{
	return aktualnaPolozka;
}

int DialogovyStrom::zacniDialog() {
	if (castiDialogu.size() == 0) {
		stav = DialogStav::SKONCIL;
		return -1;
	}
	else {
		stav = DialogStav::BEZI;
		return -1;
	}
}

void DialogovyStrom::vlozPolozku(DialogPolozka* paPolozka) {
	castiDialogu.push_back(paPolozka);
}

void DialogovyStrom::pridajMoznost(DialogVolba* paVolba, DialogPolozka* paPolozka) {
	castiDialogu[0]->pridajMoznost(paVolba);
	castiDialogu.push_back(paPolozka);
	int pos = find(castiDialogu.begin(), castiDialogu.end(), paPolozka) - castiDialogu.begin();
	paVolba->dalsia = pos;

}

void DialogovyStrom::zmazMoznost(DialogVolba* paVolba, DialogPolozka* paPolozka) {
	castiDialogu[0]->zmazMoznost(paVolba);
	castiDialogu.erase(std::remove(castiDialogu.begin(), castiDialogu.end(), paPolozka), castiDialogu.end());
}

void DialogovyStrom::Setdialogquest(Quest* paQuest) {
	dialogQuest = paQuest;
	pridajMoznost(paQuest->GetvolbaKuQuestu(), paQuest->GetdialogPolozka());
}